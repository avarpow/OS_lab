#include "sync.h"
#include "asm_utils.h"
#include "stdio.h"
#include "log.h"
#include "os_modules.h"

SpinLock::SpinLock()
{
    initialize();
}

void SpinLock::initialize(){bolt = 0;}

void SpinLock::lock()
{
    uint32 key = 1;
    int count=0;
    do
    {
        printf_debug("%d times try to get lock. . . . \n",count++);
        asm_atomic_exchange(&key, &bolt);
        if(key==0){
            printf_debug("success  get lock !\n");
        }
    } while (key);
}

void SpinLock::unlock()
{
    bolt = 0;
}