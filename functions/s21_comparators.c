#include "../s21_decimal.h"

int s21_is_less(s21_decimal first_number, s21_decimal second_number) {
  return compare(first_number, second_number) == -1;
}
int s21_is_less_or_equal(s21_decimal first_number, s21_decimal second_number) {
  return compare(first_number, second_number) <= 0;
}

int s21_is_greater(s21_decimal first_number, s21_decimal second_number) {
  return compare(first_number, second_number) == 1;
}
int s21_is_greater_or_equal(s21_decimal first_number,
                            s21_decimal second_number) {
  return compare(first_number, second_number) >= 0;
}

int s21_is_equal(s21_decimal first_number, s21_decimal second_number) {
  return compare(first_number, second_number) == 0;
}

int s21_is_not_equal(s21_decimal first_number, s21_decimal second_number) {
  return compare(first_number, second_number) != 0;
}

int compare(s21_decimal dec1, s21_decimal dec2) {
  s21_big_decimal big_dec1 = {0};
  s21_big_decimal big_dec2 = {0};

  s21_convert_to_big_decimal(&dec1, &big_dec1);
  s21_convert_to_big_decimal(&dec2, &big_dec2);

  int first_sign = s21_big_get_sign(&big_dec1);
  int second_sign = s21_big_get_sign(&big_dec2);
  int res_sign = first_sign == 0 ? 1 : -1;
  s21_normalization(&big_dec1, &big_dec2);

  if (s21_big_is_zero(&big_dec1) && s21_big_is_zero(&big_dec2)) {
    return 0;
  }

  if (first_sign == 1 && second_sign == 0) {
    return -1;
  } else if (first_sign == 0 && second_sign == 1) {
    return 1;
  }

  for (int i = BIG_DECIMAL_SIZE - 1; i >= 0; i--) {
    if (big_dec1.bits[i] > big_dec2.bits[i]) {
      return 1 * res_sign;
    } else if (big_dec1.bits[i] < big_dec2.bits[i]) {
      return -1 * res_sign;
    }
  }
  return 0;
}