#include "Physical_address_pool.h"
#include "os_constant.h"

Physical_AddressPool::Physical_AddressPool()
{
}

// 设置地址池BitMap
void Physical_AddressPool::initialize(char *bitmap, const int length, const int startAddress)
{
    resources.initialize(bitmap, length);
    this->startAddress = startAddress;
}

// 从地址池中分配count个连续页
int Physical_AddressPool::allocate(const int count)
{
    int start = resources.allocate(count);
    return (start == -1) ? -1 : (start * PAGE_SIZE + startAddress);
}

// 释放若干页的空间
void Physical_AddressPool::release(const int address, const int amount)
{
    resources.release((address - startAddress) / PAGE_SIZE, amount);
}