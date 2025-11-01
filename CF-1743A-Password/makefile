CC=gcc
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g
TARGET = 1743A

${TARGET}: 1743A.o dict.o
	${CC} ${LFLAGS} 1743A.o dict.o -o ${TARGET}

1743A.o: 1743A.c
	${CC} ${CFLAGS} 1743A.c

dict.o: dict.c
	${CC} ${CFLAGS} dict.c

clean:
	rm -rf ${TARGET}
	rm -rf *.o