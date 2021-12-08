/**
 * @file main.c
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief mollier
 * @version 0.1
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "thermo.h"

#define HMAX 99
#define HSTEP 10
#define TMIN -246
#define TMAX 1000
#define GNUPLOT_FMT "%d %d %Lf\n"
#define GNUPLOT_SERIE_END "\n\n"

/**
 * @brief generate gnuplot datas using both mollier.(dat && gp)
 * 
 * 
 */
static void gnuplot_mollier(void)
{
    int tcpt, hcpt;
    for (hcpt = HMAX; hcpt > 0; hcpt -= HSTEP)
    {
        for (tcpt = TMIN; tcpt < TMAX; tcpt++)
            printf(
                GNUPLOT_FMT,
                hcpt,
                tcpt,
                dewpoint((ld)tcpt, (ld)hcpt));
        printf(GNUPLOT_SERIE_END);
    }
}

static ld he_fn_sample_eq(int a)
{
    //return (4 * a) - ((a * a) / 2);
    //return (1/50 * a - (a *a));
    //return 50 + (20 * sin(1/10 * (double)a) );
    return 20 * sin((double)a) + 80;
    //return 20 * sin((double)a / 8) + 80;
    //return (a * a) * (25 - (a * a));
    //return (0.5 * a) * (8 - a) + 80;
}

/**
 * @brief heat equation solver to generate gnuplot matrix datas
 * 
 * 
 */
static void gnuplot_heat_eq(void)
{
    fn_ld_int_t hfn = &he_fn_sample_eq;
    ld alpha = heat_eq_solver_1d_bs_method(
        150,
        100,
        4.0,
        0.0,
        0.0,
        1.0, 
        1.0 / 8.0, 
        hfn);
}

/**
 * @brief main
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    //gnuplot_mollier();
    gnuplot_heat_eq();
    return EXIT_SUCCESS;
}
