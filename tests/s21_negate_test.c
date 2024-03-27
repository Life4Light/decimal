#include "s21_decimal_test.h"

START_TEST(negate_test_1) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {1, 1, 1, 0};
  s21_set_scale(&decimal, 28);
  s21_decimal result;
  s21_decimal expected_result = {1, 1, 1, 0};
  s21_set_scale(&expected_result, 28);
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_negate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(negate_test_2) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {5, 5, 5, 0};
  //  s21_set_scale(&decimal, 28);
  s21_set_sign(&decimal, 1);
  s21_decimal result;
  s21_decimal expected_result = {5, 5, 5, 0};
  //  s21_set_scale(&expected_result, 28);
  s21_set_sign(&expected_result, 0);
  ck_assert(s21_negate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(negate_test_3) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {7, 0, 0, 0};
  //  s21_set_scale(&decimal, 28);
  s21_decimal result;
  s21_decimal expected_result = {7, 0, 0, 0};
  //  s21_set_scale(&expected_result, 28);
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_negate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(negate_test_4) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {0, 0, 0, 0};
  //  s21_set_scale(&decimal, 28);
  s21_decimal result;
  s21_decimal expected_result = {0, 0, 0, 0};
  //  s21_set_scale(&expected_result, 28);
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_negate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

START_TEST(negate_test_5) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&decimal, 28);
  s21_decimal result;
  s21_decimal expected_result = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&expected_result, 28);
  s21_set_sign(&expected_result, 1);
  ck_assert(s21_negate(decimal, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}

Suite *create_negate_suite() {
  Suite *suite = suite_create("negate_tests_suite");

  TCase *add_test_case = tcase_create("negate_test_case");
  tcase_add_test(add_test_case, negate_test_1);
  tcase_add_test(add_test_case, negate_test_2);
  tcase_add_test(add_test_case, negate_test_3);
  tcase_add_test(add_test_case, negate_test_4);
  tcase_add_test(add_test_case, negate_test_5);

  suite_add_tcase(suite, add_test_case);
  return suite;
}
