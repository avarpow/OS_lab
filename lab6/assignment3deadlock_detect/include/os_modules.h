#ifndef OS_MODULES_H
#define OS_MODULES_H

#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "deadlock.h"

extern InterruptManager interruptManager;
extern STDIO stdio;
extern ProgramManager programManager;
extern deadlockManager  DeadlockManager;

#endif