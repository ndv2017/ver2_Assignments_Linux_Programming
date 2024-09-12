.PHONY: all clean

FLAG	:=	-lrt
CC		:=	gcc

all:
	$(CC) -o sendmsg sendmsg.c $(FLAG)
	$(CC) -o retrievemsg retrievemsg.c $(FLAG)
	$(CC) -o main main.c $(FLAG)

clean:
	rm -rf sendmsg retrievemsg main
