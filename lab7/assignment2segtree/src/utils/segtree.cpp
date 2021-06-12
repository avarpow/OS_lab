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
    this->leave_nodes = next_power_of_two(length);
    printf_debug("length %d leave %d\n",length,leave_nodes);
    int bytes = ceil(length, 8);
    for(int i=0;i<leave_nodes*2;i++){
        set(i,false);
    }
    for(int i=length;i<leave_nodes;i++){
        set(i,true);
    }
    for(int i=leave_nodes;i>0;i--){
        bool sta=get(2*i) && get(2*i+1) && get(i);
        set(i,sta);
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
    int index;
    index = 1;
    if(get(index) == 1){
        return -1;
    }
    else{
        while(index < length /2){
            if(!get(index*2)){
                index*=2;// printf_debug("1segtree index%d\n",index);
            }
            else if(!get(index*2+1)){
                index=index*2+1;// printf_debug("2segtree index%d\n",index);
            }
            else{
                printf_error("SegmentTree BAD\n");
                while(1);
            }
        }
    }
    up(index,true);
    // printf_debug("segtree alloc index%d\n",index-leave_nodes/2);brk();
    return index-leave_nodes/2;
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
    int node = index+leave_nodes/2;
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