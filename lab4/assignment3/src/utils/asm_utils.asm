[bits 32]

global asm_hello_world
global asm_lidt
global asm_unhandled_interrupt
global asm_breakpoint_interrupt
global asm_halt
global asm_print_string
global asm_int_32_interrupt_warpper
extern int_32_handle

ASM_UNHANDLED_INTERRUPT_INFO db 'Unhandled interrupt happened, halt...'
                             db 0
ASM_IDTR dw 0
         dd 0

asm_print_string:
    ;mov ah, 0x4e ;
    mov ecx,[esp + 4 * 1]
    mov ah,[esp + 4 * 2]
    mov ebx,160
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

asm_int_32_interrupt_warpper:
    call int_32_handle
    iret

; void asm_unhandled_interrupt()
asm_unhandled_interrupt:
    cli
    mov esi, ASM_UNHANDLED_INTERRUPT_INFO
    mov ebx,160
    mov ah, 0x03
.output_information:
    cmp byte[esi], 0
    je .end
    mov al, byte[esi]
    mov word[gs:bx], ax
    inc esi
    add ebx, 2
    jmp .output_information
.end:
    jmp $

ASM_BREAKPOINT_INFO db 'Breakpoint interrupt happened, halt...'
                             db 0
; void asm_breakpoint_interrupt()
asm_breakpoint_interrupt:
    cli
    mov esi, ASM_BREAKPOINT_INFO
    xor ebx, ebx
    mov ah, 0x03
.output_information:
    cmp byte[esi], 0
    je .end
    mov al, byte[esi]
    mov word[gs:bx], ax
    inc esi
    add ebx, 2
    jmp .output_information
.end:
    iret

; void asm_lidt(uint32 start, uint16 limit)
asm_lidt:
    push ebp
    mov ebp, esp
    push eax

    mov eax, [ebp + 4 * 3]
    mov [ASM_IDTR], ax
    mov eax, [ebp + 4 * 2]
    mov [ASM_IDTR + 2], eax
    lidt [ASM_IDTR]

    pop eax
    pop ebp
    ret

asm_hello_world:
    push eax
    xor eax, eax

    mov ah, 0x03 ;青色
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

asm_halt:
    jmp $