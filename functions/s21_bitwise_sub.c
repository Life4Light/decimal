#include "../s21_decimal.h"

int s21_bitwise_sub(s21_big_decimal minuend, s21_big_decimal subtrahend,
                    s21_big_decimal *result) {
  bool borrow = false;
  s21_big_reset_to_zero(result);
  for (int i = 0; i < BIG_DECIMAL_SIZE - 1; ++i) {
    long unsigned temp = 0;
    if (borrow) {
      temp--;
    }
    if (minuend.bits[i] == 0 && borrow)
      borrow = true;
    else if ((unsigned long)minuend.bits[i] + temp <
             (unsigned long)subtrahend.bits[i]) {
      temp += ((unsigned long)1 << sizeof(unsigned) * 8);
      borrow = true;
    } else
      borrow = false;
    temp += (unsigned long)minuend.bits[i] - (unsigned long)subtrahend.bits[i];
    result->bits[i] = temp;
  }
  if (borrow)
    return CALCULATION_ERROR;
  else
    return OK;
}