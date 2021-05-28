#include "sync.h"
#include "asm_utils.h"
#include "stdio.h"
#include "log.h"
#include "os_modules.h"
#include "program.h"

SpinLock::SpinLock()
{
    initialize();
}

void SpinLock::initialize()
{
    bolt = 0;
}

void SpinLock::lock()
{
    uint32 key = 1;

    do
    {
        asm_atomic_exchange(&key, &bolt);
        //printf("pid: %d\n", programManager.running->pid);
    } while (key);
}

void SpinLock::unlock()
{
    bolt = 0;
}

Semaphore::Semaphore()
{
    initialize(0);
}

void Semaphore::initialize(uint32 counter)
{
    this->counter = counter;
    semLock.initialize();
    waiting.initialize();
}

void Semaphore::P()
{
    PCB *cur = nullptr;
    while (true)
    {
        semLock.lock(); //counter临界区
        if (counter > 0)
        {
            --counter;//成功获取锁
            semLock.unlock();
            return;
        }
        cur = programManager.running;
        printf_debug("P block : %s\n",cur->name);
        waiting.push_back(&(cur->tagInGeneralList));
        cur->status = ProgramStatus::BLOCKED;//将该进程阻塞
        semLock.unlock();
        programManager.schedule();//立刻调度进程，防止继续在while循环中消耗CPU
    }
}

void Semaphore::V()
{
    semLock.lock();
    ++counter;
    if (waiting.size())//有进程在等待，需要唤醒进程
    {
        PCB *program = ListItem2PCB(waiting.front(), tagInGeneralList);
        waiting.pop_front();//选取最前面的进程唤醒
        semLock.unlock();
        programManager.MESA_WakeUp(program);//唤醒进程
        printf_debug("V wake %s\n",program->name);

    }
    else
    {
        semLock.unlock();
    }
}