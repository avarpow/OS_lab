#include "interrupt.h"
#include "os_type.h"
#include "os_constant.h"
#include "asm_utils.h"
extern "C" void asm_breakpoint_interrupt();
extern "C" void asm_int_32_interrupt_warpper();
extern "C" void asm_print_string(char *,char);
InterruptManager::InterruptManager()
{
    initialize();
}
extern "C" void  int_32_handle(char color){
    asm_print_string("int32 interrupt handle",0x4e);
}

void InterruptManager::initialize()
{
    // 初始化IDT
    IDT = (uint32 *)IDT_START_ADDRESS;
    asm_lidt(IDT_START_ADDRESS, 256 * 8 - 1);

    for (uint i = 0; i < 256; ++i)
    {
        setInterruptDescriptor(i, (uint32)asm_unhandled_interrupt, 0);
    }
    setInterruptDescriptor(3, (uint32)asm_breakpoint_interrupt, 0);
    setInterruptDescriptor(0x32, (uint32)asm_int_32_interrupt_warpper, 0);

}

void InterruptManager::setInterruptDescriptor(uint32 index, uint32 address, byte DPL)
{
    // 中断描述符的低32位
    IDT[index * 2] = (CODE_SELECTOR << 16) | (address & 0xffff);
    // 中断描述符的高32位
    IDT[index * 2 + 1] = (address & 0xffff0000) | (0x1 << 15) | (DPL << 13) | (0xe << 8);
}
