#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    int pid=fork();
    int wstatus;
    printf("pid=%d waiting\n",pid);
    wait(&wstatus);
    printf("pid=%d sta=%d endwaiting\n",pid,wstatus);
}
// int main(){
//     int pid=fork();
//     int t=123;
//     int *sta=&t;
//     //if(pid==0){
//         printf("pid=%d waiting\n",pid);
//         wait(sta);
//         printf("pid=%d sta=%d endwaiting\n",pid,*sta);
//     sleep(1);
//     //}
// }
