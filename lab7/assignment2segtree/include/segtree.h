#ifndef SEGTREE_H
#define SEGTREE_H

#include "os_type.h"

class SegTree
{
public:
    // 被管理的资源个数
    int length;
    int bytes;
    //叶子节点的个数
    int leave_nodes;
    // bitmap的起始地址
    char *seg;
public:
    // 初始化
    SegTree();
    // 设置BitMap，bitmap=起始地址，length=总位数(即被管理的资源个数)
    void initialize(char *s, const int length);
    // 获取第index个资源的状态，true=allocated，false=free
    bool get(const int index) const;
    // 设置第index个资源的状态，true=allocated，false=free
    void set(const int index, const bool status);
    //
    void up(int index,bool status);
    // 分配count个连续的资源，若没有则返回-1，否则返回分配的第1个资源单元序号
    int allocate(const int count);
    // 释放第index个资源开始的count个资源
    void release(const int index, const int count);
    // 返回Bitmap存储区域
    //char *getBitmap();
    // 返回Bitmap的大小
    int size() const;
private:
    // 禁止Bitmap之间的赋值
    SegTree(const SegTree &) {}
    void operator=(const SegTree&) {}
};

#endif