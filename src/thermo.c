
#include <stdlib.h>
#include <stdio.h>
#include "thermo.h"

ld celcius2kelvin(ld t)
{
    return t + 273.15f;
}

ld celcius2fahrenheit(ld t)
{
    const ld slope = 9 / 5;
    const ld offset = 32;
    return (t * slope) + offset;
}

ld fahrenheit2celcius(ld t)
{
    const ld slope = 5 / 9;
    const ld offset = 32;
    return (t - offset) * slope;
}

ld pressure_altitude(ld a)
{
    const ld p0 = 1013.25; // ref hPa for 15°C 100m norm OACI
    const ld delta = 0.0065 / 288.15;
    const ld p = p0 * powl(1 - (a * delta), 5.255);
    return p;
}

ld dewpoint(ld t, ld h)
{
    ld a,    // Temperature converted in °K
        svp, // Saturated Vapor Pressure Pa
        vp,  // Vapor Pressure Pa
        td;  // Temperature Dewpoint °C
    a = 373.15f / celcius2kelvin(t);
    svp = -7.90298f * (a - 1);
    svp += 5.02808f * log10l(a);
    svp += -1.3816e-7 * (powl(10.0f, (11.344f * (1.0f - 1.0f / a))) - 1.0f);
    svp += 8.1328e-3 * (powl(10.0f, (-3.49149f * (a - 1.0f))) - 1.0f);
    svp += log10l(1013.246f);
    vp = powl(10.0f, svp - 3.0f) * h;
    td = logl(vp / 0.61078f);
    td = (241.88f * td) / (17.558f - td);
    return td;
}

ld dewpoint_fast(ld t, ld h)
{
    const ld a = 17.271;
    const ld b = 237.7;
    const ld temp = (a * t) / (b + t) + logl(h / 100);
    return (b * temp) / (a - temp);
}

ld absolute_humidity(ld t, ld h)
{
    ld ah,  // Absolute humidity
        at; // Absolute temperature °K
    at = celcius2kelvin(t);
    ah = 6.112;
    ah *= expl((17.67 * t) / at);
    ah *= h;
    ah *= 2.1674;
    ah /= at;
    return ah;
}

ld heat_index(ld t, ld h)
{
    ld hi;
    hi = 0.5 * (t + 61.0 + ((t - 68.0) * 1.2) + (h * 0.094));
    if (hi < 79)
        return hi;
    const ld _2 = 2.0f;
    const ld tp2 = powl(t, _2);
    const ld hp2 = powl(h, _2);
    hi = -42.379 +
         2.04901523 * t +
         10.14333127 * h +
         -0.22475541 * t * h +
         -0.00683783 * tp2 +
         -0.05481717 * hp2 +
         0.00122874 * tp2 * h +
         0.00085282 * t * hp2 +
         -0.00000199 * tp2 * hp2;
    if (t >= 80.0)
    {
        if ((h < 13) && (t <= 112.0))
            hi -= ((13.0 - h) * 0.25) * sqrtl((17.0 - fabsl(t - 95.0)) * 0.05882);

        else if ((h > 85.0) && (t <= 87.0))
            hi += ((h - 85.0) * 0.1) * ((87.0 - t) * 0.2);
    }
    return hi;
}

ld heat_eq_solver_1d_bs_method(
    unsigned int nx,
    unsigned int nt,
    ld a2,
    ld u0,
    ld ue,
    ld h,
    ld k,
    fn_ld_int_t fn)
{
    FILE *streamout = stdout;
    unsigned int j, i;
    ld lambda;
    minfo_t *minfo;
    minfo = malloc(sizeof(minfo_t));
    minfo->nbcol = nx;
    minfo->nbrow = nt;
    pr_vector_t mat;
    pr_vector_t vcols;
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));
    mat_init(&mat, minfo, 0.0);
    lambda = (k * a2) / (h * h);
    const unsigned short implicit_form = (lambda != 0.5);
    vcols = malloc(sizeof(pr_item_t) * minfo->nbcol);
    mat_get_col(&mat, minfo, 0, &vcols);
    mat_fill_vect(&vcols, minfo->nbcol, u0);
    mat_set_col(&mat, 0, &vcols, minfo, 0);
    for (j = 1; j < nx; j++)
        mat_set_value(&mat, 0, j, minfo, fn((int)j));
    if (implicit_form == 1)
        for (i = 0; i < nt - 1; i++)
            for (j = 1; j < nx - 1; j++)
            {
                const ld mlv = mat_get_value(&mat, i, j - 1, minfo);
                const ld mcv = mat_get_value(&mat, i, j, minfo);
                const ld mrv = mat_get_value(&mat, i, j + 1, minfo);
                const ld mv = (lambda * (mlv + mrv)) + ((1 - (2 * lambda)) * mcv);
                mat_set_value(&mat, i + 1, j, minfo, mv * lambda);
            }
    else
        for (i = 0; i < nt - 1; i++)
            for (j = 1; j < nx - 1; j++)
            {
                const ld mlv = mat_get_value(&mat, i, j - 1, minfo);
                const ld mrv = mat_get_value(&mat, i, j + 1, minfo);
                const ld mv = (mlv + mrv) / 2;
                mat_set_value(&mat, i + 1, j, minfo, mv);
            }
    mat_print(&mat, minfo, streamout);
    free(vcols);
    free(mat);
    free(minfo);
    return lambda;
}