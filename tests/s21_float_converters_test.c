
#include "s21_decimal_test.h"
#define TOL 1e-7
START_TEST(float_to_decimal_test_1) {
  float number = 0.123456789;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {1234568, 0, 0, 0};
  s21_set_scale(&exptected_decimal, 7);

  ck_assert(s21_from_float_to_decimal(number, &decimal) == OK);
  ck_assert(s21_is_equal(decimal, exptected_decimal) == TRUE);
}
START_TEST(float_to_decimal_test_2) {
  float number = -0.00123456789;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {1234568, 0, 0, 0};
  s21_set_sign(&exptected_decimal, 1);
  s21_set_scale(&exptected_decimal, 9);

  ck_assert(s21_from_float_to_decimal(number, &decimal) == OK);
  ck_assert(s21_is_equal(decimal, exptected_decimal) == TRUE);
}
START_TEST(float_to_decimal_test_3) {
  float number = 1e-29;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {0, 0, 0, 0};

  ck_assert(s21_from_float_to_decimal(number, &decimal) == CONVERTATION_ERROR);
  ck_assert(s21_is_equal(decimal, exptected_decimal));
}
END_TEST
START_TEST(float_to_decimal_test_4) {
  float number = 7922817e22;
  s21_decimal decimal;
  // s21_decimal exptected_decimal = {0, 0, 0, 0};

  ck_assert(s21_from_float_to_decimal(number, &decimal) == CONVERTATION_ERROR);
}
START_TEST(float_to_decimal_test_5) {
  float number = -7922816e22;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {0x20000000, 0xB392B21A, 0xFFFFFF77, 0};
  s21_set_sign(&exptected_decimal, 1);
  ck_assert(s21_from_float_to_decimal(number, &decimal) == OK);
  ck_assert(s21_is_equal(decimal, exptected_decimal));
}
START_TEST(float_to_decimal_test_6) {
  float number = 123e-28;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {123, 0, 0, 0};
  s21_set_scale(&exptected_decimal, 28);

  ck_assert(s21_from_float_to_decimal(number, &decimal) == OK);
  ck_assert(s21_is_equal(decimal, exptected_decimal));
}
END_TEST
START_TEST(float_to_decimal_test_7) {
  float number = 1234567e-34;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {1, 0, 0, 0};
  s21_set_scale(&exptected_decimal, 28);

  ck_assert(s21_from_float_to_decimal(number, &decimal) == OK);
  ck_assert(s21_is_equal(decimal, exptected_decimal));
}
END_TEST
START_TEST(float_to_decimal_test_8) {
  float number = 1634567e-34;
  s21_decimal decimal;
  s21_decimal exptected_decimal = {2, 0, 0, 0};
  s21_set_scale(&exptected_decimal, 28);

  ck_assert(s21_from_float_to_decimal(number, &decimal) == OK);
  ck_assert(s21_is_equal(decimal, exptected_decimal));
}
END_TEST

START_TEST(decimal_to_float_test_1) {
  s21_decimal decimal = {123456789, 0, 0, 0};
  s21_set_scale(&decimal, 10);
  float expected_number = 123456789e-10;
  float number = 0;

  ck_assert(s21_from_decimal_to_float(decimal, &number) == OK);
  ck_assert_double_eq_tol(number, expected_number, TOL);
}
START_TEST(decimal_to_float_test_2) {
  s21_decimal decimal = {12345678, 0, 0, 0};
  s21_set_scale(&decimal, 5);
  float expected_number = 12345678e-5;
  float number = 0;

  ck_assert(s21_from_decimal_to_float(decimal, &number) == OK);
  ck_assert_double_eq_tol(expected_number, number, 1e-4);
}

END_TEST
Suite *create_float_convertets_suite() {
  Suite *suite = suite_create("float converters tests");
  TCase *decimal_to_float_tc = tcase_create("float to decimal tests");

  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_1);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_2);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_3);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_4);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_5);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_6);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_7);
  tcase_add_test(decimal_to_float_tc, float_to_decimal_test_8);

  TCase *float_to_decimal_tc = tcase_create("decimal to float tests");
  tcase_add_test(float_to_decimal_tc, decimal_to_float_test_1);
  tcase_add_test(float_to_decimal_tc, decimal_to_float_test_2);

  suite_add_tcase(suite, decimal_to_float_tc);
  suite_add_tcase(suite, float_to_decimal_tc);

  return suite;
}
