org 7c00h
[bits 16]
echo:
    mov ah,0
    int 0x16
    mov dl,al
    mov ah,0x0e
    int 0x10
    jmp echo

times 510 - ($ - $$) db 0
db 0x55, 0xaa