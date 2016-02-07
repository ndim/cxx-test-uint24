cxx-test-uint24
===============

A few implementations for an unsigned 24bit integer on an 8bit Atmel
AVR MCU using C and C++.

The goal is to define an array of 1024 24bit values which must add up
to exactly 3072 bytes - as the MCU might only have 4KB of RAM and thus
an array of 1024 32bit values will not fit.

We only need very limited operations on the uint24, namely setting it
to zero (for debugging purposes) and incrementing it (for the
production use).

To build, run

    $ make -j

This builds all implementations for a bunch of different ATmega MCUs.

  * `test-c-custom`

    Custom C code with inline asm. No `++` operators, everything
    operation needs to be done with function calls like
    `incr_uint24(&foo)`.

  * `test-c-gcc47`

	Use the `__uint24` which GCC 4.7 introduced on AVR. This allows
    using the normal C `++foo;` operator.

  * `test-cxx-chararray`

     C++ typedef as array of 3 chars. Does not do operator
     overloading, so this has no practical advantage over any of the
     two C based solutions.

  * `test-cxx-class`

     C++ class with array of 3 chars as member variable. Overloads the
     `++foo;` operator.

  * `test-cxx-struct`

     C++ struct with array of 3 chars as member variable. Overloads
     the `++foo;` operator.

For the generated code, read the `build/*/bin/*.lss` disassembly
listings.
