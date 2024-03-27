#include "../s21_decimal.h"

void banking_round(s21_big_decimal *decimal);
bool is_overflow(s21_big_decimal decimal);
int get_fractional_part(s21_big_decimal *result, s21_big_decimal *remainder,
                        s21_big_decimal divider);
void scale_correction(int *scale, s21_big_decimal *decimal);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_zero(&value_2)) return 3;
  if (s21_is_zero(&value_1)) {
    s21_reset_to_zero(result);
    return OK;
  }
  s21_big_decimal big_divisible = {{0}};
  s21_convert_to_big_decimal(&value_1, &big_divisible);
  s21_big_decimal big_divider = {{0}};
  s21_convert_to_big_decimal(&value_2, &big_divider);
  s21_big_decimal bitwise_division_result = {{0}};
  s21_big_decimal bitwise_division_remainder = {{0}};
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};

  s21_bitwise_division(big_divisible, big_divider, &bitwise_division_result,
                       &bitwise_division_remainder);
  int frac_scale = get_fractional_part(
      &bitwise_division_result, &bitwise_division_remainder, big_divider);
  int scale = s21_get_scale(&value_1) - s21_get_scale(&value_2);
  if (scale < 0) {
    s21_big_decimal multiplier = {{0}};
    multiplier.bits[0] = 1;

    while (scale != 0) {
      s21_mul_big_decimal(multiplier, ten, &multiplier);
      scale++;
    }
    s21_mul_big_decimal(bitwise_division_result, multiplier,
                        &bitwise_division_result);
  }
  scale += frac_scale;
  scale_correction(&scale, &bitwise_division_result);
  s21_big_set_scale(&bitwise_division_result, scale);

  int sign = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
  s21_big_set_sign(&bitwise_division_result, sign);

  const int check = check_overflow(bitwise_division_result);
  if (check == OK) {
    correction(&bitwise_division_result);
    s21_convert_from_big_decimal(&bitwise_division_result, result);
  }

  return check;
}

int get_fractional_part(s21_big_decimal *result, s21_big_decimal *remainder,
                        s21_big_decimal divider) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal new_number = {{0}};
  int scale = 0;
  s21_mul_big_decimal(*result, ten, result);
  while (result->bits[3] == 0 && !s21_big_is_zero(remainder)) {
    s21_mul_big_decimal(*remainder, ten, remainder);
    s21_big_reset_to_zero(&new_number);
    s21_bitwise_division(*remainder, divider, &new_number, remainder);
    s21_bitwise_add(*result, new_number, result);
    s21_mul_big_decimal(*result, ten, result);
    scale++;
  }
  s21_mul_big_decimal(*remainder, ten, remainder);
  s21_big_reset_to_zero(&new_number);
  s21_bitwise_division(*remainder, divider, &new_number, remainder);
  s21_bitwise_add(*result, new_number, result);
  banking_round(result);
  return scale;
}

void scale_correction(int *scale, s21_big_decimal *decimal) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal remainder = {{0}};
  while (*scale > 28) {
    s21_bitwise_division(*decimal, ten, decimal, &remainder);
    if ((remainder.bits[0] == 5 && decimal->bits[0] % 2 == 1) ||
        remainder.bits[0] > 5) {
      s21_bitwise_add(*decimal, one, decimal);
    }
    (*scale)--;
  }
}

void banking_round(s21_big_decimal *decimal) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal remainder = {{0}};
  s21_bitwise_division(*decimal, ten, decimal, &remainder);
  if ((remainder.bits[0] == 5 && decimal->bits[0] % 2 == 1) ||
      remainder.bits[0] > 5) {
    s21_bitwise_add(*decimal, one, decimal);
  }
}