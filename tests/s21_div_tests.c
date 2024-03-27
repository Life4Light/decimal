
#include "s21_decimal_test.h"

START_TEST(div_test_1) {
  s21_decimal divisible = {15, 0, 0, 0};
  s21_decimal divider = {3, 0, 0, 0};
  s21_decimal result = {{0}};
  s21_decimal expected_result = {5, 0, 0, 0};

  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(div_test_2) {
  s21_decimal divisible = {1, 0, 0, 0};
  s21_decimal divider = {3, 0, 0, 0};
  s21_decimal result = {{0}};
  s21_decimal expected_result = {0x05555555, 0x14B700CB, 0xAC544CA, 0};
  s21_set_scale(&expected_result, 28);

  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(div_test_3) {
  s21_decimal divisible = {4, 0, 0, 0};
  s21_decimal divider = {3, 0, 0, 0};
  s21_decimal result = {{0}};
  s21_decimal expected_result = {0x15555555, 0x52DC032C, 0x2B151328, 0};
  s21_set_scale(&expected_result, 28);

  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(div_test_4) {
  s21_decimal divisible = {72656, 0, 0, 0};
  s21_decimal divider = {1, 0, 0, 0};
  s21_set_scale(&divider, 28);

  s21_decimal result = {{0}};

  ck_assert(s21_div(divisible, divider, &result) == NUMBER_TOO_LARGE);
}
END_TEST
START_TEST(div_test_5) {
  s21_decimal divisible = {72656, 0, 0, 0};
  s21_decimal divider = {1, 0, 0, 0};
  s21_set_scale(&divider, 28);
  s21_set_sign(&divider, 1);

  s21_decimal result = {{0}};

  ck_assert(s21_div(divisible, divider, &result) == NUMBER_TOO_LOW);
}
END_TEST

START_TEST(div_test_6) {
  s21_decimal divisible = {70005, 0, 0, 0};
  s21_set_scale(&divisible, 1);

  s21_decimal divider = {7000, 0, 0, 0};
  s21_decimal result = {{0}};

  s21_decimal expected_result = {0xF0B6DB6E, 0xBFB8B953, 0x2050659F, 0};

  s21_set_scale(&expected_result, 28);

  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(div_test_7) {
  s21_decimal divisible = {2, 0, 0, 0};

  s21_decimal divider = {3, 0, 0, 0};
  s21_decimal result = {{0}};

  s21_decimal expected_result = {0x0AAAAAAB, 0x296E0196, 0x158A8994, 0};
  s21_set_scale(&expected_result, 28);
  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(div_test_8) {
  s21_decimal divisible = {0, 0, 0, 0};

  s21_decimal divider = {3, 0, 0, 0};
  s21_decimal result = {{0}};

  s21_decimal expected_result = {0, 0, 0, 0};
  ck_assert(s21_div(divisible, divider, &result) == OK);
  ck_assert(s21_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(div_test_9) {
  s21_decimal divisible = {3, 0, 0, 0};
  s21_decimal divider = {0, 0, 0, 0};
  s21_decimal result = {{0}};
  ck_assert(s21_div(divisible, divider, &result) == 3);
}
END_TEST
Suite *create_div_suite() {
  Suite *suite = suite_create("div_tests_suite");
  TCase *div_test_case = tcase_create("div_test_case");

  tcase_add_test(div_test_case, div_test_1);
  tcase_add_test(div_test_case, div_test_2);
  tcase_add_test(div_test_case, div_test_3);
  tcase_add_test(div_test_case, div_test_4);
  tcase_add_test(div_test_case, div_test_5);
  tcase_add_test(div_test_case, div_test_6);
  tcase_add_test(div_test_case, div_test_7);
  tcase_add_test(div_test_case, div_test_8);
  tcase_add_test(div_test_case, div_test_9);

  suite_add_tcase(suite, div_test_case);
  return suite;
}
