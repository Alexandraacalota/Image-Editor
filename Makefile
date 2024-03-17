#Calota Alexandra-Maria, grupa 314CA
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

build:
	$(CC) $(CFLAGS) main.c -lm -o image_editor
	
pack:
	zip -FSr 314CA_CalotaAlexandraMaria_Tema3.zip README Makefile *.c *.h

clean:
	rm -f image_editor

