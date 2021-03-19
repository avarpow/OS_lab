; If you meet compile error, try 'sudo apt install gcc-multilib g++-multilib' first

%include "head.include"
; you code here

your_if:
    mov ebx,[a1]
    cmp ebx,12
    jl your_if_st12
    cmp ebx,24
    jl your_if_st24
    jmp your_if_other
    your_if_st12:
        shr ebx,1
        mov eax,ebx
        inc eax ;eax=ebx*2
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
    mov eax,[a2]
    mov ebx,[while_flag]
    mov ecx,eax
    sub ecx,11
    my_loop:
        push eax
        push ecx
        push ebx
        call my_random
        pop ebx
        pop ecx
        mov [ecx+ebx-1],al
        pop eax
        dec eax
        mov [a2],eax
        loop my_loop

%include "end.include"

your_function:
    mov ecx,0
    mov edx,[your_string]
    func_loop:
        mov al,[ecx+edx]
        mov ah,0
        cmp ax,0
        je func_end
        pushad
        push ax
        call print_a_char
        pop ax
        popad
        add ecx,1
        jmp func_loop
    func_end:
        ret

