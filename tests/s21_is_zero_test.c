#include "s21_decimal_test.h"

START_TEST(test_1) {
  int ret = true;
  for (int i = 0; i < 7; i++) {
    s21_big_decimal bd = {};
    bd.bits[i] = 123;
    if (s21_big_is_zero(&bd)) {
      ret = false;
    }
  }
  ck_assert(ret);
}
END_TEST

START_TEST(test_2) {
  s21_big_decimal bd = {};
  ck_assert(s21_big_is_zero(&bd));
}
END_TEST

START_TEST(test_3) {
  s21_big_decimal bd = {};
  bd.bits[7] = 123;
  ck_assert(s21_big_is_zero(&bd));
}
END_TEST

Suite *create_zero_suite() {
  Suite *suite = suite_create("zero tests");
  TCase *tc = tcase_create("zero");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  suite_add_tcase(suite, tc);

  return suite;
}
