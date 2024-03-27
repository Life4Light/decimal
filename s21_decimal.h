#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#define BIG_DECIMAL_SIZE (int)(sizeof(s21_big_decimal) / sizeof(unsigned))
#define DECIMAL_SIZE (int)(sizeof(s21_decimal) / sizeof(unsigned))
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 0
#define NUMBER_TOO_LARGE 1
#define NUMBER_TOO_LOW 2
#define INDEX_ERROR 2
#define OVERFLOW_ERROR 1
#define CALCULATION_ERROR 1
#define CONVERTATION_ERROR 1
#define DIVIZION_BY_ZERO = 3,

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

unsigned s21_big_set_sign(s21_big_decimal *dec, int sign);
unsigned s21_big_get_sign(const s21_big_decimal *dec);
bool s21_big_is_zero(s21_big_decimal *dec);
unsigned s21_big_set_zero(s21_big_decimal *dec);
unsigned s21_is_zero(const s21_decimal *dec);
unsigned s21_big_get_scale(const s21_big_decimal *dec);
unsigned s21_big_set_scale(s21_big_decimal *dec, int scale);
unsigned s21_big_set_bit(s21_big_decimal *dec, int bit, int index);
unsigned s21_big_get_bit(const s21_big_decimal *dec, int index);
unsigned s21_set_sign(s21_decimal *dec, int sign);
unsigned s21_get_sign(const s21_decimal *dec);
unsigned s21_get_scale(const s21_decimal *dec);
unsigned s21_set_scale(s21_decimal *dec, int scale);
unsigned s21_set_bit(s21_decimal *dec, int bit, int index);
unsigned s21_get_bit(const s21_decimal *dec, int index);
int s21_copy(s21_decimal dec, s21_decimal *result);
int get_first_non_zero_bit(const s21_big_decimal decimal);
int s21_get_first_bit(const s21_big_decimal *num);
void set_zero(s21_big_decimal *val1);
void s21_reset_to_zero(s21_decimal *number);
void s21_big_reset_to_zero(s21_big_decimal *number);
int s21_big_is_equal(s21_big_decimal dec1, s21_big_decimal dec2);
void left_align(s21_big_decimal *dec, int expected_scale);
void right_align(s21_big_decimal *dec, int expected_scale);
void s21_move_to_expected_align(s21_big_decimal *dec, int expected_scale);
void s21_normalization(s21_big_decimal *dec1, s21_big_decimal *dec2);
bool high_byte_is_zero(s21_big_decimal decimal);
int check_overflow(s21_big_decimal decimal);
int correction(s21_big_decimal *decimal);
int s21_bitwise_add(const s21_big_decimal first_number,
                    const s21_big_decimal second_number,
                    s21_big_decimal *result);
int s21_bitwise_division(s21_big_decimal divisible, s21_big_decimal divider,
                         s21_big_decimal *result, s21_big_decimal *remainder);
void s21_sub_shift_right(s21_big_decimal *dec, const int shift_value);
void s21_shift_right(s21_big_decimal *dec, const int shift_value);
void s21_sub_shift_left(s21_big_decimal *dec, const int shift_value);
void s21_shift_left(s21_big_decimal *dec, const int shift_value);
s21_big_decimal s21_bitwise_negation(s21_big_decimal decimal);
int s21_bitwise_sub(s21_big_decimal minuend, s21_big_decimal subtrahend,
                    s21_big_decimal *result);
int decimal_to_big_decimal(const s21_decimal *source,
                           s21_big_decimal *destination);
int big_decimal_to_decimal(const s21_big_decimal *source,
                           s21_decimal *destination);
int s21_convert_from_big_decimal(const s21_big_decimal *source,
                                 s21_decimal *destination);

int s21_convert_to_big_decimal(const s21_decimal *source,
                               s21_big_decimal *destination);

int compare(s21_decimal dec1, s21_decimal dec2);
int s21_mul_big_decimal(s21_big_decimal val1, s21_big_decimal val2,
                        s21_big_decimal *res);
#endif  // S21_DECIMAL_H