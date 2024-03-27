#include "../s21_decimal.h"

void get_float_params(const char *since_notation, int *float_mantissa,
                      int *float_scale);
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  char since_notation[20];
  sprintf(since_notation, "%E", src);
  int float_mantissa;
  int float_scale;

  get_float_params(since_notation, &float_mantissa, &float_scale);

  s21_reset_to_zero(dst);
  if (since_notation[0] == '-') s21_set_sign(dst, 1);
  dst->bits[0] = float_mantissa;

  int scale = 6 - float_scale;
  bool error = false;
  if (scale > 34) {
    s21_reset_to_zero(dst);
    error = true;
  }
  if (scale < 0) {
    s21_decimal multiplier_ten = {{10, 0, 0, 0}};

    while (scale != 0 && !error) {
      if (s21_mul(multiplier_ten, *dst, dst) != OK) error = true;
      scale++;
    }
  }
  s21_set_scale(dst, scale);
  return error ? CONVERTATION_ERROR : OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double result = 0;

  for (int i = 0; i < (int)((DECIMAL_SIZE - 1) * sizeof(unsigned) * 8); i++) {
    if (s21_get_bit(&src, i) == 1) result += pow(2.0, i);
  }

  int scale = s21_get_scale(&src);
  result /= pow(10, scale);

  *dst = s21_get_sign(&src) == 1 ? -(float)result : (float)result;
  return OK;
}

void get_float_params(const char *since_notation, int *float_mantissa,
                      int *float_scale) {
  *float_mantissa = 0;
  int i = 0;
  while (i < 7) {
    if (*since_notation >= 48 && *since_notation <= 57) {
      *float_mantissa += pow(10, 7 - i - 1) * (*since_notation - 48);
      i++;
    }
    since_notation++;
  }
  since_notation++;
  *float_scale = atoi(since_notation);
  if (*float_scale <= -23 && *float_scale >= -28) {
    int shift = -(22 + *float_scale);
    while (shift != 0) {
      *float_mantissa = round((double)*float_mantissa / 10);
      shift--;
      (*float_scale)++;
    }
  }
}