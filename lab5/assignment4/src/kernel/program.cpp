#include "program.h"
#include "stdlib.h"
#include "interrupt.h"
#include "asm_utils.h"
#include "stdio.h"
#include "thread.h"
#include "os_modules.h"
#include "log.h"

const int PCB_SIZE = 4096;                   // PCB的大小，4KB。
char PCB_SET[PCB_SIZE * MAX_PROGRAM_AMOUNT]; // 存放PCB的数组，预留了MAX_PROGRAM_AMOUNT个PCB的大小空间。
bool PCB_SET_STATUS[MAX_PROGRAM_AMOUNT];     // PCB的分配状态，true表示已经分配，false表示未分配。

ProgramManager::ProgramManager()
{
    initialize();
}

void ProgramManager::initialize()
{
    allPrograms.initialize();//初始化all链表
    readyPrograms.initialize();//初始化ready链表
    running = nullptr;//没有running
    for (int i = 0; i < MAX_PROGRAM_AMOUNT; ++i)
    {
        PCB_SET_STATUS[i] = false;//标记没有进程占用pcb
    }
}

int ProgramManager::executeThread(ThreadFunction function, void *parameter, const char *name, int priority)
{
    // 关中断，防止创建线程的过程被打断
    bool status = interruptManager.getInterruptStatus();
    interruptManager.disableInterrupt();
    // 分配一页作为PCB
    PCB *thread = allocatePCB();//申请PCB空间
    if (!thread)
        return -1;
    // 初始化分配的页
    memset(thread, 0, PCB_SIZE);
    for (int i = 0; i < MAX_PROGRAM_NAME && name[i]; ++i)
    {
        thread->name[i] = name[i];//设定进程名
    }
    thread->status = ProgramStatus::READY;//设置进程状态为READY
    thread->priority = priority;//设置进程优先级有
    thread->ticks = priority * 10;//设定优先级
    thread->ticksPassedBy = 0;//初始化经过的时间
    thread->pid = ((int)thread - (int)PCB_SET) / PCB_SIZE;
    // 线程栈
    thread->stack = (int *)((int)thread + PCB_SIZE);//重置程序栈为最大值
    thread->stack -= 7;//申请7个栈空间
    thread->stack[0] = 0;
    thread->stack[1] = 0;
    thread->stack[2] = 0;
    thread->stack[3] = 0;
    thread->stack[4] = (int)function;//进程要执行的函数
    thread->stack[5] = (int)program_exit;//函数退出后执行
    thread->stack[6] = (int)parameter;//函数参数

    allPrograms.push_back(&(thread->tagInAllList));//加入all链表
    readyPrograms.push_back(&(thread->tagInGeneralList));//加入ready链表
    // 恢复中断
    interruptManager.setInterruptStatus(status);

    return thread->pid;
}

void ProgramManager::schedule()
{
    bool status = interruptManager.getInterruptStatus();
    interruptManager.disableInterrupt();

    if (readyPrograms.size() == 0)//只有一个运行进程，不切换
    {
        interruptManager.setInterruptStatus(status);
        return;
    }
    if (running->status == ProgramStatus::DEAD)
    {
        releasePCB(running);//进程已经结束，释放PCB空间
        running->priority=-1;
    }
    int pro_size=readyPrograms.size();
    int max_priority=running->priority;
    PCB *max_priority_pcb=nullptr;
    ListItem *cur_item=readyPrograms.front();
    ListItem *max_item=nullptr;
    for(int i=0;i<pro_size;i++){
        PCB *cur_pcb = ListItem2PCB(cur_item, tagInGeneralList);//获取PCB地址
        if(cur_pcb->priority>max_priority){//寻找最高优先级的进程
            max_priority=cur_pcb->priority;
            max_priority_pcb=cur_pcb;
            max_item=cur_item;
        }
        cur_item=cur_item->next;
    }
    if(max_priority_pcb !=nullptr){
        printf_debug("switch to  higher priority %d pid:%d\n",max_priority,max_priority_pcb->pid);
        running->status = ProgramStatus::READY;//状态设置为ready状态
        running->ticks = running->priority * 10;//重新设置时间片
        readyPrograms.push_back(&(running->tagInGeneralList));//加入readylist中
        PCB *cur = running;//获取当前地址
        max_priority_pcb->status = ProgramStatus::RUNNING;//设置为running状态
        running = max_priority_pcb;//设置为running状态
        readyPrograms.erase(max_item);//从ready中删除
        asm_switch_thread(cur, max_priority_pcb);
    }

    interruptManager.setInterruptStatus(status);
}

void program_exit()
{
    PCB *thread = programManager.running;
    thread->status = ProgramStatus::DEAD;

    if (thread->pid)
    {
        printf_debug("exit thread %d\n",thread->pid);
        programManager.schedule();
    }
    else
    {
        interruptManager.disableInterrupt();
        printf("halt\n");
        asm_halt();
    }
}

PCB *ProgramManager::allocatePCB()
{
    for (int i = 0; i < MAX_PROGRAM_AMOUNT; ++i)
    {
        if (!PCB_SET_STATUS[i])
        {
            PCB_SET_STATUS[i] = true;
            return (PCB *)((int)PCB_SET + PCB_SIZE * i);
        }
    }

    return nullptr;
}

void ProgramManager::releasePCB(PCB *program)
{
    int index = ((int)program - (int)PCB_SET) / PCB_SIZE;
    PCB_SET_STATUS[index] = false;
}