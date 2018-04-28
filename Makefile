# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC=g++
#Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS_COMPILE=-c -O3 -Wall -Wextra -pedantic
CFLAGS_LINK=-lsfml-graphics -lsfml-window -lsfml-system

all: main.o
	$(CC) $(CFLAGS_LINK) main.o -o fight

hello: main.o
	$(CC) $(CFLAGS_LINK) main.o -o fight

main.o: main.cpp
	$(CC) $(CFLAGS_COMPILE) main.cpp

clean:
	rm -rf *.o hello
