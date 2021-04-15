#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
extern char **environ;
int main(){
    int pid;
    char *argv[] ={"test",NULL};
    if((pid=fork())==0)
        execlp("ls","/bin/ls",NULL);
    if((pid=fork())==0)
        execl("/bin/ls","/bin/ls",NULL);
    if((pid=fork())==0)
        execvp("ls",argv);
    if((pid=fork())==0)
        execvpe("/bin/ls",argv,NULL);
    if((pid=fork())==0)
        execv("/bin/ls",argv);
    return 0;
}
/*
*/