#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "log.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;

extern "C" void setup_kernel()
{
    // 中断处理部件
    interruptManager.initialize();
    // 屏幕IO处理部件
    stdio.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);
    printf_error("error message :%d %x\n", -1234, 0x7abcdef0);
    printf_debug("debug message :%d %x\n", -1234, 0x7abcdef0);
    printf_info ("info message :%d %x\n", -1234, 0x7abcdef0);
    asm_halt();
}
    // printf("print percentage: %%\n"
    //        "print char \"N\": %c\n"
    //        "print string \"Hello World!\": %s\n"
    //        "print decimal: \"-1234\": %d\n"
    //        "print hexadecimal \"0x7abcdef0\": %x\n",
    //        'N', "Hello World!", -1234, 0x7abcdef0);
