# Makefile

CFLAGS = -Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2
OBJ = ma.o memory_tests.o links.o
LIBFLAGS = -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=reallocarray -Wl,--wrap=free -Wl,--wrap=strdup -Wl,--wrap=strndup -shared -o


.PHONY: all, clean, clean_obj
all: komunikat ma_example

komunikat:
	@echo "Tworzenie wszystkich plikow"

ma_example: libma.so ma_example.c
	gcc $(CFLAGS) -o ma_example ma_example.c -L. -lma -Wl,-rpath=.

libma.so: $(OBJ)
	gcc $(LIBFLAGS) libma.so $(OBJ)
	@echo "Stworzono libma.so"

ma.o: ma.c ma.h
	gcc $(CFLAGS) -c -o $@ $<

links.o: links.c links.h
	gcc $(CFLAGS) -c -o $@ $<

memory_tests.o: memory_tests.c memory_tests.h
	gcc $(CFLAGS) -c -o $@ $<

clean:
	@echo "Usuwanie wszystkich plikow"
	rm -f *.o
	rm -f libma.so
	rm -f ma_example

clean_obj:
	@echo "Usuwanie plikow obiektowych"
	rm -f *.o
