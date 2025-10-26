.PHONY: all
all: testerka

testerka: testerka.o nsqrt.o
	g++ -z noexecstack -o testerka testerka.o nsqrt.o -lgmp

testerka.o:
	g++ -c -Wall -Wextra -std=c++20 -O2 -o testerka.o testerka.cpp

nsqrt.o:
	nasm -f elf64 -w+all -w+error -o nsqrt.o nsqrt.asm

clean:
	rm -rf *.o
	rm testerka