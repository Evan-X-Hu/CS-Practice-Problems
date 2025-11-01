CC=gcc
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g
TARGET = 268

${TARGET}: 268.o linkedlist.o
	${CC} ${LFLAGS} 268.o linkedlist.o -o ${TARGET}

268.o: 268.c
	${CC} ${CFLAGS} 268.c

linkedlist.o: linkedlist.c
	${CC} ${CFLAGS} linkedlist.c

clean:
	rm -rf ${TARGET}
	rm -rf *.o