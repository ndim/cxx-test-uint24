#ifndef TEST_C_CUSTOM_H
#define TEST_C_CUSTOM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  typedef char c_custom_uint24_t[3];

  inline static
  void zero_c_custom_uint24_t(volatile c_custom_uint24_t *dest)
  {
    asm volatile("\n\t"
		 /* store 24 bit value zero */
		 "std	%a[preg]+2, __zero_reg__\n\t"     /* 2 cycles */
		 "std	%a[preg]+1, __zero_reg__\n\t"     /* 2 cycles */
		 "st	%a[preg],   __zero_reg__\n\t"     /* 2 cycles */
		 : /* output operands */
		 : /* input operands */
		   [preg] "b" (dest)
		   /* no clobber */
		 );
  }

  inline static
  void incr_c_custom_uint24_t(volatile c_custom_uint24_t *element)
  {
    uint16_t accu;
    asm volatile("\n\t"
		 /* load 24 bit value */
		 "ld	%A[accu],    %a[elem]\n\t"        /* 2 cycles */
		 "ldd	%B[accu],    %a[elem]+1\n\t"      /* 2 cycles */
		 "ldd	__tmp_reg__, %a[elem]+2\n\t"      /* 2 cycles */

		 /* increment 24 bit value */
		 "adiw	%[accu],     1\n\t"               /* 2 cycles */
		 "adc	__tmp_reg__, __zero_reg__\n\t"    /* 1 cycle  */

		 /* store 24 bit value */
		 "st	%a[elem],    %A[accu]\n\t"        /* 2 cycles */
		 "std	%a[elem]+1,  %B[accu]\n\t"        /* 2 cycles */
		 "std	%a[elem]+2,  __tmp_reg__\n\t"     /* 2 cycles */

		 : /* output operands */
		   /* Let compiler decide which registers to
		    * clobber. However, the adiw instruction only
		    * works on r24:r25, r26:r27, r28:r29, r30:r31, so
		    * &w is the appropriate letter for the clobber
		    * accu.
		    */
		   [accu] "=&w" (accu)

		 : /* input operands */
		   [elem] "b" (element)

		   /* : let compiler decide which regs to clobber via register var accu var */
		 );
  }

#ifdef __cplusplus
}
#endif

#endif
