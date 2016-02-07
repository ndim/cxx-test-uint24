########################################################################

AWK     = awk
MKDIR_P = mkdir -p
SORT_U  = sort -u

########################################################################

CC      = avr-gcc
CXX     = avr-gcc
NM      = avr-nm
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump

########################################################################

ASFLAGS  ?=
CFLAGS   ?=
CPPFLAGS ?=
CXXFLAGS ?=

########################################################################
# Collect all targets here so we can build them in parallel in a later
# rule

CHECKs ?=
EXEs   ?=
OBJs   ?=

########################################################################

CPPFLAGS += -Werror
CPPFLAGS += -Wall -Wextra
CPPFLAGS += -Iinclude

CFLAGS += -Os -gstabs
# Note that -std=c11 does not work for us as we need asm statements.
CFLAGS += -std=gnu11 -pedantic
CFLAGS += -Wstrict-prototypes
CFLAGS += -fshort-enums -fno-common
CFLAGS += -save-temps=obj

CXXFLAGS += -Os -gstabs
CXXFLAGS += -std=c++11 -pedantic
CXXFLAGS += -fshort-enums -fno-common
CXXFLAGS += -save-temps=obj

########################################################################

MCUs =
MCUs += atmega328
MCUs += atmega644
MCUs += atmega644a
MCUs += atmega644p
MCUs += atmega644pa
MCUs += atmega1284
MCUs += atmega1284p

########################################################################

.PHONY: all
all: all-local

########################################################################
# Define MCU specific rules. $(1) is the MCU value.

define mcu-specific-rules =

########################################################################
# Separately object files to build so we can examine them as well
# independent on what object files the binaries actually require.

OBJs += build/$(1)/objs/main-c.o
OBJs += build/$(1)/objs/main-cxx.o

OBJs += build/$(1)/objs/test-c-custom.o
OBJs += build/$(1)/objs/test-c-gcc47.o
OBJs += build/$(1)/objs/test-cxx-chararray.o
OBJs += build/$(1)/objs/test-cxx-class.o
OBJs += build/$(1)/objs/test-cxx-struct.o

########################################################################
# Link object files into ELF binaries

EXEs += build/$(1)/bin/x-c-custom.elf
EXEs += build/$(1)/bin/x-c-gcc47.elf
build/$(1)/bin/x-c-%.elf : CFLAGS+=-mmcu=$(1)
build/$(1)/bin/x-c-%.elf: build/$(1)/objs/main-c.o build/$(1)/objs/test-c-%.o
	@$$(MKDIR_P) $$(@D)
	$$(LINK.c) -o $$@ $$^

EXEs += build/$(1)/bin/x-cxx-chararray.elf
EXEs += build/$(1)/bin/x-cxx-class.elf
EXEs += build/$(1)/bin/x-cxx-struct.elf
build/$(1)/bin/x-cxx-%.elf : CXXFLAGS+=-mmcu=$(1)
build/$(1)/bin/x-cxx-%.elf: build/$(1)/objs/main-cxx.o build/$(1)/objs/test-cxx-%.o
	@$$(MKDIR_P) $$(@D)
	$$(LINK.cc) -o $$@ $$^

########################################################################
# Generate hex files and text information from ELF binaries

# hex file for flashing with avrdude
build/$(1)/bin/%.hex: build/$(1)/bin/%.elf
	$$(OBJCOPY) -O ihex -R .eeprom -R .fuse $$< $$@

# disassembly
build/$(1)/bin/%.lss: build/$(1)/bin/%.elf
	$$(OBJDUMP) -h -S $$< > $$@

# symbol list (without symbol size)
build/$(1)/bin/%.sym: build/$(1)/bin/%.elf
	$$(NM) -n $$< | $$(SORT_U) > $$@

# verbose symbol list containing the symbol size
build/$(1)/bin/%.vsym: build/$(1)/bin/%.elf
	$$(OBJDUMP) --syms $$< > $$@

########################################################################
# Compile sources to object files

build/$(1)/objs/%.o : CFLAGS+=-mmcu=$(1)
build/$(1)/objs/%.o : CFLAGS+=-Wa,-adhlns=$$(@:.o=.lst)
build/$(1)/objs/%.o: src/%.c
	@$$(MKDIR_P) $$(@D)
	$$(COMPILE.c) -o $$@ $$<

build/$(1)/objs/%.o : CXXFLAGS+=-mmcu=$(1)
build/$(1)/objs/%.o : CXXFLAGS+=-Wa,-adhlns=$$(@:.o=.lst)
build/$(1)/objs/%.o: src/%.cc
	@$$(MKDIR_P) $$(@D)
	$$(COMPILE.cc) -o $$@ $$<

########################################################################
# Automatic dependency generation for object files

build/$(1)/deps/%.c.dep : CFLAGS+=-mmcu=$(1)
build/$(1)/deps/%.c.dep: src/%.c
	@$$(MKDIR_P) $$(@D)
	$$(COMPILE.c) -MM -MT build/$(1)/objs/$$*.o -MF $$@ $$<

build/$(1)/deps/%.cc.dep : CXXFLAGS+=-mmcu=$(1)
build/$(1)/deps/%.cc.dep: src/%.cc
	@$$(MKDIR_P) $$(@D)
	$$(COMPILE.cc) -MM -MT build/$(1)/objs/$$*.o -MF $$@ $$<

include $$(foreach F, $$(wildcard src/*.c src/*.cc), build/$(1)/deps/$$(notdir $$(F)).dep)

########################################################################
# Define MCU specific rules.

endef

########################################################################
# Add the rules for each MCU value from $(MCUs)

$(foreach mcu, $(MCUs), $(eval $(call mcu-specific-rules,$(mcu))))

########################################################################

HEXs  = $(EXEs:%.elf=%.hex)
LSSs  = $(EXEs:%.elf=%.lss)
SYMs  = $(EXEs:%.elf=%.sym)
VSYMs = $(EXEs:%.elf=%.vsym)

########################################################################

.PHONY: all-local
all-local: $(OBJs) $(EXEs) $(HEXs) $(LSSs) $(SYMs) $(VSYMs)

########################################################################

CHECKs += check-table-size
check-table-size: $(VSYMs)
	$(AWK) 'BEGIN { errs=0; } ($$6 == "table") && (strtonum("0x"$$5) != 3072) { print FILENAME; print; errs++; } END { exit errs; }' $(VSYMs)

########################################################################

.PHONY: check
check: $(CHECKs)

########################################################################

.PHONY: clean
clean:
	rm -rf build

########################################################################
# End of GNUmakefile
