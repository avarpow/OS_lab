%include "boot.inc"
;org 0x7e00
[bits 16]
mov ax, 0xb800
mov gs, ax
mov ah, 0x03 ;青色
mov ecx, bootloader_tag_end - bootloader_tag
xor ebx, ebx
mov esi, bootloader_tag
output_bootloader_tag:
    mov al, [esi]
    mov word[gs:bx], ax
    inc esi
    add ebx,2
    loop output_bootloader_tag
creat_gdt:
;空描述符
mov dword [GDT_START_ADDRESS+0x00],0x00
mov dword [GDT_START_ADDRESS+0x04],0x00  

;创建描述符，这是一个数据段，对应0~4GB的线性地址空间
mov dword [GDT_START_ADDRESS+0x08],0x0000ffff    ; 基地址为0，段界限为0xFFFFF
mov dword [GDT_START_ADDRESS+0x0c],0x00cf9200    ; 粒度为4KB，存储器段描述符 

;建立保护模式下的堆栈段描述符      
mov dword [GDT_START_ADDRESS+0x10],0x00000000    ; 基地址为0x00000000，界限0x0 
mov dword [GDT_START_ADDRESS+0x14],0x00409600    ; 粒度为1个字节

;建立保护模式下的显存描述符   
mov dword [GDT_START_ADDRESS+0x18],0x80007fff    ; 基地址为0x000B8000，界限0x07FFF 
mov dword [GDT_START_ADDRESS+0x1c],0x0040920b    ; 粒度为字节

;创建保护模式下平坦模式代码段描述符
mov dword [GDT_START_ADDRESS+0x20],0x0000ffff    ; 基地址为0，段界限为0xFFFFF
mov dword [GDT_START_ADDRESS+0x24],0x00cf9800    ; 粒度为4kb，代码段描述符 

;初始化描述符表寄存器GDTR
mov word [pgdt], 39      ;描述符表的界限   
lgdt [pgdt]
      
in al,0x92                         ;南桥芯片内的端口 
or al,0000_0010B
out 0x92,al                        ;打开A20

cli                                ;中断机制尚未工作
mov eax,cr0
or eax,1
mov cr0,eax                        ;设置PE位
cr0_ok:      
;以下进入保护模式
jmp dword CODE_SELECTOR:protect_mode_begin

;16位的描述符选择子：32位偏移
;清流水线并串行化处理器
[bits 32]           
protect_mode_begin:                              

mov eax, DATA_SELECTOR                     ;加载数据段(0..4GB)选择子
mov ds, eax
mov es, eax
mov eax, STACK_SELECTOR
mov ss, eax
mov eax, VIDEO_SELECTOR
mov gs, eax

; 初始化栈指针
mov ah, 0x0 ;
mov al, '0'
;初始化bp
mov bp,0
;初始化位置
mov bh,9 ;字符1初始行
mov bl,0 ;字符1初始列
mov ch,16 ;字符2初始行
mov cl,79 ;字符2初始列
mov dh,0 ;字符1初始方向
mov dl,3 ;字符2初始方向
call clear_screen
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

clear_screen:
    pushad
    mov ax,0
    mov ecx,2000
    mov di,0
    clc_loop:
        mov word [gs:di],ax
        add di,2
        loop clc_loop
    popad
    ret

print_id:
    pushad
    mov si, stuid          ; 显示姓名和学号
    mov di, 64
    mov cx, 16
print_char:
    mov ah,0x47
    mov al, [si]
    inc si
    mov word [gs:di],ax
    add di,2
    loop print_char
    popad
    ret
jmp $ ; 死循环

pgdt dw 0
     dd GDT_START_ADDRESS
delay equ 5000
delay2 equ 10
stuid db 'Avarpow 18324034'

bootloader_tag db 'run bootloader'
bootloader_tag_end:

protect_mode_tag db 'enter protect mode'
protect_mode_tag_end:

