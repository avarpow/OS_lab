#include<stdio.h>
#include<unistd.h>
int main(){
    int x=100;
    int pid=fork();
    printf("pid=%d x=%d\n",pid,x);
    if(pid==0){
        x=200;
    }
    else{
        x=300;
    }
    printf("pid=%d x=%d\n",pid,x);
    return 0;
}