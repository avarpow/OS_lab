#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "log.h"
#include "program.h"
#include "thread.h"
#include "sync.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;

Semaphore semaphore;
Semaphore no_empty;
Semaphore no_full;

int cheese_burger;
int msg_count;
#define BUFFER_SIZE 3
void producer(void *arg) {
    while (true) {
        no_full.P();//
        semaphore.P();
        int delay=0x0ffffff;
        while(delay--);//延时
        msg_count++;
        printf("[producer] msg_count:%d\n",msg_count);
        no_empty.V();
        semaphore.V();
    }
}
void consumer(void *arg) {
    while (true) {
        no_empty.P();
        semaphore.P();
        int delay=0x5ffffff;
        while(delay--);//延时
        msg_count--;
        printf("[consumer] msg_count:%d\n",msg_count);
        no_full.V();
        semaphore.V();
    }
}
void a_mother(void *arg)
{
    semaphore.P();
    int delay = 0;

    printf("mother: start to make cheese burger, there are %d cheese burger now\n", cheese_burger);
    // make 10 cheese_burger
    cheese_burger += 10;

    printf("mother: oh, I have to hang clothes out.\n");
    // hanging clothes out
    delay = 0xfffffff;
    while (delay)
        --delay;
    // done

    printf("mother: Oh, Jesus! There are %d cheese burgers\n", cheese_burger);
    semaphore.V();
}

void a_naughty_boy(void *arg)
{
    semaphore.P();
    printf("boy   : Look what I found!\n");
    // eat all cheese_burgers out secretly
    cheese_burger -= 10;
    // run away as fast as possible
    semaphore.V();
}

void first_thread(void *arg)
{
    // 第1个线程不可以返回
    stdio.moveCursor(0);
    for (int i = 0; i < 25 * 80; ++i)
    {
        stdio.print(' ');
    }
    stdio.moveCursor(0);
    
    cheese_burger = 0;
    msg_count = 0;
    semaphore.initialize(1);
    no_full.initialize(3);
    no_empty.initialize(0);

    // programManager.executeThread(a_mother, nullptr, "second thread", 1);
    // programManager.executeThread(a_naughty_boy, nullptr, "third thread", 1);
    programManager.executeThread(producer, nullptr, "producer 1", 5);
    programManager.executeThread(producer, nullptr, "producer 2", 5);
    programManager.executeThread(consumer, nullptr, "consumer ", 1);

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
