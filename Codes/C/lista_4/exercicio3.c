#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef union fltint Flt_Int;

union fltint {
  uint64_t a;
  double b;
};

int main(void) {
  Flt_Int u;
  u.b = 500.1234;

  printf("%" PRIu64 "\n", u.a);
  return 0;
}
