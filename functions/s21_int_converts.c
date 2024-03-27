#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_reset_to_zero(dst);
  if (src < 0) {
    s21_set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  return OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_truncate(src, &src);
  int int_overflow = FALSE;
  for (int i = 1; i < DECIMAL_SIZE - 1 && !int_overflow; i++) {
    if (src.bits[i] != 0) {
      int_overflow = 1;
    }
  }
  int sign = s21_get_sign(&src);
  if (int_overflow || (sign == 1 && src.bits[0] > (unsigned)INT_MAX + 1) ||
      (sign == 0 && src.bits[0] > INT_MAX)) {
    int_overflow = TRUE;
  } else {
    *dst = src.bits[0] * (sign == 1 ? -1 : 1);
  }
  return int_overflow ? CONVERTATION_ERROR : OK;
}