#include "s21_decimal_test.h"

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST
START_TEST(floor_2) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_set_sign(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *create_floor_suite(void) {
  Suite *s = suite_create("floor_tests_suite");
  TCase *tc = tcase_create("case_floor");

  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);

  suite_add_tcase(s, tc);
  return s;
}
