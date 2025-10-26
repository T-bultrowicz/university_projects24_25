.PHONY: all clean
all: freverse gen
freverse: freverse.o
	ld -g --fatal-warnings -o freverse freverse.o
freverse.o: freverse.asm
	nasm -g -f elf64 -w+all -w+error -w-unknown-warning -w-reloc-rel -o freverse.o freverse.asm
gen: wpisz.cpp
	g++ -o gen wpisz.cpp
clean:
	rm -rf *.o
	rm -rf gen
	rm -rf freverse
	rm dane.txt
	rm wzorzec.txt

