.PHONY:clean build debug run
clean:
	@touch 1.bin
	@touch 1.img
	@rm *.bin
	@rm *.img
build:clean
	@nasm -o mbr.o -g -f elf32 mbr.asm 
	@ld -o mbr.symbol -melf_i386 -N mbr.o -Ttext 0x7c00
	@ld -o mbr.bin -melf_i386 -N mbr.o -Ttext 0x7c00 --oformat binary
	@nasm -o bootloader.o -g -f elf32 bootloader.asm 
	@ld -o bootloader.symbol -melf_i386 -N bootloader.o -Ttext 0x7e00
	@ld -o bootloader.bin -melf_i386 -N bootloader.o -Ttext 0x7e00 --oformat binary
	@nasm -f bin bootloader.asm -g -o bootloader.bin
	@dd if=mbr.bin of=hd.img bs=512 count=1 seek=0 conv=notrunc
	@dd if=bootloader.bin of=hd.img bs=512 count=5 seek=1 conv=notrunc
run:build
	@qemu-system-i386 -hda hd.img -serial null -parallel stdio
debug: build
	@qemu-system-i386 -hda hd.img -serial null -parallel stdio -s -S
