
#include "suite_thermo.h"

void reset_test_thermo()
{
}

static int suite_setup(void)
{
    reset_test_thermo();
    return 0;
}

static int suite_teardown(void)
{
    reset_test_thermo();
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_mollier_thermo_pressure_altitude, "pressure_altitude"},
    {0, 0},
};

void test_mollier_thermo_add_suite()
{
    const char *suite_name = "thermo";
    const char *suite_err_fmt = "Error adding suite %s : %s\n";
    const char *test_err_fmt = "Error adding test '%s' : %s\n";
    CU_pSuite suite = CU_add_suite(suite_name, suite_setup, suite_teardown);
    if (!suite)
    {
        CU_cleanup_registry();
        printf(suite_err_fmt, suite_name, CU_get_error_msg());
        _exit(3);
    }
    int i;
    for (i = 0; test_functions[i].name; i++)
    {
        if (!CU_add_test(suite, test_functions[i].name, test_functions[i].function))
        {
            CU_cleanup_registry();
            printf(test_err_fmt, test_functions[i].name, CU_get_error_msg());
            _exit(3);
        }
    }
}

void test_mollier_thermo_pressure_altitude()
{
    const double granularity = 0.01f;
    const ld altitudes[17] = {
        0, 500, 1000, 1500, 2000,
        2500, 3000, 3500, 4000, 4500,
        5000, 6000, 7000, 8000, 9000,
        10000, 11000};
    const ld pressures[17] = {
        1013.25, 954.62, 898.76, 845.59, 794.98,
        746.86, 701.12, 657.68, 616.45, 577.33,
        540.25, 471.87, 410.66, 356.06, 307.48,
        264.42, 226.37};

    for (int i = 0; i < 17; i++)
        CU_ASSERT_DOUBLE_EQUAL(
            (double)pressures[i],
            (double)pressure_altitude(altitudes[i]),
            granularity);
}
