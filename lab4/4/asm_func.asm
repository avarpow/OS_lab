[bits 32]
global function_from_asm
extern function_from_C
extern function_from_CPP
extern function_from_Rust

function_from_asm:
    call function_from_C
    call function_from_CPP
    call function_from_Rust
    ret