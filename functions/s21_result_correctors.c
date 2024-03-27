#include "../s21_decimal.h"

bool high_byte_is_zero(s21_big_decimal decimal) {
  bool result = true;
  for (int i = DECIMAL_SIZE - 1; i < BIG_DECIMAL_SIZE - 1 && result; i++) {
    if (decimal.bits[i] != 0) {
      result = false;
    }
  }
  return result;
}
int check_overflow(s21_big_decimal decimal) {
  int check = OK;

  s21_move_to_expected_align(&decimal, 0);
  if (!high_byte_is_zero(decimal)) {
    const int sign = s21_big_get_sign(&decimal);
    if (sign == 1)
      check = NUMBER_TOO_LOW;
    else
      check = NUMBER_TOO_LARGE;
  }
  return check;
}

int correction(s21_big_decimal *decimal) {
  int sign = s21_big_get_sign(decimal);
  s21_big_decimal divider = {{0}};
  s21_big_reset_to_zero(&divider);
  divider.bits[0] = 10;

  s21_big_decimal one = {{0}};
  one.bits[0] = 1;

  s21_big_decimal remainder = {{0}};

  int scale = s21_big_get_scale(decimal);
  while (!high_byte_is_zero(*decimal) && scale >= 0) {
    s21_bitwise_division(*decimal, divider, decimal, &remainder);
    if (remainder.bits[0] > 5 ||
        (remainder.bits[0] == 5 && decimal->bits[0] % 2 == 1)) {
      s21_bitwise_add(*decimal, one, decimal);
    }
    scale--;
  }
  s21_big_set_scale(decimal, scale);
  s21_big_set_sign(decimal, sign);
  return OK;
}