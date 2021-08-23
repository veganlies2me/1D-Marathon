//by dear God I hope nobody gets through the same pain as me attempting to save variables, thanks Eievui and ISSOtm
#include <gb/gb.h>
#include <string.h>
#include "memcmp.c"
uint16_t maxscore;
extern int memcmp(const void * buf1, const void * buf2, size_t count);
const char corruption_string[] = "SRAM corruption test string.";

char sram_corruption_string[sizeof(corruption_string)];

void init_sram() {
    // Check if the strings are equal.
    ENABLE_RAM_MBC1;
    if (memcmp(corruption_string, sram_corruption_string, sizeof(corruption_string))) {
        // If they are not equal, copy the test sting to SRAM and intitiallize variables.
        memcpy(sram_corruption_string, corruption_string, sizeof(corruption_string));
        maxscore = 0;
    }
    DISABLE_RAM_MBC1;
}