
#include "s21_decimal_test.h"

START_TEST(bitwise_subtraction_test_1) {
  s21_big_decimal minuend = {0b11 << 30, 0b10, 0, 0, 0, 0, 0, 0};
  s21_big_decimal subtrahend = {0b11 << 30, 0b1, 0, 0, 0, 0, 0, 0};
  s21_big_decimal result;
  s21_big_reset_to_zero(&result);
  s21_big_decimal expected_result = {0, 1, 0, 0, 0, 0, 0, 0};

  ck_assert(s21_bitwise_sub(minuend, subtrahend, &result) == OK);
  ck_assert(s21_big_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(bitwise_subtraction_test_2) {
  s21_big_decimal minuend = {0, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal subtrahend = {1, 0, 0, 0, 0, 0, 0, 0};
  s21_big_decimal result;
  s21_big_reset_to_zero(&result);

  ck_assert(s21_bitwise_sub(minuend, subtrahend, &result) == CALCULATION_ERROR);
}
END_TEST
START_TEST(bitwise_subtraction_test_3) {
  s21_big_decimal minuend = {0, 0, 0, 0, 0, 0, 0b1 << 30, 0};
  s21_big_decimal subtrahend = {0, 0, 0, 0, 0, 0, 0b1 << 31, 0};
  s21_big_decimal result;
  s21_big_reset_to_zero(&result);

  ck_assert(s21_bitwise_sub(minuend, subtrahend, &result) == CALCULATION_ERROR);
}
END_TEST

START_TEST(bitwise_subtraction_test_4) {
  // 265337593543950335
  s21_big_decimal minuend = {0b10110000101111100111111111111111,
                             0b11101011101010101100100010,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0};
  // 2653375935439503
  s21_big_decimal subtrahend = {0b00111010000101100110001010001111,
                                0b10010110110100111011,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0};
  // 262684217608510832
  s21_big_decimal expected_result = {0b01110110101010000001110101110000,
                                     0b11101001010011110111100111,
                                     0,
                                     0,
                                     0,
                                     0,
                                     0,
                                     0};
  s21_big_decimal result;
  s21_big_reset_to_zero(&result);

  ck_assert(s21_bitwise_sub(minuend, subtrahend, &result) == OK);
  ck_assert(s21_big_is_equal(result, expected_result) == TRUE);
}
END_TEST

START_TEST(bitwise_subtraction_test_5) {
  // 265337593543950335
  s21_big_decimal minuend = {0b0, 0b10, 0, 0, 0, 0, 0, 0};
  // 2653375935439503
  s21_big_decimal subtrahend = {0b1 << 31, 0b10, 0, 0, 0, 0, 0, 0};

  s21_big_decimal result;
  ck_assert(s21_bitwise_sub(minuend, subtrahend, &result) == CALCULATION_ERROR);
}
END_TEST

Suite *create_bitwise_operations_suite() {
  Suite *suite = suite_create("bitwise_operations_tests_suite");

  TCase *bitwise_subtraction_test_case =
      tcase_create("bitwise_subtraction_test_case");
  tcase_add_test(bitwise_subtraction_test_case, bitwise_subtraction_test_1);
  tcase_add_test(bitwise_subtraction_test_case, bitwise_subtraction_test_2);
  tcase_add_test(bitwise_subtraction_test_case, bitwise_subtraction_test_3);
  tcase_add_test(bitwise_subtraction_test_case, bitwise_subtraction_test_4);
  tcase_add_test(bitwise_subtraction_test_case, bitwise_subtraction_test_5);
  suite_add_tcase(suite, bitwise_subtraction_test_case);
  return suite;
}
