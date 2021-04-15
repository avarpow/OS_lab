#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
    int a=open("./test.in",O_RDWR);
    int b=open("./test.out",O_RDWR);
    char o1[200]="01234";
    char o2[200]="ABCDE";
    char k[10]={0};
    int pid=fork();
    read(a,k,5);
    printf("pid=%d k=%s\n",pid,k);
    write(b,o1,5);
    write(b,o2,5);
    return 0;
}