# GmsNEO

# Version
VERSION = 0.0

# Project Name
NAME = executable

# Includes and Libs
INCS = -Iinclude 
LIBS = -lglfw -lGL

# Flags
CFLAGS = ${INCS}
LDFLAGS = ${LIBS}

# Compiler
CC = gcc

SRC = default.c engine/glad.c 
OBJ = default.o glad.o
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
