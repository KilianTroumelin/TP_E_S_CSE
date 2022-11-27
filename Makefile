CC=gcc
CFLAGS=-Wall -g -O0 -fno-stack-protector
LDLIBS=-unistd
RM=rm -f

all : eval-libc test-format test-rand test test-stdes test-ffunction test-syscall test-stdes_buff clean

stdes : stdes.o 
	$(CC) $(CFLAGS) -o stdes stdes.o $(LDLIBS)

stdes.o : stdes.c stdes.h
	$(CC) -c $(CFLAGS) -o stdes.o stdes.c

eval-libc : eval-libc.o stdes.o
	$(CC) $(CFLAGS) -o eval-libc eval-libc.o stdes.o

eval-libc.o : eval-libc.c stdes.h
	$(CC) -c $(CFLAGS) -o eval-libc.o eval-libc.c

eval-syscall : eval-syscall.o stdes.o
	$(CC) $(CFLAGS) -o eval-syscall eval-syscall.o stdes.o $(LDLIBS)

eval-syscall.o : eval-syscall.c stdes.h
	$(CC) -c $(CFLAGS) -o eval-syscall.o eval-syscall.c

test-format : test-format.o stdes.o
	$(CC) $(CFLAGS) -o test-format test-format.o stdes.o $(LDLIBS)

test-format.o : test-format.c stdes.h
	$(CC) -c $(CFLAGS) -o test-format.o test-format.c

test-rand : test-rand.o stdes.o
	$(CC) $(CFLAGS) -o test-rand test-rand.o stdes.o $(LDLIBS)

test-rand.o : test-rand.c stdes.h
	$(CC) -c $(CFLAGS) -o test-rand.o test-rand.c

test : test.o stdes.o
	$(CC) $(CFLAGS) -o test test.o stdes.o $(LDLIBS)

test.o : test.c stdes.h
	$(CC) -c $(CFLAGS) -o test.o test.c

test-stdes : test-stdes.o stdes.o 
	$(CC) $(CFLAGS) -o test-stdes test-stdes.o stdes.o $(LDLIBS)

test-stdes.o : test-stdes.c stdes.h 
	$(CC) -c $(CFLAGS) -o test-stdes.o test-stdes.c

test-ffunction : test-ffunction.o stdes.o 
	$(CC) $(CFLAGS) -o test-ffunction test-ffunction.o stdes.o $(LDLIBS)

test-ffunction.o : test-ffunction.c stdes.h 
	$(CC) -c $(CFLAGS) -o test-ffunction.o test-ffunction.c

test-syscall : test-syscall.o
	$(CC) $(CFLAGS) -o test-syscall test-syscall.o $(LDLIBS)

test-syscall.o : test-syscall.c
	$(CC) -c $(CFLAGS) -o test-syscall.o test-syscall.c

test-stdes_buff : test-stdes_buff.o stdes.o 
	$(CC) $(CFLAGS) -o test-stdes_buff test-stdes_buff.o stdes.o $(LDLIBS)

test-stdes_buff.o : test-ffunction.c stdes.h 
	$(CC) -c $(CFLAGS) -o test-stdes_buff.o test-stdes_buff.c

clean : 
	$(RM) *.o