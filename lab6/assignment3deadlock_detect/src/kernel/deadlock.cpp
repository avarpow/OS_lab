#include "sync.h"
#include "asm_utils.h"
#include "stdio.h"
#include "log.h"
#include "os_modules.h"
#include "program.h"
#include "deadlock.h"


deadlockManager::deadlockManager()
{

    for(int i=0;i<100;i++){g[i/10][i%10]=0;}
    for(int i=0;i<10;i++){c[i]=0;}
    for(int i=0;i<10;i++){in[i]=0;}
}
void deadlockManager::add(int s,int d)
{
    printf_debug("add %d:%d\n",s,d);
    g[s][c[s]++]=d;
    in[d]++;
}
void deadlockManager::getforks(Semaphore* f)
{
    fork=f;
}
void deadlockManager::remove(int s,int d){
    printf_debug("remove %d:%d\n",s,d);
    int cur=c[s];
    for(int i=0;i<cur;i++){
        if(g[s][i]==d){
            g[s][i]=g[s][cur-1];
            c[s]--;
            in[d]--;
            return;
        }
    }
}
void deadlockManager::init(/* args */)
{
    for(int i=0;i<100;i++){g[i/10][i%10]=0;}
    for(int i=0;i<10;i++){in[i]=0;}
    for(int i=0;i<10;i++){c[i]=0;}

}
void deadlockManager::show()
{
        printf(" == show \n");
    for(int i=0;i<10;i++){
        printf("i:%d  ",i);
        for(int j=0;j<c[i];j++){
            printf("%d ",g[i][j]);
        }
        printf("\n");
    }

}
int deadlockManager::check_deadlock(/* args */){
    int delay=0x3ffffff;
    while(delay--);
    show();
    printf_debug("checking\n");
    int vis[10]={0};
    int temp_in[10];
    for(int i=0;i<10;i++){
        temp_in[i]=in[i];
    }
    for(int i=0;i<10;i++){//使用拓扑排序检测有向图中的环
        for(int j=0;j<10;j++){
            if(temp_in[j]==0 && vis[j] == 0 ){
                vis[j]=1;
                for(int k=0;k<c[j];k++){
                    temp_in[g[j][k]]--;
                }
            }
        }
    }
    for(int i=0;i<10;i++){
        if(temp_in[i]!=0 && i<5){
            //发生了死锁，强制删除该进程，并释放该进程占用的信号量
            printf_error("deadlock detected\n realease locks\n");
            for(int j=0;j<c[i];j++){
                fork[g[i][j]-5].V();
                remove(i,g[i][j]);
                for(int fo=5;fo<10;fo++){
                    for(int k=0;k<c[fo];k++){
                        if(g[fo][k] == i){
                            remove(fo,i);
                        }
                    }
                }
                printf_debug("force unlock %d",g[i][j]-5);
                    int delay=0x3ffffff;
                    while(delay--);
            }
            return 1;
        }
    }
    return 0;
}
//deadlockManager::~deadlockManager(){}

