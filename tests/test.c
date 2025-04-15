#include "test.h"

#define TEST_BLOCKS 4

int main() {
  int nf = 0;

  Suite *suites[TEST_BLOCKS] = {menuInteractionTests(), matrixTests(),
                                fsmTests(), backendTests()};

  for (int i = 0; i < TEST_BLOCKS; i++) {
    SRunner *sr = srunner_create(suites[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    nf += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  return nf == 0 ? 0 : 1;
}