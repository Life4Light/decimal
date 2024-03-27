#include "s21_decimal_test.h"

START_TEST(test_1) {
  s21_big_decimal dec = {};
  s21_big_set_scale(&dec, 10);
  ck_assert_int_eq(s21_big_get_scale(&dec), 10);
}
END_TEST

START_TEST(test_2) {
  s21_big_decimal dec = {};
  // s21_big_set_sign(&dec, 1);
  s21_big_set_scale(&dec, -10);
  ck_assert_int_eq(s21_big_get_scale(&dec), 0);
}
END_TEST

START_TEST(test_3) {
  s21_big_decimal dec = {};
  s21_big_set_sign(&dec, 1);
  s21_big_set_scale(&dec, 10);
  ck_assert(s21_big_get_scale(&dec) == 10 && s21_big_get_sign(&dec) == 1);
}
END_TEST

START_TEST(test_4) {
  s21_big_decimal dec = {};
  s21_big_set_sign(&dec, 1);
  s21_big_set_scale(&dec, -10);
  ck_assert(s21_big_get_scale(&dec) == 0 && s21_big_get_sign(&dec) == 1);
}
END_TEST

START_TEST(test_5) {
  s21_big_decimal dec = {};
  s21_big_set_sign(&dec, 1);
  s21_big_set_scale(&dec, 10);
  s21_big_set_scale(&dec, -10);
  ck_assert(s21_big_get_scale(&dec) == 10 && s21_big_get_sign(&dec) == 1);
}
END_TEST

START_TEST(test_6) {
  s21_big_decimal dec = {};
  s21_big_set_sign(&dec, 1);

  ck_assert(s21_big_set_scale(&dec, 2048) == CALCULATION_ERROR);
}
END_TEST

START_TEST(test_7) {
  s21_decimal dec = {};
  s21_set_scale(&dec, 10);
  ck_assert_int_eq(s21_get_scale(&dec), 10);
}
END_TEST

START_TEST(test_8) {
  s21_decimal dec = {};
  // s21_big_set_sign(&dec, 1);
  s21_set_scale(&dec, -10);
  ck_assert_int_eq(s21_get_scale(&dec), 0);
}
END_TEST

START_TEST(test_9) {
  s21_decimal dec = {};
  s21_set_sign(&dec, 1);
  s21_set_scale(&dec, 10);
  ck_assert(s21_get_scale(&dec) == 10 && s21_get_sign(&dec) == 1);
}
END_TEST

START_TEST(test_10) {
  s21_decimal dec = {};
  s21_set_sign(&dec, 1);
  s21_set_scale(&dec, -10);
  ck_assert(s21_get_scale(&dec) == 0 && s21_get_sign(&dec) == 1);
}
END_TEST

START_TEST(test_11) {
  s21_decimal dec = {};
  s21_set_sign(&dec, 1);
  s21_set_scale(&dec, 10);
  s21_set_scale(&dec, -10);
  ck_assert(s21_get_scale(&dec) == 10 && s21_get_sign(&dec) == 1);
}
END_TEST

START_TEST(test_12) {
  s21_decimal dec = {};
  s21_set_sign(&dec, 1);

  ck_assert(s21_set_scale(&dec, 2048) == CALCULATION_ERROR);
}
END_TEST

Suite *create_scale_suite() {
  Suite *suite = suite_create("scale tests");
  TCase *tc = tcase_create("scale");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  suite_add_tcase(suite, tc);

  return suite;
}
