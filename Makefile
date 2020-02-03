CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
LIBS = -lm

OBJ =\
	./src/main.c \
	./src/init.c \
	./src/common.c \
	./src/update.c \

all: main

clean:
	rm -f Game a.out

.c.o:
	$(CC) -c $(INCLUDES) $(CFLAGS) $<

main: $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(CFLAGS) -o Game