#include "../s21_decimal.h"

s21_big_decimal s21_bitwise_negation(s21_big_decimal decimal) {
  for (int i = 0; i < BIG_DECIMAL_SIZE - 1; i++) {
    decimal.bits[i] = ~decimal.bits[i];
  }
  return decimal;
}