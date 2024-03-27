
#include "s21_decimal_test.h"
START_TEST(right_shift_test_1) {
  s21_big_decimal decimal = {0b1111, 0, 0, 0, 0, 0, 0, 0};
  s21_shift_right(&decimal, 2);
  const s21_big_decimal expected = {0b11, 0, 0, 0, 0, 0, 0, 0};
  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(right_shift_test_2) {
  s21_big_decimal decimal = {0, 0b1111, 0, 0, 0, 0, 0, 0};
  s21_shift_right(&decimal, 2);
  const s21_big_decimal expected = {0b11 << 30, 0b11, 0, 0, 0, 0, 0, 0};
  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(right_shift_test_3) {
  s21_big_decimal decimal = {0b1111, 0, 0, 0, 0, 0, 0, 0};
  s21_big_set_scale(&decimal, 10);
  s21_shift_right(&decimal, 4);
  s21_big_decimal expected = {0, 0, 0, 0, 0, 0, 0, 0};
  s21_big_set_scale(&expected, 10);
  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(right_shift_test_4) {
  s21_big_decimal decimal = {0, 0, 0b111, 0, 0, 0, 0, 0};
  s21_big_set_scale(&decimal, 10);
  s21_shift_right(&decimal, 66);
  s21_big_decimal expected = {0b1, 0, 0, 0, 0, 0, 0, 0};
  s21_big_set_scale(&expected, 10);
  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(left_shift_test_1) {
  s21_big_decimal decimal = {0b1111, 0, 0, 0, 0, 0, 0, 0};
  s21_shift_left(&decimal, 30);
  const s21_big_decimal expected = {0b11 << 30, 0b11, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(left_shift_test_2) {
  s21_big_decimal decimal = {0b1111, 0, 0, 0, 0, 0, 0, 0};
  s21_shift_left(&decimal, 4);
  const s21_big_decimal expected = {0b1111 << 4, 0, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(left_shift_test_3) {
  s21_big_decimal decimal = {0, 0, 0, 0, 0, 0, 0b1111, 0};
  s21_shift_left(&decimal, 30);
  const s21_big_decimal expected = {0, 0, 0, 0, 0, 0, 0b1111 << 30, 0};

  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(left_shift_test_4) {
  s21_big_decimal decimal = {0b111, 0, 0, 0, 0, 0, 0, 0};
  s21_shift_left(&decimal, 66);
  const s21_big_decimal expected = {0, 0, 0b111 << 2, 0, 0, 0, 0, 0};

  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

START_TEST(left_shift_test_5) {
  s21_big_decimal decimal = {10, 0, 0, 0, 0, 0, 0, 0};
  const s21_big_decimal expected = {0, 0, 0b01 << 30, 0b1, 0, 0, 0, 0};

  s21_shift_left(&decimal, 93);

  ck_assert(s21_big_is_equal(decimal, expected) == TRUE);
}
END_TEST

Suite *create_shifts_suite() {
  Suite *suite = suite_create("shifts tests");
  TCase *rigth_shift_tc = tcase_create("rigth_shift_test_case");
  tcase_add_test(rigth_shift_tc, right_shift_test_1);
  tcase_add_test(rigth_shift_tc, right_shift_test_2);
  tcase_add_test(rigth_shift_tc, right_shift_test_3);
  tcase_add_test(rigth_shift_tc, right_shift_test_4);

  TCase *left_shift_tc = tcase_create("left_shift_test_case");
  tcase_add_test(left_shift_tc, left_shift_test_1);
  tcase_add_test(left_shift_tc, left_shift_test_2);
  tcase_add_test(left_shift_tc, left_shift_test_3);
  tcase_add_test(left_shift_tc, left_shift_test_4);
  tcase_add_test(left_shift_tc, left_shift_test_5);

  suite_add_tcase(suite, left_shift_tc);
  suite_add_tcase(suite, rigth_shift_tc);

  return suite;
}
