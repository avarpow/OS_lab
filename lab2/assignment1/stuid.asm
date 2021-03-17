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

# mov al, '0'
# mov [gs:0], ax
# mov al, '1'
# mov [gs:80*2], ax
# mov al, '2'
# mov [gs:160*2], ax
# mov al, '3'
# mov [gs:240*2], ax
# mov al, '4'
# mov [gs:320*2], ax
# mov al, '5'
# mov [gs:400*2], ax
# mov al, '6'
# mov [gs:480*2], ax
# mov al, '7'
# mov [gs:560*2], ax
# mov al, '8'
# mov [gs:640*2], ax
# mov al, '9'
# mov [gs:720*2], ax
# mov al, 'a'
# mov [gs:800*2], ax
# mov al, 'b'
# mov [gs:880*2], ax
# mov al, 'c'
# mov [gs:960*2], ax

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