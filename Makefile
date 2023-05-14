# GmsNEO

# Version
VERSION = 0.0

# Project Name
NAME = executable

# Includes and Libs
INCS = -Iinclude 
LIBS = -lglfw -lGL -lm -lpng

# Flags
CFLAGS = ${INCS}
LDFLAGS = ${LIBS}

# Compiler
CC = gcc

SRC = main.c engine/glad.c engine/media.c engine/input.c engine/mesh.c engine/graphics.c engine/draw.c engine/shaders.c
OBJ = main.o glad.o media.o shaders.o mesh.o draw.o input.o graphics.o
#OBJ = ${SRC:.c=.o}

all: options build

options:
	@echo gmsNEO build options:
	@echo "CFLAGS	= ${CFLAGS}"
	@echo "LDFLAGS	= ${LDFLAGS}"
	@echo "CC	= ${CC}"

.c.o:
	${CC} -c ${CFLAGS} ${SRC}

build: ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${LDFLAGS}

clean:
	rm -f ${NAME} ${OBJ}

.PHONY: all options clean
