
#include "s21_decimal_test.h"

START_TEST(bitwise_division_test_1) {
  s21_big_decimal divisible = {15, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal divider = {3, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal result;
  s21_big_decimal remainder;
  s21_big_reset_to_zero(&result);
  s21_big_reset_to_zero(&remainder);
  s21_big_decimal excepted_result = {5, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal excepted_remainder = {0, 0, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_bitwise_division(divisible, divider, &result, &remainder) ==
            OK);
  ck_assert(s21_big_is_equal(result, excepted_result) == TRUE);
  ck_assert(s21_big_is_equal(remainder, excepted_remainder) == TRUE);
}
END_TEST

START_TEST(bitwise_division_test_2) {
  s21_big_decimal divisible = {17, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal divider = {3, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal result;
  s21_big_decimal remainder;
  s21_big_reset_to_zero(&result);
  s21_big_reset_to_zero(&remainder);
  s21_big_decimal excepted_result = {5, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal excepted_remainder = {2, 0, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_bitwise_division(divisible, divider, &result, &remainder) ==
            OK);
  ck_assert(s21_big_is_equal(result, excepted_result) == TRUE);
  ck_assert(s21_big_is_equal(remainder, excepted_remainder) == TRUE);
}
END_TEST

START_TEST(bitwise_division_test_3) {
  s21_big_decimal divisible = {0, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal divider = {3, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal result;
  s21_big_decimal remainder;
  s21_big_reset_to_zero(&result);
  s21_big_reset_to_zero(&remainder);
  s21_big_decimal excepted_result = {0, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal excepted_remainder = {0, 0, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_bitwise_division(divisible, divider, &result, &remainder) ==
            OK);
  ck_assert(s21_big_is_equal(result, excepted_result) == TRUE);
  ck_assert(s21_big_is_equal(remainder, excepted_remainder) == TRUE);
}
END_TEST

START_TEST(bitwise_division_test_4) {
  // 265337593543950335
  s21_big_decimal divisible = {0b10110000101111100111111111111111,
                               0b11101011101010101100100010,
                               0,
                               0,
                               0,
                               0,
                               0,
                               0};

  // 2653375935439503
  s21_big_decimal divider = {0b00111010000101100110001010001111,
                             0b10010110110100111011,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0};

  s21_big_decimal result;
  s21_big_decimal remainder;
  s21_big_reset_to_zero(&result);
  s21_big_reset_to_zero(&remainder);

  s21_big_decimal excepted_result = {100, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal excepted_remainder = {35, 0, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_bitwise_division(divisible, divider, &result, &remainder) ==
            OK);
  ck_assert(s21_big_is_equal(result, excepted_result) == TRUE);
  ck_assert(s21_big_is_equal(remainder, excepted_remainder) == TRUE);
}
END_TEST

START_TEST(bitwise_division_test_5) {
  s21_big_decimal divisible = {10035, 0, 0, 0, 0, 0, 0};

  s21_big_decimal divider = {100, 0, 0, 0, 0, 0, 0, 0};
  s21_shift_left(&divisible, 30);
  s21_shift_left(&divider, 30);

  s21_big_decimal result;
  s21_big_decimal remainder;
  s21_big_reset_to_zero(&result);
  s21_big_reset_to_zero(&remainder);

  s21_big_decimal excepted_result = {100, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal excepted_remainder = {35, 0, 0, 0, 0, 0, 0, 0};
  s21_shift_left(&excepted_remainder, 30);
  ck_assert(s21_bitwise_division(divisible, divider, &result, &remainder) ==
            OK);
  ck_assert(s21_big_is_equal(result, excepted_result) == TRUE);
  ck_assert(s21_big_is_equal(remainder, excepted_remainder) == TRUE);
}
END_TEST

Suite *create_bitwise_division_suite() {
  Suite *suite = suite_create("bitwise_division_tests_suite");

  TCase *bitwise_division_test_case =
      tcase_create("bitwise_division_test_case");
  tcase_add_test(bitwise_division_test_case, bitwise_division_test_1);
  tcase_add_test(bitwise_division_test_case, bitwise_division_test_2);
  tcase_add_test(bitwise_division_test_case, bitwise_division_test_3);
  tcase_add_test(bitwise_division_test_case, bitwise_division_test_4);
  tcase_add_test(bitwise_division_test_case, bitwise_division_test_5);
  suite_add_tcase(suite, bitwise_division_test_case);
  return suite;
}