CC=gcc
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g
TARGET=1117

${TARGET}: 1117.o
	${CC} ${LFLAGS} 1117.o -o ${TARGET}

1117.o: 1117.c
	${CC} ${CFLAGS} 1117.c

clean:
	rm -rf ${TARGET}
	rm -rf *.o