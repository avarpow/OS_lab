org 7c00h
[bits 16]
xor ax, ax ; eax = 0
; 初始化段寄存器, 段地址全部设为0
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax
; 初始化栈指针
mov sp, 0x7c00
mov ax, 0xb800
mov gs, ax
mov ah, 0x47 ;蓝色

;初始化bp

mov ah, 0x47 ;改颜色
mov bp,2*(12*80+12)
mov al, '1'
mov [gs:bp], ax
add bp,2
mov al, '8'
mov [gs:bp], ax
add bp,2
mov al, '3'
mov [gs:bp], ax
add bp,2
mov al, '2'
mov [gs:bp], ax
add bp,2
mov al, '4'
mov [gs:bp], ax
add bp,2
mov al, '0'
mov [gs:bp], ax
add bp,2
mov al, '3'
mov [gs:bp], ax
add bp,2
mov al, '4'
mov [gs:bp], ax
add bp,2


jmp $ ; 死循环

times 510 - ($ - $$) db 0
db 0x55, 0xaa