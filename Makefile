CC = gcc
CFLAGS = -o

EXECUTABLE = main

LIB = objLib


ifeq ($(OS),Windows_NT) 
	REMOVE = del /f
else
	REMOVE = rm -rf
endif


all: $(EXECUTABLE)

test:
	$(CC) $(CFLAGS) test.exe test.c

$(EXECUTABLE):
	$(CC) $(CFLAGS) $(EXECUTABLE) main.c $(LIB).c

clean:
	$(REMOVE) *.exe *.o *.ppm $(EXECUTABLE)
