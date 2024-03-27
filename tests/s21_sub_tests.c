
#include "s21_decimal_test.h"
START_TEST(sub_test_1) {
  s21_decimal value_1 = {
      15,
      0,
      0,
      0,
  };
  s21_decimal value_2 = {5, 0, 0, 0};
  s21_decimal excepted_result = {10};
  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_sub(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

START_TEST(sub_test_2) {
  s21_decimal value_1 = {
      5,
      0,
      0,
      0,
  };
  s21_decimal value_2 = {15, 0, 0, 0};
  s21_decimal excepted_result = {10};
  s21_set_sign(&excepted_result, 1);
  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_sub(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

Suite *create_sub_suite() {
  Suite *suite = suite_create("sub_tests_suite");

  TCase *add_test_case = tcase_create("sub_test_case");
  tcase_add_test(add_test_case, sub_test_1);
  tcase_add_test(add_test_case, sub_test_2);

  suite_add_tcase(suite, add_test_case);
  return suite;
}
