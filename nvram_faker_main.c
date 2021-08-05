/* 
 * test driver to debug nvram-faker code without
 * having to LD_PRELOAD a lib.
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define DEBUG
#endif

#ifndef NVRAM_EXE
#define NVRAM_EXE
#endif


#include "nvram-faker-internal.h"

extern void initialize_ini(void);
extern void end(void);

int main(void)
{
    DEBUG_PRINTF("[FAKE_NVRAM] calling initalize_dict().\n");
    initialize_dict();
    DEBUG_PRINTF("[FAKE_NVRAM] calling end().\n");
    end();
    DEBUG_PRINTF("[FAKE_NVRAM] Done.\n");
    return 0;
}