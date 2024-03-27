#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"

Suite *create_sign_suite();
Suite *create_zero_suite();
Suite *create_scale_suite();
Suite *create_bit_suite();
Suite *create_big_decimal_converters_suite();
Suite *create_shifts_suite();
Suite *create_bitwise_operations_suite();
Suite *create_bitwise_division_suite();
Suite *create_normalizaion_suite();

// Converters
Suite *create_integer_converters_suite();
Suite *create_float_convertets_suite();
// Another

Suite *create_truncate_suite();
Suite *create_round_suite();
Suite *create_negate_suite();
Suite *create_floor_suite();

// Arithmetic
Suite *suite_mul();
Suite *create_add_suite();
Suite *create_div_suite();
Suite *create_sub_suite();
// Comparators
Suite *create_suite_is_equal();
Suite *create_suite_is_not_equal();

Suite *create_suite_is_less();
Suite *create_suite_is_less_or_equal();

Suite *create_suite_is_greater();
Suite *create_suite_is_greater_or_equal();
#endif  // S21_DECIMAL_TEST_H
