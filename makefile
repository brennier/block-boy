CC = gcc
CFLAGS = -O3 --std=c99 -Wall
LIBS = lib
INCLUDES = include
LFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
OUTPUT = game

${OUTPUT}: main.o
	${CC} $^ -o ${OUTPUT} -L ${LIBS} ${LFLAGS}

main.o: main.c
	${CC} $^ -c -I ${INCLUDES}

clean:
	@echo "Cleaning up all files.."
	rm *.o ${OUTPUT}

run: ${OUTPUT}
	./${OUTPUT}
	rm *.o ${OUTPUT}
