# Named Pipe - FIFO

.PHONY: all clean

all: clean
	gcc -o producer producer.c
	gcc -o consumer consumer.c

clean:
	rm -rf producer consumer fifo
