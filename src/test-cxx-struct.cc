#include "test-cxx-struct"

cxx_struct_uint24_t table[1024];

void test(void)
{
  asm volatile("nop\n");
  zero_struct_uint24(&table[13]);
  asm volatile("nop\n");
  incr_struct_uint24(&table[13]);
  asm volatile("nop\n");
  ++table[13];
  asm volatile("nop\n");
}
