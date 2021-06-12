#ifndef PHYSICAL_ADDRESS_POOL_H
#define PHYSICAL_ADDRESS_POOL_H

#include "segtree.h"
#include "os_type.h"

class Physical_AddressPool
{
public:
    SegTree resources;
    int startAddress;

public:
    Physical_AddressPool();
    // 初始化地址池
    void initialize(char *bitmap, const int length, const int startAddress);
    // 从地址池中分配count个连续页，成功则返回第一个页的地址，失败则返回-1
    int allocate(const int count);
    // 释放若干页的空间
    void release(const int address, const int amount);
};

#endif