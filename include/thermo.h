/**
 * @file thermo.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief thermo headers for temperatures
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _MOLLIER_THERMO_
#define _MOLLIER_THERMO_

#include <math.h>
#include "matrix.h"

typedef long double ld;
typedef ld (*fn_ld_int_t)(int);

/**
 * @brief conert celcius to kelvin
 * 
 * @param t 
 * @return ld 
 */
ld celcius2kelvin(ld t);

/**
 * @brief pressure 
 * 
 * @param a m
 * @return ld hPa | mb
 */
ld pressure_altitude(ld a);

/**
 * @brief dewpoint
 * @url http://wahiduddin.net/calc/density_algorithms.htm
 * 
 * @param t °C
 * @param h %
 * @return ld °C
 */
ld dewpoint(ld t, ld h);

/**
 * @brief dewpoint fast
 * 
 * @param t °C
 * @param h %
 * @return ld °C
 */
ld dewpoint_fast(ld t, ld h);

/**
 * @brief absolute humidity g/m³
 * @url https://carnotcycle.wordpress.com/2012/08/04/how-to-convert-relative-humidity-to-absolute-humidity/
 * 
 * @param t °C
 * @param h %
 * @return ld %
 */
ld absolute_humidity(ld t, ld h);

/**
 * @brief Using both Rothfusz and Steadman's equations
 * @url https://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
 * 
 * @param t °F
 * @param h %
 * @return ld °F
 */
ld heat_index(ld t, ld h);

/**
 * @brief Bender-Schmidt method 1d FDM solver using implicit or explicit form
 *          heat equation (∂u/∂t)=α²(∂²u/∂x²)
 *          considering 
 *          α² = k/pc
 *          k thermal conductivity (W/(m·K))
 *          pc specific heat capacity (J/(kg·K)) with
 *          p material density kg/m3
 *          c specific heat capacity (kJ kg−1 K−1)
 * 
 * @param nx vector size : number of values (Y) for matrix m(X,Y)
 * @param nt vector size : number of time (X) for matrix m(X,Y)
 * @param a2 α²
 * @param u0 initial boundary condition
 * @param ue terminal boundary condition
 * @param h stepsize of x (along x-axis)
 * @param k stepsize of t (along y-axis)
 * @param fn energy equation u(x,0)
 * @return ld lambda coefficient of conductivity
 */
ld heat_eq_solver_1d_bs_method(
    unsigned int nx,
    unsigned int nt,
    ld a2,
    ld u0,
    ld ue,
    ld h,
    ld k,
    fn_ld_int_t fn);

#endif // _MOLLIER_THERMO_