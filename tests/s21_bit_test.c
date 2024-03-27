#include "s21_decimal_test.h"

START_TEST(test_1) {
  s21_big_decimal dec = {};
  dec.bits[0] |= 1 << 3;
  ck_assert_int_eq(s21_big_get_bit(&dec, 3), 1);
}
END_TEST

START_TEST(test_2) {
  s21_big_decimal dec = {};
  dec.bits[0] |= 1;
  ck_assert_int_eq(s21_big_get_bit(&dec, 0), 1);
}
END_TEST

START_TEST(test_3) {
  s21_big_decimal dec = {};
  dec.bits[1] |= 1;
  ck_assert_int_eq(s21_big_get_bit(&dec, 32), 1);
}
END_TEST

START_TEST(test_4) {
  s21_big_decimal dec = {};
  ck_assert_int_eq(s21_big_get_bit(&dec, 9999), 2);
}
END_TEST

START_TEST(test_5) {
  s21_big_decimal dec = {};
  dec.bits[sizeof(s21_big_decimal) / sizeof(unsigned) - 3] |= 1;
  ck_assert_int_eq(s21_big_get_bit(&dec, 30), 0);
}
END_TEST

START_TEST(test_6) {
  s21_big_decimal dec = {};
  s21_big_set_bit(&dec, 1, 1);
  ck_assert_int_eq(s21_big_get_bit(&dec, 1), 1);
}
END_TEST

START_TEST(test_7) {
  s21_big_decimal dec = {};
  s21_big_set_bit(&dec, 1, 0);
  ck_assert_int_eq(s21_big_get_bit(&dec, 1), 0);
}
END_TEST

START_TEST(test_8) {
  s21_big_decimal dec = {};
  s21_big_set_bit(&dec, 1, 40);
  ck_assert_int_eq(s21_big_get_bit(&dec, 40), 1);
}
END_TEST

START_TEST(test_9) {
  s21_big_decimal dec = {};
  s21_big_set_bit(&dec, 1, 40);
  s21_big_set_bit(&dec, 0, 40);
  ck_assert_int_eq(s21_big_get_bit(&dec, 40), 0);
}
END_TEST

START_TEST(test_10) {
  s21_big_decimal dec = {};
  ck_assert_int_eq(s21_big_set_bit(&dec, 1, 10000), 2);
}
END_TEST

START_TEST(test_11) {
  s21_decimal dec = {};
  dec.bits[0] = 1 << 3;
  ck_assert_int_eq(s21_get_bit(&dec, 3), 1);
}
END_TEST

START_TEST(test_12) {
  s21_decimal dec = {};
  dec.bits[0] = 1;
  ck_assert_int_eq(s21_get_bit(&dec, 0), 1);
}
END_TEST

START_TEST(test_13) {
  s21_decimal dec = {};
  dec.bits[sizeof(s21_decimal) / sizeof(unsigned) - 3] |= 1;
  ck_assert_int_eq(s21_get_bit(&dec, 32), 1);
}
END_TEST

START_TEST(test_14) {
  s21_decimal dec = {};
  ck_assert_int_eq(s21_get_bit(&dec, 9999), 2);
}
END_TEST

START_TEST(test_15) {
  s21_decimal dec = {};
  dec.bits[sizeof(s21_decimal) / sizeof(unsigned) - 3] |= 1;
  ck_assert_int_eq(s21_get_bit(&dec, 30), 0);
}
END_TEST

START_TEST(test_16) {
  s21_decimal dec = {};
  s21_set_bit(&dec, 1, 1);
  ck_assert_int_eq(s21_get_bit(&dec, 1), 1);
}
END_TEST

START_TEST(test_17) {
  s21_decimal dec = {};
  s21_set_bit(&dec, 1, 0);
  ck_assert_int_eq(s21_get_bit(&dec, 1), 0);
}
END_TEST

START_TEST(test_18) {
  s21_decimal dec = {};
  s21_set_bit(&dec, 1, 40);
  ck_assert_int_eq(s21_get_bit(&dec, 40), 1);
}
END_TEST

START_TEST(test_19) {
  s21_decimal dec = {};
  s21_set_bit(&dec, 1, 40);
  s21_set_bit(&dec, 0, 40);
  ck_assert_int_eq(s21_get_bit(&dec, 40), 0);
}
END_TEST

START_TEST(test_20) {
  s21_decimal dec = {};
  ck_assert_int_eq(s21_set_bit(&dec, 1, 10000), 2);
}
END_TEST

Suite *create_bit_suite() {
  Suite *suite = suite_create("set_get bit tests");
  TCase *tc = tcase_create("bit test");
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
  tcase_add_test(tc, test_13);
  tcase_add_test(tc, test_14);
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);

  suite_add_tcase(suite, tc);

  return suite;
}
