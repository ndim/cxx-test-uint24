#include "test-c-gcc47.h"

c_gcc_uint24_t table[1024];

void test(void)
{
  asm volatile ("nop\n");
  zero_c_gcc_uint24_t(&table[13]);
  asm volatile ("nop\n");
  incr_c_gcc_uint24_t(&table[13]);
  asm volatile ("nop\n");
}
