org 7c00h
delay equ 5000
delay2 equ 10


;初始化
;字符1位置bh,bl
;字符2位置ch,cl
;字符与颜色al,ah
;当前方向dh,dl
;方向00：右下，方向01：右上，方向10：左下，方向11：左上
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
mov ah, 0x0 ;
mov al, '0'

;初始化bp
mov bp,0
;初始化位置

mov [gs:2 * 2], ax

mov bh,9 ;字符1初始行
mov bl,0 ;字符1初始列
mov ch,16 ;字符2初始行
mov cl,79 ;字符2初始列
mov dh,0 ;字符1初始方向
mov dl,3 ;字符2初始方向

print:
    pushad
    mov dh,0
    mov dl,bh
    imul dx,80
    mov bh,0
    add dx,bx
    imul dx,2
    mov bp,dx
    mov [gs:bp],ax
    popad
    call print_id
    call pause
    call change_text

    pushad
    mov dh,0
    mov dl,ch
    imul dx,80
    mov ch,0
    add dx,cx
    imul dx,2
    mov bp,dx
    mov [gs:bp],ax
    popad
    call print_id
    call pause
    call change_text
    call change_b_position
    call change_c_position
    jmp print

change_text: ;改变颜色和数字
    inc ah
    inc al
    cmp al,':'
    jge set_al_zero
    jmp change_text_end
set_al_zero: ;超过9重新设置为0
    mov al,'0'
change_text_end:
    ret

change_b_position:
    cmp dh,0
    je right_down_b
    cmp dh,1
    je right_up_b
    cmp dh,2
    je left_down_b
    cmp dh,3
    je left_up_b
    right_down_b:
        inc bh
        inc bl
        jmp check_bl
    right_up_b:
        dec bh
        inc bl
        jmp check_bl
    left_down_b:
        inc bh
        dec bl
        jmp check_bl
    left_up_b:
        dec bh
        dec bl
        jmp check_bl
check_bl:
    cmp bl,0
    jle change_left_right
    cmp bl,79
    jge change_left_right
    jmp check_bh
change_left_right: ;改变方向左右
    xor dh,0x02
check_bh:
    cmp bh,0
    jle change_up_down
    cmp bh,24
    jge change_up_down
    jmp change_end
change_up_down:
    xor dh,0x01  ;改变方向上下
change_end:
    ret

change_c_position:
    cmp dl,0
    je right_down_c
    cmp dl,1
    je right_up_c
    cmp dl,2
    je left_down_c
    cmp dl,3
    je left_up_c
    right_down_c:
        inc ch
        inc cl
        jmp c_check_cl
    right_up_c:
        dec ch
        inc cl
        jmp c_check_cl
    left_down_c:
        inc ch
        dec cl
        jmp c_check_cl
    left_up_c:
        dec ch
        dec cl
        jmp c_check_cl
c_check_cl:
    cmp cl,0
    jle c_change_left_right
    cmp cl,79
    jge c_change_left_right
    jmp c_check_ch
c_change_left_right:
    xor dl,0x02 ;改变方向左右
c_check_ch:
    cmp ch,0
    jle c_change_up_down
    cmp ch,24
    jge c_change_up_down
    jmp c_change_end
c_change_up_down:
    xor dl,0x01  ;改变方向上下
c_change_end:
    ret

pause: ;延时函数
    pushad
    mov ecx,delay
    in_loop:
        call pause_2
        loop in_loop
    in_end:
    popad
    ret

pause_2:
    pushad
    mov ecx,delay2
    in_loop_2:
        loop in_loop_2
    in_end_2:
    popad
    ret
   
print_id:
    pushad
    mov si, stuid          ; 显示姓名和学号
    mov di, 64
    mov cx, 16
print_char:                      ; 
    mov ah,0x47
    mov al, [si]
    inc si
    mov word [gs:di],ax
    add di,2
    loop print_char
    popad
    ret
jmp $ ; 死循环

stuid db 'Avarpow 18324034'
times 510 - ($ - $$) db 0
db 0x55, 0xaa