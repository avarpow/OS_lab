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
    SwapOutTest(/* args */);//构造函数
    void SwapOutCheck();//检查页面是否被访问
    void SwapOut(char *vaddr);//换出页面
    bool IsActive(char *vaddr);//判断页面是否被访问过
};



#endif