// #include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "romancalc.h"

START_TEST (test_mapromandigit_1)
{
    ck_assert_int_eq(mapromandigit('0'), -1);
}
END_TEST

START_TEST (test_mapromandigit_2)
{
    ck_assert_int_eq(mapromandigit('\0'), 0);
}
END_TEST

START_TEST (test_mapromandigit_3)
{
    ck_assert_int_eq(mapromandigit('I'), 1);
}
END_TEST

START_TEST (test_mapromandigit_4)
{
    ck_assert_int_eq(mapromandigit('V'), 5);
}
END_TEST

START_TEST (test_mapromandigit_5)
{
    ck_assert_int_eq(mapromandigit('X'), 10);
}
END_TEST

START_TEST (test_mapromandigit_6)
{
    ck_assert_int_eq(mapromandigit('L'), 50);
}
END_TEST

START_TEST (test_mapromandigit_7)
{
    ck_assert_int_eq(mapromandigit('C'), 100);
}
END_TEST

START_TEST (test_mapromandigit_8)
{
    ck_assert_int_eq(mapromandigit('D'), 500);
}
END_TEST

START_TEST (test_mapromandigit_9)
{
    ck_assert_int_eq(mapromandigit('M'), 1000);
}
END_TEST

START_TEST (test_mapromandigit_10)
{
    ck_assert_int_eq(mapromandigit('i'), -1);
}
END_TEST


START_TEST (test_compare_1)
{
    ck_assert_int_eq(compare(9, 1), -1); // IIX
}
END_TEST

START_TEST (test_compare_2)
{
    ck_assert_int_eq(compare(5, 1), 4); // IV
}
END_TEST

START_TEST (test_compare_3)
{
    ck_assert_int_eq(compare(10, 1), 9); // IX
}
END_TEST

START_TEST (test_compare_4)
{
    ck_assert_int_eq(compare(10, 5), -1); // VX
}
END_TEST

START_TEST (test_compare_5)
{
    ck_assert_int_eq(compare(1, 1), 2); // II
}
END_TEST


START_TEST (test_rtod_1)
{
    ck_assert_int_eq(romantodecimal("I"), 1);
}
END_TEST

START_TEST (test_rtod_2)
{
    ck_assert_int_eq(romantodecimal("II"), 2);
}
END_TEST

START_TEST (test_rtod_3)
{
    ck_assert_int_eq(romantodecimal("III"), 3);
}
END_TEST

START_TEST (test_rtod_4)
{
    ck_assert_int_eq(romantodecimal("XXX"), 30);
}
END_TEST

START_TEST (test_rtod_5)
{
    ck_assert_int_eq(romantodecimal("XXXX"), -1);
}
END_TEST

START_TEST (test_rtod_6)
{
    ck_assert_int_eq(romantodecimal("IVI"), -1);
}
END_TEST


START_TEST (test_calc_1)
{
    char add = '+';
    ck_assert_int_eq(calculator((char *)&add, 1, 1), 2);
}
END_TEST

START_TEST (test_calc_2)
{
    char add = '+';
    ck_assert_int_eq(calculator((char *)&add, 1, 1000), 1001);    
}
END_TEST

START_TEST (test_calc_3)
{
    char add = '+';
    ck_assert_int_eq(calculator((char *)&add, 50, 1), 51);
}
END_TEST

START_TEST (test_calc_4)
{
    char sub = '-';
    ck_assert_int_eq(calculator((char *)&sub, 51, 2), 49);
}
END_TEST

START_TEST (test_calc_5)
{
    char sub = '-';
    ck_assert_int_eq(calculator((char *)&sub, 3, 100), 97);
}
END_TEST

START_TEST (test_calc_6)
{
    char mul = '*';
    ck_assert_int_eq(calculator((char *)&mul, 1, 2), -1);
}
END_TEST


START_TEST (test_dtor_1)
{    
    ck_assert_str_eq(decimaltoroman(3), "III");
}
END_TEST

START_TEST (test_dtor_2)
{    
    ck_assert_str_eq(decimaltoroman(1001), "MI");
}
END_TEST

START_TEST (test_dtor_3)
{    
    ck_assert_str_eq(decimaltoroman(30), "XXX");
}
END_TEST

START_TEST (test_dtor_4)
{    
    ck_assert_str_eq(decimaltoroman(1984), "MCMLXXXIV");
}
END_TEST

START_TEST (test_dtor_5)
{    
    ck_assert_str_eq(decimaltoroman(1234), "MCCXXXIV");
}
END_TEST

START_TEST (test_dtor_6)
{    
    ck_assert_str_eq(decimaltoroman(490), "CDXC");
}
END_TEST



Suite * romancalc_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("RomanCalc");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_mapromandigit_1);
    tcase_add_test(tc_core, test_mapromandigit_2);
    tcase_add_test(tc_core, test_mapromandigit_3);
    tcase_add_test(tc_core, test_mapromandigit_4);
    tcase_add_test(tc_core, test_mapromandigit_5);
    tcase_add_test(tc_core, test_mapromandigit_6);
    tcase_add_test(tc_core, test_mapromandigit_7);
    tcase_add_test(tc_core, test_mapromandigit_8);
    tcase_add_test(tc_core, test_mapromandigit_9);
    tcase_add_test(tc_core, test_mapromandigit_10);
    
    tcase_add_test(tc_core, test_compare_1);
    tcase_add_test(tc_core, test_compare_2);
    tcase_add_test(tc_core, test_compare_3);
    tcase_add_test(tc_core, test_compare_4);
    tcase_add_test(tc_core, test_compare_5);
    
    tcase_add_test(tc_core, test_rtod_1);
    tcase_add_test(tc_core, test_rtod_2);
    tcase_add_test(tc_core, test_rtod_3);
    tcase_add_test(tc_core, test_rtod_4);
    tcase_add_test(tc_core, test_rtod_5);
    tcase_add_test(tc_core, test_rtod_6);
    
    tcase_add_test(tc_core, test_calc_1);
    tcase_add_test(tc_core, test_calc_2);
    tcase_add_test(tc_core, test_calc_3);
    tcase_add_test(tc_core, test_calc_4);
    tcase_add_test(tc_core, test_calc_5);
    tcase_add_test(tc_core, test_calc_6);
    
    tcase_add_test(tc_core, test_dtor_1);
    tcase_add_test(tc_core, test_dtor_2);
    tcase_add_test(tc_core, test_dtor_3);
    tcase_add_test(tc_core, test_dtor_4);
    tcase_add_test(tc_core, test_dtor_5);
    tcase_add_test(tc_core, test_dtor_6);
    
    suite_add_tcase(s, tc_core);

    return s;
}

int main (void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = romancalc_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

