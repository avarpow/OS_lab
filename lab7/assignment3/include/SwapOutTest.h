#ifndef SWAPOUTTEST_H
#define SWAPOUTTEST_H
class SwapOutTest
{
public:
    char *p[10];//页面
    int count;//页面数量
    int vaild[10];//页面是否被换出
    char *unactive[10];//闲置页面
    int unactivecount;//闲置页面数量
    SwapOutTest(/* args */);
    void SwapOutCheck();
    void SwapOut(char *vaddr);
    bool IsActive(char *vaddr);
};



#endif