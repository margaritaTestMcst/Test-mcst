CC = gcc

SRC = $(shell find . -name "*.c")

all: task5

task5: $(SRC)
	$(CC) -O2 -Wall -Wextra  $(CFLAGS) $(SRC) -o task5 

clean:
	rm -f task5
