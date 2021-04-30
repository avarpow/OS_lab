main.out: main.o c_func.o cpp_func.o asm_func.o rs_func.o
	g++ -o main.out main.o c_func.o cpp_func.o asm_func.o rs_func.o -m32
c_func.o: c_func.c
	gcc -o c_func.o -m32 -c c_func.c
cpp_func.o: cpp_func.cpp
	g++ -o cpp_func.o -m32 -c cpp_func.cpp 
rs_func.o: rs_func.rs
	rustc rs_func.rs --emit obj --target=i686-unknown-linux-gnu --crate-type staticlib
main.o: main.cpp
	g++ -o main.o -m32 -c main.cpp
asm_func.o: asm_func.asm
	nasm -o asm_func.o -f elf32 asm_func.asm
run: main.out
	./main.out
clean:
	rm *.o
	rm *.out