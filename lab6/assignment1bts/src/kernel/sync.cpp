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
    printf_debug("bolt %d\n",bolt);
    asm_btslock(&bolt);
    printf_debug("bolt %d\n",bolt);
}

void SpinLock::unlock()
{
    printf_debug("bolt %d\n",bolt);
    asm_btsunlock(&bolt);
    printf_debug("bolt %d\n",bolt);

}