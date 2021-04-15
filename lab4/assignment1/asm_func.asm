[bits 32]
global function_from_asm
extern function_from_C
extern function_from_CPP
extern function_from_Rust
function_from_asm:
    call function_from_C
    sub esp,8
    mov eax,18324034
    mov [esp + 4 * 0],eax
    mov eax,name
    mov [esp + 4 * 1],eax
    call function_from_CPP
    add esp,8
    call function_from_Rust
    ret

name db 'Avarpow'
    db 0

