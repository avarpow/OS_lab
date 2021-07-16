#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "stdlib.h"
#include "program.h"
#include "thread.h"
#include "sync.h"
#include "memory.h"

// 屏幕IO处理器
STDIO stdio;
// 中断管理器
InterruptManager interruptManager;
// 程序管理器
ProgramManager programManager;
// 内存管理器
MemoryManager memoryManager;

char key_buf[200];
int key_buf_size = 0;
char dir[60] = "/";
char subscript[30] = "";
char username[30] = "avarpow";
char PC[30] = "";
struct FILE
{
    char filename[20];
    int namesize;
};
FILE f[10] = {
    {"/etc/", 5},
    {"/var/", 5},
    {"/lib/", 5},
    {"/root/", 6},
    {"/home/", 6},
    {"/home/avarpow/", 14},
    {"/home/avarpow/1.txt", 19},
    {"/home/avarpow/2.txt", 19},
    {"/home/avarpow/3.txt", 19},
    {"/home/avarpow/4.txt", 19}};

//cd ls su exec shutdown help

void cd() {}
void ls() {}
void su() {}
void exec() {}
void shutdown() {}
void help()
{
    printf("=======help=====\n");
    printf("1.ls\n");
    printf("2.cd\n");
    printf("3.su\n");
    printf("4.shutdown\n");
    printf("5.help \n");
}
int get_subscript(int index)
{
    for (int i = index + 1; i < key_buf_size - 1; i++)
    {
        subscript[i - index - 1] = key_buf[i];
    }
    subscript[key_buf_size - index - 1] = 0;
    return key_buf_size - index - 2;
}
void first_thread(void *arg)
{

    printf("start shell thread\n");
    printf("%s @ %s> ", username, dir);
    while (1)
    {
        if (key_buf[key_buf_size - 1] == '\n')
        {
            if (key_buf_size > 1)
            {
                if (strcmp(key_buf, "ls", 2))
                {
                    int k = get_subscript(2);
                    printf("shell ls\n");
                    if (k <= 0)
                    {
                        printf("NO argument\n");
                        key_buf_size = 0;
                        printf("%s @ %s> ", username, dir);
                        continue;
                    }
                    for (int i = 0; i < 10; i++)
                    {
                        if (k <= f[i].namesize && strcmp(subscript, f[i].filename, k))
                        {
                            printf("%s    ", f[i].filename);
                        }
                    }
                    printf("\n");
                }
                if (strcmp(key_buf, "su", 2))
                {
                    int k = get_subscript(2);
                    if (k <= 0)
                    {
                        printf("NO argument\n");
                        key_buf_size = 0;
                        printf("%s @ %s> ", username, dir);
                        continue;
                    }
                    strcpy(username, subscript, 30);
                }
                else if (strcmp(key_buf, "cd", 2))
                {
                    int k = get_subscript(2);
                    printf("shell cd\n");
                    if (k <= 0)
                    {
                        printf("NO argument\n");
                        key_buf_size = 0;
                        printf("%s @ %s> ", username, dir);
                        continue;
                    }
                    int flag = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        if ((k == f[i].namesize || (k == f[i].namesize-1)) && strcmp(subscript, f[i].filename, k) )
                        {
                            if (f[i].filename[f[i].namesize - 1] == '/')
                            {
                                strcpy(dir, f[i].filename, f[i].namesize);
                                key_buf_size = 0;
                                printf("%s @ %s> ", username, dir);
                                continue;
                            }
                            else
                            {
                                printf("%s is a file, not a directory");
                            }
                        }
                    }
                    printf("\n");
                }
            }
            if (key_buf_size > 3)
            {
                if (strcmp(key_buf, "help", 4))
                {
                    help();
                }
            }
            if (key_buf_size > 8)
            {
                if (strcmp(key_buf, "shutdown", 8))
                {
                    printf("shutdown");
                    for (int i = 0; i < 5; i++)
                    {
                        printf(".");
                        int t = 99999999;
                        while (t--)
                            ;
                    }
                    printf("OK\n");
                    interruptManager.disableKeyboardInterrupt();
                    asm_halt();
                }
            }
            key_buf_size = 0;
            printf("%s @ %s> ", username, dir);
        }
    }

    asm_halt();
}

extern "C" void setup_kernel()
{

    // 中断管理器
    interruptManager.initialize();
    interruptManager.enableTimeInterrupt();
    interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler);
    interruptManager.setKeyBoardInterrupt((void *)asm_keyboard_interrupt_handler);

    // 输出管理器
    stdio.initialize();

    // 进程/线程管理器
    programManager.initialize();

    // 内存管理器
    memoryManager.openPageMechanism();
    memoryManager.initialize();

    // 创建第一个线程
    int pid = programManager.executeThread(first_thread, nullptr, "first thread", 1);
    if (pid == -1)
    {
        printf("can not execute thread\n");
        asm_halt();
    }

    ListItem *item = programManager.readyPrograms.front();
    PCB *firstThread = ListItem2PCB(item, tagInGeneralList);
    firstThread->status = RUNNING;
    programManager.readyPrograms.pop_front();
    programManager.running = firstThread;
    asm_switch_thread(0, firstThread);

    asm_halt();
}
