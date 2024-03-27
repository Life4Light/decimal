#include <check.h>
#include <stdlib.h>

#include "s21_decimal.h"
#include "tests/s21_decimal_test.h"

void run_tests() {
  Suite *suite = NULL;
  SRunner *sRunner = NULL;

  Suite *suite_array[] = {create_sign_suite(),
                          create_zero_suite(),
                          create_scale_suite(),
                          suite_mul(),
                          create_suite_is_equal(),
                          create_suite_is_not_equal(),
                          create_suite_is_less(),
                          create_suite_is_less_or_equal(),
                          create_suite_is_greater(),
                          create_suite_is_greater_or_equal(),
                          create_bit_suite(),
                          create_bit_suite(),
                          create_shifts_suite(),
                          create_bitwise_operations_suite(),
                          create_bitwise_division_suite(),
                          create_add_suite(),
                          create_normalizaion_suite(),
                          create_truncate_suite(),
                          create_integer_converters_suite(),
                          create_float_convertets_suite(),
                          create_negate_suite(),
                          create_round_suite(),
                          create_floor_suite(),
                          create_div_suite(),
                          create_sub_suite()};

  int count_of_tests = sizeof(suite_array) / sizeof(Suite *);
  for (int i = 0; i < count_of_tests; i++) {
    suite = suite_array[i];
    sRunner = srunner_create(suite);
    srunner_set_fork_status(sRunner, CK_NOFORK);

    srunner_run_all(sRunner, CK_NORMAL);
    srunner_free(sRunner);

    suite = NULL;
    sRunner = NULL;
  }
}

int main() { run_tests(); }
