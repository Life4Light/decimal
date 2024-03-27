#include "s21_decimal_test.h"
void assert(s21_big_decimal first, s21_big_decimal second) {
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
    ck_assert_uint_eq(first.bits[i], second.bits[i]);
  }
}
START_TEST(normalizaion_test_1) {
  s21_big_decimal first_value = {{0}};
  s21_big_decimal second_value = {{0}};
  // 0.68985125146545154
  // 0.6898512514654515400000000000;

  first_value.bits[0] = 0x65CDD000;
  first_value.bits[1] = 0xC3ED89B9;
  first_value.bits[2] = 0x164A50D8;

  second_value.bits[0] = 0x17254C02;
  second_value.bits[1] = 0xF5159B;
  second_value.bits[2] = 0x0;
  ;

  s21_big_set_scale(&first_value, 28);
  s21_big_set_scale(&second_value, 17);
  s21_normalization(&first_value, &second_value);
  assert(first_value, second_value);
}
END_TEST
Suite *create_normalizaion_suite() {
  Suite *suite = suite_create("normalizaion tests");
  TCase *tc = tcase_create("normalizaion");
  tcase_add_test(tc, normalizaion_test_1);

  suite_add_tcase(suite, tc);

  return suite;
}