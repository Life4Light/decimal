#include "../s21_decimal.h"

int s21_bitwise_add(const s21_big_decimal first_number,
                    const s21_big_decimal second_number,
                    s21_big_decimal *result) {
  s21_big_reset_to_zero(result);
  unsigned long transfer = 0;
  for (int i = 0; i < BIG_DECIMAL_SIZE - 1; ++i) {
    unsigned long temp = (unsigned long)first_number.bits[i] +
                         (unsigned long)second_number.bits[i] +
                         (unsigned long)transfer;
    transfer = temp >> (sizeof(unsigned) * 8);
    temp -= transfer << (sizeof(unsigned) * 8 + 1);
    result->bits[i] = temp;
  }
  return transfer;
}