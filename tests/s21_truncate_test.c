
#include "s21_decimal_test.h"

START_TEST(truncate_test_1) {
  // 7.9228162514264337593543950335
  // 7
  s21_decimal decimal = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&decimal, 28);
  s21_decimal result;
  s21_decimal expected_result = {7, 0, 0, 0};
  ck_assert(s21_truncate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(truncate_test_2) {
  //-7.9228162514264337593543950335
  //-7
  s21_decimal decimal = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&decimal, 28);
  s21_set_sign(&decimal, 1);
  s21_decimal result;
  s21_decimal expected_result = {7, 0, 0, 0};
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_truncate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(truncate_test_3) {
  //-7
  //-7
  s21_decimal decimal = {7, 0, 0, 0};
  s21_set_sign(&decimal, 1);
  s21_decimal result;
  s21_decimal expected_result = {7, 0, 0, 0};
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_truncate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(truncate_test_4) {
  //-7.234
  //-7
  s21_decimal decimal = {7234, 0, 0, 0};
  s21_set_scale(&decimal, 3);
  s21_set_sign(&decimal, 1);
  s21_decimal result;
  s21_decimal expected_result = {7, 0, 0, 0};
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_truncate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(truncate_test_5) {
  // 0.01
  // 0
  s21_decimal decimal = {1, 0, 0, 0};
  s21_set_scale(&decimal, 2);
  s21_decimal result;
  s21_decimal expected_result = {0, 0, 0, 0};
  ck_assert(s21_truncate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

Suite *create_truncate_suite() {
  Suite *suite = suite_create("truncate_tests_suite");

  TCase *add_test_case = tcase_create("truncate_test_case");
  tcase_add_test(add_test_case, truncate_test_1);
  tcase_add_test(add_test_case, truncate_test_2);
  tcase_add_test(add_test_case, truncate_test_3);
  tcase_add_test(add_test_case, truncate_test_4);
  tcase_add_test(add_test_case, truncate_test_5);

  suite_add_tcase(suite, add_test_case);
  return suite;
}