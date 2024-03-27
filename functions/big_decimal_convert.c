#include "../s21_decimal.h"

int s21_convert_to_big_decimal(const s21_decimal *source,
                               s21_big_decimal *destination) {
  int decimal_length = sizeof(s21_decimal) / sizeof(unsigned);
  int big_decimal_length = sizeof(s21_big_decimal) / sizeof(unsigned);
  for (int i = 0; i < decimal_length - 1; ++i) {
    destination->bits[i] = source->bits[i];
  }
  destination->bits[big_decimal_length - 1] = source->bits[decimal_length - 1];
  return OK;
}

int s21_convert_from_big_decimal(const s21_big_decimal *source,
                                 s21_decimal *destination) {
  int decimal_length = sizeof(s21_decimal) / sizeof(unsigned);
  int big_decimal_length = sizeof(s21_big_decimal) / sizeof(unsigned);
  // int length_difference = big_decimal_length - decimal_length;
  for (int i = decimal_length - 1; i < big_decimal_length - 1; ++i) {
    if (source->bits[i] != 0) return CONVERTATION_ERROR;
  }
  for (int i = 0; i < decimal_length - 1; ++i) {
    destination->bits[i] = source->bits[i];
  }
  destination->bits[decimal_length - 1] = source->bits[big_decimal_length - 1];
  return OK;
}