#pragma once

#include "defs.h"

#ifdef __ASSEMBLER__
.globl intr32_entries
#else

#include <stdint.h>

extern uint32_t intr32_entries[INTR32_NR_INTS];

#endif
