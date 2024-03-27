#include "s21_decimal_test.h"

START_TEST(test_1) {
  s21_big_decimal bd = {};
  bd.bits[7] |= 1 << 31;
  ck_assert_int_eq(s21_big_get_sign(&bd), 1);
}
END_TEST

START_TEST(test_2) {
  s21_big_decimal bd = {};
  ck_assert_int_eq(s21_big_get_sign(&bd), 0);
}
END_TEST

START_TEST(test_3) {
  s21_big_decimal bd = {};
  s21_big_set_sign(&bd, 1);
  ck_assert_int_eq(s21_big_get_sign(&bd), 1);
}
END_TEST

START_TEST(test_4) {
  s21_big_decimal bd = {};
  s21_big_set_sign(&bd, 0);
  ck_assert_int_eq(s21_big_get_sign(&bd), 0);
}
END_TEST

START_TEST(test_5) {
  s21_decimal bd = {};
  bd.bits[3] |= 1 << 31;
  ck_assert_int_eq(s21_get_sign(&bd), 1);
}
END_TEST

START_TEST(test_6) {
  s21_decimal bd = {};
  ck_assert_int_eq(s21_get_sign(&bd), 0);
}
END_TEST

START_TEST(test_7) {
  s21_decimal bd = {};
  s21_set_sign(&bd, 1);
  ck_assert_int_eq(s21_get_sign(&bd), 1);
}
END_TEST

START_TEST(test_8) {
  s21_decimal bd = {};
  s21_set_sign(&bd, 0);
  ck_assert_int_eq(s21_get_sign(&bd), 0);
}
END_TEST

Suite *create_sign_suite() {
  Suite *suite = suite_create("sign tests");
  TCase *tc = tcase_create("sign");
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);

  suite_add_tcase(suite, tc);

  return suite;
}
