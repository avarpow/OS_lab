main.out: main.o c_func.o cpp_func.o asm_func.o rs_func.a
	g++ -o main.out main.o c_func.o cpp_func.o asm_func.o rs_func.a -m32 -lpthread -ldl
c_func.o: c_func.c
	gcc -o c_func.o -m32 -c c_func.c
cpp_func.o: cpp_func.cpp
	g++ -o cpp_func.o -m32 -c cpp_func.cpp 
rs_func.a: rs_func.rs
	rustc rs_func.rs  --target=i686-unknown-linux-gnu --crate-type=staticlib -o rs_func.a
main.o: main.cpp
	g++ -o main.o -m32 -c main.cpp
asm_func.o: asm_func.asm
	nasm -o asm_func.o -f elf32 asm_func.asm
clean:
	rm *.o & rm *.out & rm *.a
run: main.out
	./main.out