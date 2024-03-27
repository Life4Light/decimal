
#include "s21_decimal_test.h"
START_TEST(int_to_decimal_test_1) {
  s21_decimal decimal;
  int integer = 12345678;
  s21_decimal expected_result = {12345678, 0, 0, 0};
  s21_from_int_to_decimal(integer, &decimal);
  ck_assert(s21_is_equal(decimal, expected_result) == TRUE);
}
END_TEST

START_TEST(int_to_decimal_test_2) {
  s21_decimal decimal;
  int integer = -12345678;
  s21_decimal expected_result = {12345678, 0, 0, 0};
  s21_set_sign(&expected_result, 1);
  s21_from_int_to_decimal(integer, &decimal);
  ck_assert(s21_is_equal(decimal, expected_result) == TRUE);
}
END_TEST

START_TEST(int_to_decimal_test_3) {
  s21_decimal decimal;
  int integer = INT_MIN;
  s21_decimal expected_result = {((unsigned)INT_MAX + 1), 0, 0, 0};
  s21_set_sign(&expected_result, 1);
  s21_from_int_to_decimal(integer, &decimal);
  ck_assert(s21_is_equal(decimal, expected_result) == TRUE);
}
END_TEST

START_TEST(int_to_decimal_test_4) {
  s21_decimal decimal;
  int integer = INT_MAX;
  s21_decimal expected_result = {INT_MAX, 0, 0, 0};
  s21_from_int_to_decimal(integer, &decimal);
  ck_assert(s21_is_equal(decimal, expected_result) == TRUE);
}
END_TEST

START_TEST(int_to_decimal_test_5) {
  s21_decimal decimal = {12345678};
  int result;
  s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(result, 12345678);
}
END_TEST
START_TEST(int_to_decimal_test_6) {
  s21_decimal decimal = {12345678};
  s21_set_sign(&decimal, 1);
  int result;
  s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(result, -12345678);
}
END_TEST
START_TEST(int_to_decimal_test_7) {
  s21_decimal decimal = {(unsigned)INT_MAX + 1};
  s21_set_sign(&decimal, 1);
  int result;
  s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(result, INT_MIN);
}
END_TEST
START_TEST(int_to_decimal_test_8) {
  s21_decimal decimal = {INT_MAX};
  int result;
  s21_from_decimal_to_int(decimal, &result);
  ck_assert_int_eq(result, INT_MAX);
}
END_TEST
Suite *create_integer_converters_suite() {
  Suite *suite = suite_create("int_to_decimal_tests_suite");

  TCase *converters_test_case = tcase_create("int_to_decimal_test_case");
  tcase_add_test(converters_test_case, int_to_decimal_test_1);
  tcase_add_test(converters_test_case, int_to_decimal_test_2);
  tcase_add_test(converters_test_case, int_to_decimal_test_3);
  tcase_add_test(converters_test_case, int_to_decimal_test_4);
  tcase_add_test(converters_test_case, int_to_decimal_test_5);
  tcase_add_test(converters_test_case, int_to_decimal_test_6);
  tcase_add_test(converters_test_case, int_to_decimal_test_7);
  tcase_add_test(converters_test_case, int_to_decimal_test_8);

  suite_add_tcase(suite, converters_test_case);
  return suite;
}
