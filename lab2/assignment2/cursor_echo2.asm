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
    mov bp,es
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
    call echo
    iret
    ;jmp $ ; 死循环
echo:
    call get_key
    call judeg
    jmp echo
get_key:
    mov ah,0
    int 0x16
    mov dl,al
    ret

;-------------------------------------------------------
judeg:
judge_back:	;判断退格
	cmp dl,0x08
	jz ch_back
	jmp judge_tab
ch_back:
	cmp bp,0
	jle next
	dec bp
	int 1
    ;;#call set_pos
	imul bx,bp,2
	mov word [es:bx],0
	jmp next
;-------------------------------------------------------
judge_tab:	;判断制表符
	cmp dl,0x09
	jz ch_tab
	jmp judge_enter
ch_tab:
    push ax
	mov dl,8
	mov bx,bp
	div dl
	mov al,8
	sub al,ah
	xor ah,ah
	add bx,bp
	mov bp,bx
	int 1
    pop ax
    ;;#call set_pos
	jmp next
;-------------------------------------------------------
judge_enter:	;判断回车
	cmp dl,0x0d
	jz ch_enter
	jmp judge_newline
ch_enter:
	push dx
	mov bx,bp
	mov dl,80
	div dl	;ax储存商，dx储存余数
	pop dx
	shr bp,8
	sub bx,bp
	mov bp,bx
	int 1
    ;#call set_pos
	jmp next
;--------------------------------------------------------
judge_newline:	;判断换行
	cmp dl,0x0a
	jz ch_newline
	jmp judge_ch
ch_newline:
	cmp bp,1840
	jae calup
	jmp n1
calup:
	call roll_up
	jmp next
n1:
	add bp,80
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

	inc bp
	int 1
    ;#call set_pos
outch:
	mov bx,bp
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
    push ax
    mov bx,bp
    
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
    
    mov bp,bx
    pop ax
    pop bx
    pop dx

;获取光标位置，储存在ax中
get_pos:
    push ax
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
    mov bp,ax
    pop bx
    pop dx
    pop ax
    ;#ret
    iret

 

times 510 - ($ - $$) db 0
db 0x55, 0xaa