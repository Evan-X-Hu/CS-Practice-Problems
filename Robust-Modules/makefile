CC=gcc
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g
TARGET = moduleTester

${TARGET}: moduleTester.o intArrInput.o printIntArr.o printStrArr.o
	${CC} ${LFLAGS} moduleTester.o intArrInput.o printIntArr.o printStrArr.o -o ${TARGET} -lm

moduleTester.o: moduleTester.c
	${CC} ${CFLAGS} moduleTester.c

intArrInput.o: intArrInput.c
	${CC} ${CFLAGS} intArrInput.c

printIntArr.o: printIntArr.c
	${CC} ${CFLAGS} printIntArr.c

printStrArr.o: printStrArr.c
	${CC} ${CFLAGS} printStrArr.c

clean:
	rm -rf ${TARGET}
	rm -rf *.o