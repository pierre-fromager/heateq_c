/**
 * @file suite_fraction.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Test suite for polynomial fractions 
 * @version 0.1
 * @date 2021-11-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __TEST_MOLLIER_SUITE_THERMO_H__
#define __TEST_MOLLIER_SUITE_THERMO_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thermo.h"

void test_mollier_thermo_add_suite(void);
void reset_test_thermo(void);

void test_mollier_thermo_pressure_altitude(void);

#endif // __TEST_MOLLIER_SUITE_THERMO_H__