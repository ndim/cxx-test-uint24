#include "test-cxx-class"

cxx_class_uint24_t table[1024];

void test(void)
{
  asm volatile("nop\n");
  zero_class_uint24(&table[13]);
  asm volatile("nop\n");
  incr_class_uint24(&table[13]);
  asm volatile("nop\n");
  ++table[13];
  asm volatile("nop\n");
}
