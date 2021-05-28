#ifndef SYNC_H
#define SYNC_H

#include "os_type.h"
#include "list.h"

class SpinLock
{
private:
    uint32 bolt;

public:
    SpinLock();
    void initialize();
    void lock();
    void unlock();
};

class Semaphore
{
private:
    uint32 counter; //可用数量
    List waiting; //记录信号量队列
    SpinLock semLock; //控制counter的锁

public:
    Semaphore();
    void initialize(uint32 counter); //初始化信号量
    void P();//获取锁
    void V();//释放锁
};
#endif