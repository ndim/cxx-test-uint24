#ifndef TEST_C_GCC47_H
#define TEST_C_GCC47_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef __uint24 c_gcc_uint24_t;

  inline static
  void zero_c_gcc_uint24_t(volatile c_gcc_uint24_t *dest)
  {
    *dest = 0;
  }

  inline static
  void incr_c_gcc_uint24_t(volatile c_gcc_uint24_t *element)
  {
    ++(*element);
  }

#ifdef __cplusplus
}
#endif

#endif
