# Baphomet

# Version
VERSION = 0.0

# Project Name
NAME = baphomet

# Includes and Libs
INCS = -Iinclude -I/usr/local/include -I/usr/include/libxml2
LIBS = -L/usr/local/lib -lxml2 -lglfw -lGL -lm -lcglm -lpcre -lpng -lsndfile -ldl -logg -lvorbis -lportaudio -lpthread

# Flags
CFLAGS = ${INCS} -rdynamic
LDFLAGS = ${LIBS}

# Compiler & Platform/Architecture
CC = gcc
PLATFORM = $(shell uname -s)
ARCHITECTURE = $(shell uname -m)

# Directiories containing various types of file
BUILD_DIR := ./build
SRC_DIRS := ./assets/scripts ./engine

# Files to manipulate
SRC := main.c $(shell find $(SRC_DIRS) -name '*.c')
OBJ := $(SRC:%=$(BUILD_DIR)/%.o)

all: options ${SO} build

options:
	@echo gmsNEO build options:
	@echo "CFLAGS	= ${CFLAGS}"
	@echo "LDFLAGS	= ${LDFLAGS}"
	@echo "CC	= ${CC}"
	@echo "PLATFORM = ${PLATFORM}"
	@echo "ARCHITECTURE = ${ARCHITECTURE}"

# For every .c.so in ${SO} compile its .c

${BUILD_DIR}/%.c.o: %.c
	mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

build: ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${LDFLAGS}

clean:
	rm -r ${BUILD_DIR}
	rm -r ${SO}
	rm ${NAME}

.PHONY: all options clean
