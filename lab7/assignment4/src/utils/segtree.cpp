#include "segtree.h"
#include "stdlib.h"
#include "stdio.h"
#include "log.h"

SegTree::SegTree()
{
}

void SegTree::initialize(char *s, const int length)
{
    this->seg = s;
    this->length = length;

    int bytes = ceil(length, 8);

    for (int i = 0; i < bytes; ++i)
    {
        s[i] = 0;
    }
}

bool SegTree::get(const int index) const
{
    int pos = index / 8;
    int offset = index % 8;

    return (seg[pos] & (1 << offset));
}

void SegTree::set(const int index, const bool status)
{
    int pos = index / 8;
    int offset = index % 8;

    // 清0
    seg[pos] = seg[pos] & (~(1 << offset));

    // 置1
    if (status)
    {
        seg[pos] = seg[pos] | (1 << offset);
    }
}
static void brk(){}

int SegTree::allocate(const int count)
{
    if(count!=1){
        printf_error("SegmentTree allocator alloc 1 address once\n");
        return -1;
    }
    if (count == 0)
        return -1;

    int index, empty, start;

    index = 1;
    if(get(index) == 1){
        return -1;
    }
    else{
        while(index < length /2){
            if(!get(index*2)){
                index*=2;
            }
            else if(!get(index*2+1)){
                index=index*2+1;
            }
            else{
                printf_error("SegmentTree BAD\n");
            }
        }
    }
    up(index,true);
    printf_debug("segtree alloc index%d\n",index-length/2);
    brk();
    return index-length/2;
}
void SegTree::up(int index,bool status){
    set(index,status);
    while(index>1){
        index/=2;
        bool t = get(index*2) && get(index*2+1);
        set(index,t);
    }
}
void SegTree::release(const int index, const int count)
{
    int node = index+length/2;
    up(node,false);
}

// char *SegTree::getBitmap()
// {
//     return (char *)s;
// }

int SegTree::size() const
{
    return length;
}