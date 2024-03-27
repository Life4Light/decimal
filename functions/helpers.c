#include "../s21_decimal.h"
unsigned s21_big_set_sign(s21_big_decimal *dec, int sign) {
  if (sign) {
    dec->bits[(int)sizeof(s21_big_decimal) / sizeof(unsigned) - 1] |=
        (0b1 << 31);
  } else {
    dec->bits[(int)sizeof(s21_big_decimal) / sizeof(unsigned) - 1] &=
        ~(0b1 << 31);
  }
  return OK;
}

unsigned s21_big_get_sign(const s21_big_decimal *dec) {
  unsigned int ret =
      dec->bits[(int)sizeof(s21_big_decimal) / sizeof(unsigned) - 1] >> 31;
  return ret;
}

bool s21_big_is_zero(s21_big_decimal *dec) {
  int is_zero = TRUE;
  int sign = s21_big_get_sign(dec);
  s21_big_set_sign(dec, 0);
  for (int i = 0; i < (int)(sizeof(*dec) / sizeof(unsigned)) - 1; i++) {
    if (dec->bits[i] != 0) {
      is_zero = FALSE;
    }
  }
  s21_big_set_sign(dec, sign);
  return is_zero;
}

unsigned s21_big_set_zero(s21_big_decimal *dec) {
  for (int i = 0; i < (int)(sizeof(*dec) / sizeof(unsigned)); i++) {
    dec->bits[i] = 0;
  }
  return OK;
}

unsigned s21_is_zero(const s21_decimal *dec) {
  int is_zero = TRUE;
  for (int i = 0; i < (int)(sizeof(*dec) / sizeof(unsigned)); i++) {
    if (dec->bits[i] != 0) {
      is_zero = FALSE;
    }
  }
  return is_zero;
}

unsigned s21_big_get_scale(const s21_big_decimal *dec) {
  return (dec->bits[7] >> 16) & 0b11111111;
}

unsigned s21_big_set_scale(s21_big_decimal *dec, int scale) {
  if (scale > 28 || scale < 0) {
    return CALCULATION_ERROR;
  }
  int sign = s21_big_get_sign(dec);
  dec->bits[7] = 0;
  dec->bits[7] |= scale << 16;
  s21_big_set_sign(dec, sign);
  return OK;
}

unsigned s21_big_set_bit(s21_big_decimal *dec, int bit, int index) {
  if (index < 0 || index > (int)(sizeof(*dec) / sizeof(unsigned)) * 32) {
    return INDEX_ERROR;
  }
  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;

  if (bit) {
    dec->bits[bucket] |= 1U << pos;
  } else {
    dec->bits[bucket] &= ~(1U << pos);
  }
  return OK;
}

unsigned s21_big_get_bit(const s21_big_decimal *dec, int index) {
  if (index < 0 || index > (int)(sizeof(*dec) / sizeof(unsigned)) * 32) {
    return INDEX_ERROR;
  }
  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;
  return (dec->bits[bucket] >> pos) & 1U;
}

unsigned s21_set_sign(s21_decimal *dec, int sign) {
  if (!sign) {
    dec->bits[(int)sizeof(s21_decimal) / sizeof(unsigned) - 1] &= ~(0b1 << 31);
  } else {
    dec->bits[(int)sizeof(s21_decimal) / sizeof(unsigned) - 1] |= (0b1 << 31);
  }
  return OK;
}

unsigned s21_get_sign(const s21_decimal *dec) {
  unsigned int ret =
      ((dec->bits[(int)sizeof(s21_decimal) / sizeof(unsigned) - 1]) &
       (0b1 << 31)) > 0;
  return (int)ret;
}

unsigned s21_get_scale(const s21_decimal *dec) {
  return (dec->bits[3] >> 16) & 0b111111111;
}

unsigned s21_set_scale(s21_decimal *dec, int scale) {
  if (scale > 28 || scale < 0) {
    return 1;  // TODO: error code
  }
  int sign = s21_get_sign(dec);
  dec->bits[3] = 0;
  dec->bits[3] |= scale << 16;
  s21_set_sign(dec, sign);
  return OK;
}

unsigned s21_set_bit(s21_decimal *dec, int bit, int index) {
  if (index < 0 || index > (int)(sizeof(s21_decimal) - sizeof(unsigned)) * 32) {
    return INDEX_ERROR;
  }

  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;

  if (bit) {
    dec->bits[bucket] |= 1U << pos;
  } else {
    dec->bits[bucket] &= ~(1U << pos);
  }
  return OK;
}

unsigned s21_get_bit(const s21_decimal *dec, int index) {
  if (index < 0 || index > (int)(sizeof(s21_decimal) - sizeof(unsigned)) * 32) {
    return INDEX_ERROR;
  }

  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;
  return (dec->bits[bucket] >> pos) & 1U;
}

int s21_copy(s21_decimal dec, s21_decimal *result) {
  for (int i = 0; i < (int)(sizeof(s21_decimal) / sizeof(unsigned)); i++) {
    result->bits[i] = dec.bits[i];
  }
  return OK;
}

int get_first_non_zero_bit(const s21_big_decimal decimal) {
  int index = -1;
  for (int i = (sizeof(s21_big_decimal) - sizeof(unsigned)) * 8 - 1;
       i >= 0 && index == -1; i--) {
    if (s21_big_get_bit(&decimal, i) == 1) {
      index = i;
    }
  }
  return index;
}

int s21_get_first_bit(const s21_big_decimal *num) {
  int ret = 0;
  for (int i = (int)(sizeof(s21_big_decimal) / sizeof(unsigned) - 1) * 32 - 1;
       i >= 0 && ret == 0; i--) {
    if (s21_big_get_bit(num, i)) {
      ret = i;
    }
  }
  return ret;
}

void set_zero(s21_big_decimal *val1) {
  for (int i = 0; i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned)); i++) {
    val1->bits[i] = 0;
  }
}

void s21_reset_to_zero(s21_decimal *number) {
  for (int i = 0; i < DECIMAL_SIZE; ++i) {
    number->bits[i] = 0;
  }
}

void s21_big_reset_to_zero(s21_big_decimal *number) {
  for (int i = 0; i < BIG_DECIMAL_SIZE; ++i) {
    number->bits[i] = 0;
  }
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_copy(value, result);
  if (s21_get_sign(result) == 0) {
    s21_set_sign(result, 1);
  } else {
    s21_set_sign(result, 0);
  }
  return OK;
}

int s21_big_is_equal(s21_big_decimal dec1, s21_big_decimal dec2) {
  int result = TRUE;
  for (int i = 0;
       i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned)) && result != FALSE;
       ++i) {
    if (dec1.bits[i] != dec2.bits[i]) {
      result = FALSE;
    }
  }
  return result;
}