nasm -g -f bin $1.asm -o $1.bin && dd if=$1.bin of=hd.img bs=512 count=1 seek=0 conv=notrunc && qemu-system-i386 -hda hd.img -serial null -parallel stdio

