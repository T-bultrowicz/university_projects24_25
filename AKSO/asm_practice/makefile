.PHONY: all

all: parametr

parametr: parametr.o
	ld -o parametr parametr.o

parametr.o: parametr.asm
	nasm -f elf64 -w+all -w+error -o parametr.o parametr.asm