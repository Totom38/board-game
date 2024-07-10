CC = gcc
CFLAGS = -Wall -I../../include
LDFLAGS = 
SRC = experience1.c corner_fit.c ../../src/board.c ../../src/tetromino.c
OBJ = $(SRC:.c=.o)
EXEC = experience1

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: clean