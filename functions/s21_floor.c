#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = OK;
  s21_decimal tr_number = {{0}};
  s21_decimal fractional_part = {{0}};
  s21_decimal compare_number = {{0}};
  s21_decimal one = {{0}};

  one.bits[0] = 1;
  compare_number.bits[0] = 5;
  s21_set_scale(&compare_number, 1);
  s21_truncate(value, &tr_number);
  s21_sub(value, tr_number, &fractional_part);

  s21_set_sign(&fractional_part, 0);
  if (s21_get_sign(&tr_number)) {
    err = s21_sub(tr_number, one, result);
  } else {
    err = s21_copy(tr_number, result);
  }
  return err;
}