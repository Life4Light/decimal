#include "../s21_decimal.h"

void left_align(s21_big_decimal *dec, int expected_scale) {
  const int sign = s21_big_get_sign(dec);
  int current_scale = s21_big_get_scale(dec);
  while (current_scale != expected_scale) {
    s21_big_decimal triple_shift = *dec;
    s21_big_decimal single_shift = *dec;
    s21_shift_left(&triple_shift, 3);
    s21_shift_left(&single_shift, 1);
    s21_bitwise_add(single_shift, triple_shift, dec);
    current_scale++;
  }
  s21_big_set_scale(dec, current_scale);
  s21_big_set_sign(dec, sign);
}

void right_align(s21_big_decimal *dec, int expected_scale) {
  const int sign = s21_big_get_sign(dec);
  int current_scale = s21_big_get_scale(dec);
  s21_big_decimal ten = {{0}};
  ten.bits[0] = 10;
  s21_big_decimal remainder = {{0}};
  while (current_scale != expected_scale) {
    s21_bitwise_division(*dec, ten, dec, &remainder);
    current_scale--;
  }
  s21_big_set_scale(dec, current_scale);
  s21_big_set_sign(dec, sign);
}

void s21_move_to_expected_align(s21_big_decimal *dec, int expected_scale) {
  const int current_scale = s21_big_get_scale(dec);
  if (current_scale < expected_scale)
    left_align(dec, expected_scale);
  else if (current_scale > expected_scale)
    right_align(dec, expected_scale);
}
void s21_normalization(s21_big_decimal *dec1, s21_big_decimal *dec2) {
  const int first_scale = s21_big_get_scale(dec1);
  const int second_scale = s21_big_get_scale(dec2);
  const int scale = first_scale > second_scale ? first_scale : second_scale;
  s21_move_to_expected_align(dec1, scale);
  s21_move_to_expected_align(dec2, scale);
}