CFLAGS=-Wall
LIBS=-pthread -I/usr/local/include  -L/usr/local/lib -lcheck

all: romanmath

romanmath: main.o romancalc.o
	gcc -o romanmath main.o romancalc.o

main.o: main.c romancalc.h
	gcc $(CFLAGS) -c main.c

romancalc.o: romancalc.c romancalc.h
	gcc $(CFLAGS) -c romancalc.c

test: test_romanmath
	./test_romanmath

test_romanmath: check_romancalc.o romancalc.o
	gcc -o test_romanmath romancalc.o check_romancalc.o $(LIBS)

check_romancalc.o: check_romancalc.c romancalc.h
	gcc $(CFLAGS) -c check_romancalc.c
