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
    printf_debug("1 address:%x\n", p1);
    char *p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 80);
    printf_debug("2 address:%x\n", p2);
    char *p3 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
    printf_debug("3 address:%x\n", p3);
    char *p4 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 40);
    printf_debug("4 address:%x\n", p4);
    char *p5 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
    printf_debug("5 address:%x\n", p5);
    memoryManager.releasePages(AddressPoolType::KERNEL, (int)p2, 80);
    memoryManager.releasePages(AddressPoolType::KERNEL, (int)p4, 40);
    p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 35);
    printf_debug("realloc p2 %x\n", p2);
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
