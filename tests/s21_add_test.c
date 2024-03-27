
#include "s21_decimal_test.h"
// 15 + 3 = 18
START_TEST(add_test_1) {
  s21_decimal value_1 = {15, 0, 0, 0};
  s21_decimal value_2 = {3, 0, 0, 0};
  s21_decimal result = {0, 0, 0, 0};
  s21_decimal excepted_result = {18, 0, 0, 0};
  s21_add(value_1, value_2, &result);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST
//-15 + 3 = -12
START_TEST(add_test_2) {
  s21_decimal value_1 = {15, 0, 0, 0};
  s21_set_sign(&value_1, 1);

  s21_decimal value_2 = {3, 0, 0, 0};
  s21_decimal result = {0, 0, 0, 0};

  s21_decimal excepted_result = {12, 0, 0, 0};
  s21_set_sign(&excepted_result, 1);
  s21_add(value_1, value_2, &result);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

//-15 + -3 = -18
START_TEST(add_test_3) {
  s21_decimal value_1 = {15, 0, 0, 0};
  s21_set_sign(&value_1, 1);

  s21_decimal value_2 = {3, 0, 0, 0};
  s21_set_sign(&value_2, 1);

  s21_decimal result = {0, 0, 0, 0};

  s21_decimal excepted_result = {18, 0, 0, 0};
  s21_set_sign(&excepted_result, 1);
  s21_add(value_1, value_2, &result);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

// 15 - 3 = 12
START_TEST(add_test_4) {
  s21_decimal value_1 = {15, 0, 0, 0};

  s21_decimal value_2 = {3, 0, 0, 0};
  s21_set_sign(&value_2, 1);

  s21_decimal result = {0, 0, 0, 0};

  s21_decimal excepted_result = {12, 0, 0, 0};

  s21_add(value_1, value_2, &result);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

// 79 228 162 514 264 337 593 543 950 335 + 1 = overflow
START_TEST(add_test_5) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};

  s21_decimal value_2 = {1, 0, 0, 0};

  s21_decimal result = {0, 0, 0, 0};

  // s21_decimal excepted_result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == NUMBER_TOO_LARGE);
}
END_TEST

//-79 228 162 514 264 337 593 543 950 335 - 1 = overflow
START_TEST(add_test_6) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_sign(&value_1, 1);
  s21_decimal value_2 = {1, 0, 0, 0};
  s21_set_sign(&value_2, 1);
  s21_decimal result = {0, 0, 0, 0};

  // s21_decimal excepted_result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == NUMBER_TOO_LOW);
}
END_TEST

// + 7 9 228 162 514 264 337 593 543 950 33,5 + 7,9 228 162 514 264 337 593 543
// 950 33,5 = 15.845632502852867518708790067
START_TEST(add_test_7) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_1, 1);
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_2, 1);
  s21_decimal excepted_result = {0x33333333, 0x33333333, 0x33333333, 0};
  s21_set_scale(&excepted_result, 0);

  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

// + 7,9 228 162 514 264 337 593 543 950 335 + 7,9 228 162 514 264 337 593 543
// 950 335 = 15.845632502852867518708790067
START_TEST(add_test_8) {
  s21_decimal value_1 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_1, 28);
  s21_decimal value_2 = {UINT_MAX, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_2, 28);
  s21_decimal excepted_result = {0x33333333, 0x33333333, 0x33333333, 0};
  s21_set_scale(&excepted_result, 27);

  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST
// + 7,9 228 162 514 264 337 593 543 950 325 + 7,9 228 162 514 264 337 593 543
// 950 330 = 15.845632502852867518708790066
START_TEST(add_test_9) {
  s21_decimal value_1 = {UINT_MAX - 10, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_1, 28);
  s21_decimal value_2 = {UINT_MAX - 5, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_2, 28);
  s21_decimal excepted_result = {0x33333333 - 1, 0x33333333, 0x33333333, 0};
  s21_set_scale(&excepted_result, 27);

  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

// + 7,9 228 162 514 264 337 593 543 950 331 + 7,9 228 162 514 264 337 593 543
// 950 331 = 15.845632502852867518708790066
START_TEST(add_test_10) {
  s21_decimal value_1 = {UINT_MAX - 4, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_1, 28);
  s21_decimal value_2 = {UINT_MAX - 4, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_2, 28);
  s21_decimal excepted_result = {0x33333333 - 1, 0x33333333, 0x33333333, 0};
  s21_set_scale(&excepted_result, 27);

  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

// + 7,9 228 162 514 264 337 593 543 950 314 + 7,9 228 162 514 264 337 593 543
// 950 311 = 15.845632502852867518708790062
START_TEST(add_test_11) {
  s21_decimal value_1 = {UINT_MAX - 21, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_1, 28);
  s21_decimal value_2 = {UINT_MAX - 24, UINT_MAX, UINT_MAX, 0};
  s21_set_scale(&value_2, 28);
  s21_decimal excepted_result = {0x33333333 - 5, 0x33333333, 0x33333333, 0};
  s21_set_scale(&excepted_result, 27);

  s21_decimal result = {0, 0, 0, 0};

  ck_assert(s21_add(value_1, value_2, &result) == OK);
  ck_assert(s21_is_equal(result, excepted_result) == TRUE);
}
END_TEST

Suite *create_add_suite() {
  Suite *suite = suite_create("add_tests_suite");

  TCase *add_test_case = tcase_create("add_test_case");
  tcase_add_test(add_test_case, add_test_1);
  tcase_add_test(add_test_case, add_test_2);
  tcase_add_test(add_test_case, add_test_3);
  tcase_add_test(add_test_case, add_test_4);
  tcase_add_test(add_test_case, add_test_5);
  tcase_add_test(add_test_case, add_test_6);
  tcase_add_test(add_test_case, add_test_7);
  tcase_add_test(add_test_case, add_test_8);
  tcase_add_test(add_test_case, add_test_9);
  tcase_add_test(add_test_case, add_test_10);
  tcase_add_test(add_test_case, add_test_11);
  suite_add_tcase(suite, add_test_case);
  return suite;
}
