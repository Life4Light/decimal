#include "../s21_decimal.h"

int s21_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *result) {
  s21_negate(dec2, &dec2);
  return s21_add(dec1, dec2, result);
}