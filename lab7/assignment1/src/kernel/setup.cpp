#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"
#include "sync.h"
#include "memory.h"
#include "log.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;
// 内存管理器
MemoryManager memoryManager;
extern "C" void brk(){};

void first_thread(void *arg)
{
    // 第1个线程不可以返回
    // stdio.moveCursor(0);
    // for (int i = 0; i < 25 * 80; ++i)
    // {
    //     stdio.print(' ');
    // }
    // stdio.moveCursor(0);

    char *p1 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
    printf_debug("first address:%x\n", p1);
    // printf_debug("close address:%x\n", p1);
    asm_stop_page_reg();
    brk();
    asm_open_page_reg();
    *p1=10;
    asm_stop_page_reg();
    brk();
    asm_open_page_reg();

    char *p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 10);
    printf_debug("second address:%x\n", p2);
    char *p3 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
    // printf_debug("third address:%x\n", p3);
    // memoryManager.releasePages(AddressPoolType::KERNEL, (int)p2, 10);
    // p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
    // printf_debug("realloc p2 %x\n", p2);
    // p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 10);
    // printf_debug("realloc p2 %x\n", p2);

    asm_halt();
}
extern "C" void setup_kernel()
{

    // 中断管理器
    interruptManager.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);

    // 输出管理器
    stdio.initialize();

    // 进程/线程管理器
    programManager.initialize();

    // 内存管理器
    memoryManager.openPageMechanism();
    memoryManager.initialize();

    // 创建第一个线程
    int pid = programManager.executeThread(first_thread, nullptr, "first thread", 1);
    if (pid == -1)
    {
        printf("can not execute thread\n");
        asm_halt();
    }

    ListItem *item = programManager.readyPrograms.front();
    PCB *firstThread = ListItem2PCB(item, tagInGeneralList);
    firstThread->status = RUNNING;
    programManager.readyPrograms.pop_front();
    programManager.running = firstThread;
    asm_switch_thread(0, firstThread);

    asm_halt();
}
