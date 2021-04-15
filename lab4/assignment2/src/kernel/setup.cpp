#include "asm_utils.h"
char s[]="18324034 Avarpow";
char color=0x4e;
extern "C" void setup_kernel()
{
    asm_print_string(s,color);
    while(1) {}
}