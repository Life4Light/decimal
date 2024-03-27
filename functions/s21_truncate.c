#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_reset_to_zero(result);
  s21_big_decimal big_value = {{0}};
  s21_convert_to_big_decimal(&value, &big_value);
  s21_move_to_expected_align(&big_value, 0);
  return s21_convert_from_big_decimal(&big_value, result);
}