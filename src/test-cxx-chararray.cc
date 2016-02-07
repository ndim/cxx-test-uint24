#include "test-cxx-chararray"

cxx_chararray_uint24_t table[1024];

void test(void)
{
  asm volatile ("nop\n");
  zero_cxx_chararray_uint24_t(&table[13]);
  asm volatile ("nop\n");
  incr_cxx_chararray_uint24_t(&table[13]);
  asm volatile ("nop\n");
  /* ++table[13]; */
  asm volatile ("nop\n");
}
