# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=g++
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS_COMPILE=-c -Wall -Wextra -pedantic
CFLAGS_OPTIMISE=-O3
CFLAGS_LINK=-lsfml-graphics -lsfml-window -lsfml-system

all: main.cpp
	$(CC) $(CFLAGS_COMPILE) main.cpp

release: main.cpp
	$(CC) $(CFLAGS_COMPILE) $(CFLAGS_OPTIMISE) main.cpp

link: main.o
	$(CC) $(CFLAGS_LINK) main.o -o fight

run: main.cpp
	$(CC) $(CFLAGS_COMPILE) main.cpp && $(CC) $(CFLAGS_LINK) main.o -o fight && ./fight

clean:
	rm -rf *.o fight
