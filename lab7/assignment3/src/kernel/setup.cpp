#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"
#include "sync.h"
#include "memory.h"
#include "SwapOutTest.h"
#include "log.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;
// 内存管理器
MemoryManager memoryManager;
SwapOutTest SwapOutTester;
extern "C" void brk(){};
int random_series[100]={9,8,0,3,2,5,6,7,9,1,3,4,5,3,4,4,6,7,2,9,3,3,7,7,5,3,6,1,8,0,3,1,0,0,5,2,7,1,8,3,4,5,2,2,1,3,4,5,6,7,8,6,2,5,3,8,5,3,6,9,1,3,4,5,3,4,4,6,7,2,9,3,3,7,7,5,3,6,1,8,0,3,1,0,0,5,2,7,1,8,3,4,5,2,2,1,3,4,5,6};
void first_thread(void *arg)
{
    // 第1个线程不可以返回
    int k=0;
    for(int i=0;i<10;i++){
        SwapOutTester.p[i]=(char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 1);
        SwapOutTester.vaild[i]=1;
        SwapOutTester.count++;
    }
    printf_info("access addr ");
    for(int i=0;i<500;i++){
        int t=259999999;
        while (t--);
        int now=random_series[i%100];
        if(SwapOutTester.vaild[now]==1){
            *(SwapOutTester.p[random_series[i]])=k++;
            printf_info("%x ",random_series[i]);
        }
    }
    printf_info("end");
    asm_halt();
}
void SwapOutTester_thread(void *arg)
{
    while(1){
        int t=999999999;
        while (t--);
        printf_info("\n");
        SwapOutTester.SwapOutCheck();
        printf_info("access addr");
    }
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
    int pid2 = programManager.executeThread(SwapOutTester_thread, nullptr, "SwapOutTester_threads", 1);
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
