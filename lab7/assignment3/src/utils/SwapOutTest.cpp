#include"SwapOutTest.h"
#include "os_type.h"
#include "log.h"
#include "asm_utils.h"


SwapOutTest::SwapOutTest(/* args */)
{
    count=0;
    unactivecount=0;
    for(int i=0;i<10;i++){
        vaild[i]=1;
    }
}
void SwapOutTest::SwapOutCheck(){
    printf_debug("Unactive vaddr is");//检测闲置页面
    int check_count=0;
    char *temp[10];
    for(int i=0;i<count;i++){
        if(vaild[i] && !IsActive(p[i])){
            temp[check_count++]=p[i];
            printf_debug("%d ",i);
        }
    }
    printf_info("\n");
    for(int i=0;i<check_count;i++){
        for(int j=0;j<unactivecount;j++){
            if(unactive[j]==temp[i]){//检测闲置页面是否被闲置两次
                printf_error("Double unactive Swap out vaddr %x\n",temp[i]);
                SwapOut(temp[i]);//换出
            }
        }
    }
    unactivecount=0;
    for(int i=0;i<check_count;i++){
        unactive[unactivecount++]=temp[i];
    }
}
int toPTE(char * virtualAddress)
{
    return (0xffc00000 + (((int)virtualAddress & 0xffc00000) >> 10) + ((((int)virtualAddress & 0x003ff000) >> 12) * 4));
}
void SwapOutTest::SwapOut(char *vaddr){
    int *pte = (int *)toPTE(vaddr);
    *pte=*pte&(~1);//有效位清零
    for(int i=0;i<count;i++){
        if(vaddr==p[i]){
            vaild[i]=0;
        }
    }
}
bool SwapOutTest::IsActive(char *vaddr){
    int *pte = (int *)toPTE(vaddr);
    //printf_info("pte = %x\n",*pte);
    bool ans=(*pte)&(1<<5);//获取访问位
    *pte=*pte&(~(3<<5));//访问位和写入位清零
    asm_cr3();
    return ans;//返回访问位
}