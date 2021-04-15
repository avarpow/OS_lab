[bits 32]

global asm_hello_world
global asm_print_string

asm_print_string:
    ;mov ah, 0x4e ;
    mov ecx,[esp + 4 * 1]
    mov ah,[esp + 4 * 2]
    mov ebx,0
.put:
    mov al,byte[ecx]
    cmp al,0
    je .end
    mov [gs:2 * ebx], ax
    add ecx,1
    inc ebx
    jmp .put
.end:
    ret

asm_hello_world:
    push eax
    xor eax, eax

    mov ah, 0x3f
    mov al, 'H'
    mov [gs:2 * 0], ax

    mov al, 'e'
    mov [gs:2 * 1], ax

    mov al, 'l'
    mov [gs:2 * 2], ax

    mov al, 'l'
    mov [gs:2 * 3], ax

    mov al, 'o'
    mov [gs:2 * 4], ax

    mov al, ' '
    mov [gs:2 * 5], ax

    mov al, 'W'
    mov [gs:2 * 6], ax

    mov al, 'o'
    mov [gs:2 * 7], ax

    mov al, 'r'
    mov [gs:2 * 8], ax

    mov al, 'l'
    mov [gs:2 * 9], ax

    mov al, 'd'
    mov [gs:2 * 10], ax

    pop eax
    ret