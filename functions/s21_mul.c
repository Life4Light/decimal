#include "../s21_decimal.h"

int s21_mul_big_decimal(s21_big_decimal val1, s21_big_decimal val2,
                        s21_big_decimal *res) {
  s21_big_reset_to_zero(res);
  int second_bit = s21_get_first_bit(&val2);
  for (int i = second_bit; i >= 0; i--) {
    if (s21_big_get_bit(&val2, i)) {
      s21_bitwise_add(*res, val1, res);
    }
    if (i != 0) {
      s21_shift_left(res, 1);
    }
  }
  return OK;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = OK;
  s21_big_decimal res = {{0}};
  s21_big_decimal val1 = {{0}};
  s21_big_decimal val2 = {{0}};

  s21_convert_to_big_decimal(&value_1, &val1);
  s21_convert_to_big_decimal(&value_2, &val2);
  int scale = (int)(s21_big_get_scale(&val1) + s21_big_get_scale(&val2));

  if (scale > 28) {
    return NUMBER_TOO_LOW;
  } else {
    s21_mul_big_decimal(val1, val2, &res);
  }
  int first_bit_in_res = s21_get_first_bit(&res);
  int sign = (int)s21_big_get_sign(&val1) ^ (int)s21_big_get_sign(&val2);

  if (first_bit_in_res >=
          ((int)(sizeof(s21_decimal) / sizeof(unsigned) - 1) * 32) &&
      ret == OK) {
    if (sign) {
      return NUMBER_TOO_LOW;
    } else {
      return NUMBER_TOO_LARGE;
    }
  }
  if (ret == OK) {
    s21_big_set_sign(&res, sign);
    s21_big_set_scale(&res, scale);
    s21_convert_from_big_decimal(&res, result);
  } else {
    set_zero(&res);
  }

  return ret;
}