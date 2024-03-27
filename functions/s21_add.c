#include "../s21_decimal.h"
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = {0};
  s21_convert_to_big_decimal(&value_1, &big_value_1);

  s21_big_decimal big_value_2 = {0};
  s21_convert_to_big_decimal(&value_2, &big_value_2);

  s21_normalization(&big_value_1, &big_value_2);
  const unsigned scale = s21_big_get_scale(&big_value_1);
  s21_big_decimal big_result = {0};

  if (s21_big_get_sign(&big_value_1) == 1)
    big_value_1 = s21_bitwise_negation(big_value_1);
  if (s21_big_get_sign(&big_value_2) == 1)
    big_value_2 = s21_bitwise_negation(big_value_2);
  const int overflow = s21_bitwise_add(big_value_2, big_value_1, &big_result);
  const unsigned sign = s21_big_get_sign(&big_value_1) +
                        s21_big_get_sign(&big_value_2) + overflow;
  if (sign > 1) {
    s21_big_decimal unit;
    s21_big_reset_to_zero(&unit);
    unit.bits[0] = 0b1;
    s21_bitwise_add(big_result, unit, &big_result);
  }
  if (sign % 2 == 1) {
    big_result = s21_bitwise_negation(big_result);
  }
  s21_big_set_sign(&big_result, sign % 2);
  s21_big_set_scale(&big_result, scale);

  const int check = check_overflow(big_result);
  if (check == OK) {
    correction(&big_result);
    s21_convert_from_big_decimal(&big_result, result);
  }

  return check;
}