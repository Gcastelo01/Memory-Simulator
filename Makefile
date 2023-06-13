CC=gcc
CFLAGS=-Wall
EXEC=./tp2virtual
OBJ = ./bin
INCLUDE = ./include
SRC = ./src


${EXEC}: ${OBJ} ${OBJ}/tp2virtual.o
	${CC} ${CFLAGS} ${OBJ}/*.o -o ${EXEC} ${LIB}

${OBJ}/tp2virtual.o: ${SRC}/tp2virtual.c ${OBJ}/recorder.o
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/tp2virtual.c -o ${OBJ}/tp2virtual.o

${OBJ}/recorder.o: 
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/recorder.c -o ${OBJ}/recorder.o

${OBJ}:
	mkdir bin

clean: 
	rm -rf ${OBJ}/*
	rm -rf ./instances/*
	rm tp2virtual
	clear
