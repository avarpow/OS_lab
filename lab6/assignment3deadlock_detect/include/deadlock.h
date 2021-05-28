#include "sync.h"

#ifndef DEADLOCK_H
#define DEADLOCK_H
class deadlockManager
{
public:
    int g[10][10];
    int c[10];
    int in[10];
    Semaphore* fork;
public:
    deadlockManager(/* args */);
    int check_deadlock(/* args */);//检测死锁
    void add(int s,int d);//添加边
    void getforks(Semaphore* f);//获得信号量数组
    void remove(int s,int d);//删除边
    void init(/* args */);
    void show(/* args */);//展示邻接表
};
#endif