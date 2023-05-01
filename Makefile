# GmsNEO

# Version
VERSION = 0.0

# Project Name
NAME = default

# Includes and Libs
INCS = 
LIBS = 

# Flags
CFLAGS = ${INCS}
LDFLAGS = ${LIBS}

# Compiler
CC = gcc-12

SRC = default.c $(engine/*.c) $(objects/*/*.c) $(scripts/*.c)
OBJ = ${SRC:.c=.o}

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
