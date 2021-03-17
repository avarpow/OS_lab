; If you meet compile error, try 'sudo apt install gcc-multilib g++-multilib' first

%include "head.include"
; you code here

your_if:
; put your implementation here
mov ebx,[a1]
cmp ebx,12
jl your_if_st12
cmp ebx,24
jl your_if_st24
jmp your_if_other
your_if_st12:
    imul eax,ebx,2
    inc eax
    jmp your_if_end
your_if_st24:
    mov ecx,ebx
    sub ebx,24
    neg ebx
    imul ebx,ecx
    mov eax,ebx
    jmp your_if_end
your_if_other:
    shl ebx,4
    mov eax,ebx
    jmp your_if_end
your_if_end:
    mov [if_flag],eax


your_while:
; put your implementation here

%include "end.include"

your_function:
; put your implementation here
