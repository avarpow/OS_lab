org 7c00h
[bits 16]
msg db "18324034"

xor ax, ax ; eax = 0
; 初始化段寄存器, 段地址全部设为0
mov ds, ax
mov ss, ax
mov es, ax
mov fs, ax
mov gs, ax
#  初始化栈指针
# mov sp, 0x7c00
# mov ax, 0xb800
# mov gs, ax
# mov ah, 0x47 ;蓝色

;*****************************************************
;依次push进字符串地址，字符数，背景色前景色
STRING equ 0x18 ;字符串地址
SIZE equ 0x16;字符数量
COLOR equ 0x14;背景色前景色

int_init:
    mov dh,0x47
    mov [es:2],bx
    mov [es:6],bx
    mov [es:10],bx
    mov bx,main_put
    mov [es:0],bx
    mov bx,set_pos
    mov [es:4],bx
    mov bx,get_pos
    mov [es:8],bx
    mov ax,0xb800
	mov es,ax
    int 0
    jmp $ ; 死循环

main_put:
    push msg       ;msg为字符串首地址
    push 8        ;字符数
    push 0x4700    ;颜色设定为
    call echo
    iret
    ;jmp $ ; 死循环
echo:
    mov ah,0
    int 0x16
    mov dl,al
    mov ah,0x0e
    int 0x10
    jmp echo


print:
	pusha
	push bp
	mov bp,sp

 
	mov di,word [bp+STRING]	;di字符串地址
	mov cx,word [bp+SIZE]	;cx字符数
	mov dx,word [bp+COLOR]	;颜色
	int 2
    ;#call get_pos
outstr:
	mov dl,[di]
	call judeg
	inc di
	loop outstr
end_print:
	pop bp
	popa
	ret
;-------------------------------------------------------
judeg:
judge_back:	;判断退格
	cmp dl,0x08
	jz ch_back
	jmp judge_tab
ch_back:
	cmp ax,0
	jle next
	dec ax
	int 1
    ;;#call set_pos
	imul bx,ax,2
	mov word [es:bx],0
	jmp next
;-------------------------------------------------------
judge_tab:	;判断制表符
	cmp dl,0x09
	jz ch_tab
	jmp judge_enter
ch_tab:
	mov dl,8
	mov bx,ax
	div dl
	mov al,8
	sub al,ah
	xor ah,ah
	add bx,ax
	mov ax,bx
	int 1
    ;;#call set_pos
	jmp next
;-------------------------------------------------------
judge_enter:	;判断回车
	cmp dl,0x0d
	jz ch_enter
	jmp judge_newline
ch_enter:
	push dx
	mov bx,ax
	mov dl,80
	div dl	;ax储存商，dx储存余数
	pop dx
	shr ax,8
	sub bx,ax
	mov ax,bx
	int 1
    ;#call set_pos
	jmp next
;--------------------------------------------------------
judge_newline:	;判断换行
	cmp dl,0x0a
	jz ch_newline
	jmp judge_ch
ch_newline:
	cmp ax,1840
	jae calup
	jmp n1
calup:
	call roll_up
	jmp next
n1:
	add ax,80
	int 1
    ;#call set_pos
	jmp next
;---------------------------------------------------------
judge_ch:		;判断是否为可输出字符，小于0x20，大于0x7e不可输出
	cmp dl,0x20
	jl next
	cmp dl,0x7e
	ja next
mov_cursor:

	inc ax
	int 1
    ;#call set_pos
outch:
	mov bx,ax
	dec bx
	imul bx,2
	mov word [es:bx],dx
next:
	ret
;-----------------------------------------------------------
;向上滚动一行
roll_up: 
	push ds
	push es
	push cx
	push di
	mov bx,0xb800
	mov ds,bx
	mov bx,0xb7f6
	mov es,bx
	xor di,di
	xor si,si
	mov cx,2000  ;共传送80*25字
	rep movsw
	pop di
	pop cx
	pop es
	pop ds
	ret

;修改光标位置
set_pos:
    push dx
    push bx
    mov bx,ax
    
    mov dx,0x03d4
    mov al,0xe
    out dx,al
    
    mov dx,0x03d5
    mov al,bh
    out dx,al
    
    mov dx,0x03d4
    mov al,0x0f
    out dx,al
    
    mov dx,0x03d5
    mov al,bl
    out dx,al
    
    mov ax,bx
    pop bx
    pop dx

;获取光标位置，储存在ax中
get_pos:
    push dx
    push bx
    mov al,0x0e
    mov dx,0x03d4
    out dx,al
    mov dx,0x03d5
    in al,dx
    mov bl,al
    
    mov al,0x0f
    mov dx,0x03d4
    out dx,al
    mov dx,0x03d5
    in al,dx
    mov ah,bl
    pop bx
    pop dx
    ;#ret
    iret

 

times 510 - ($ - $$) db 0
db 0x55, 0xaa