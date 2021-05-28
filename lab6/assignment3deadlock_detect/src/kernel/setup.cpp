#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "log.h"
#include "deadlock.h"
#include "program.h"
#include "thread.h"
#include "sync.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;
deadlockManager  DeadlockManager;

Semaphore fork[5];
int state[5];
Semaphore semaphore;
Semaphore no_full;
Semaphore no_empty;
int cheese_burger;
int msg_count;
#define BUFFER_SIZE 3

void philosopere(void *arg) {
    int index=*(int *)arg;
    int leftfork=index;
    int rightfork=(index+1) %5;
    while (true) {
    
        int delay=0x5ffffff;
        while(delay--);//延时
        DeadlockManager.add(leftfork+5,index);
        fork[leftfork].P();
        DeadlockManager.remove(leftfork+5,index);
        DeadlockManager.add(index,leftfork+5);
        printf("[philosopere] id:%d  get fork:%d\n",index+1,leftfork);
         delay=0x5ffffff;
        while(delay--);//延时
        DeadlockManager.add(rightfork+5,index);
        fork[rightfork].P();
        DeadlockManager.remove(rightfork+5,index);
        DeadlockManager.add(index,rightfork+5);
        printf("[philosopere] id:%d  get fork:%d\n",index+1,rightfork);
        delay=0x5ffffff;
        while(delay--);//延时
        fork[rightfork].V();
        DeadlockManager.remove(index,rightfork+5);
        printf("[philosopere] id:%d  release fork:%d\n",index+1,rightfork);
        fork[leftfork].V();
        DeadlockManager.remove(index,leftfork+5);
        printf("[philosopere] id:%d  release fork:%d\n",index+1,leftfork);
        state[index]=0;
    
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
    for(int i=0;i<5;i++){
        fork[i].initialize(1);
        state[i]=0;
    }
    DeadlockManager.getforks(fork);
    // programManager.executeThread(a_mother, nullptr, "second thread", 1);
    // programManager.executeThread(a_naughty_boy, nullptr, "third thread", 1);
    int index[5]={0,1,2,3,4};
    programManager.executeThread(philosopere, index  , "philosopere 1", 1);
    programManager.executeThread(philosopere, index+1, "philosopere 2", 1);
    programManager.executeThread(philosopere, index+2, "philosopere 3", 1);
    programManager.executeThread(philosopere, index+3, "philosopere 4", 1);
    programManager.executeThread(philosopere, index+4, "philosopere 5", 1);

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
