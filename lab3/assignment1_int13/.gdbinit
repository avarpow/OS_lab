target remote:1234
break *0x7c00
break *0x7e00
layout src
add-symbol-file mbr.symbol 0x7c00
add-symbol-file bootloader.symbol 0x7e00
break brk
fs cmd
b *0x7e00
b protect_mode_begin
display $al
display $ah
display $esi
c