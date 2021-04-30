main.out: main.o asm_func.o rs_func.o
	g++ -o main.out main.o asm_func.o rs_func.o -m32  -lpthread -ldl
rs_func.o: rs_func.rs
	rustc rs_func.rs  --target=i686-unknown-linux-gnu --crate-type=staticlib -o rs_func.o
main.o: main.cpp
	g++ -o main.o -m32 -c main.cpp
asm_func.o: asm_func.asm
	nasm -o asm_func.o -f elf32 asm_func.asm
clean:
	rm *.o & rm *.out & rm *.a
run: main.out
	./main.out