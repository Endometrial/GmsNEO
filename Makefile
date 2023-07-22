# Baphomet

# Version
VERSION = 0.0

# Project Name
NAME = baphomet

# Includes and Libs
INCS = -Iinclude -I/usr/local/include
LIBS = -L/usr/local/lib -lxml2 -lglfw -lGL -lm -lcglm -lpcre -lpng -ldl -logg -lvorbis -lportaudio -lpthread

# Flags
CFLAGS = ${INCS} -rdynamic
SOFLAGS = -shared -fPIC -undefined dynamic_lookup ${INCS} ${LIBS}
LDFLAGS = ${LIBS}

# Compiler & Platform/Architecture
CC = gcc-13
PLATFORM = $(shell uname -s)
ARCHITECTURE = $(shell uname -m)

# Directiories containing various types of file
BUILD_DIR := ./build
SRC_DIRS := ./assets/scripts ./engine
SO_DIRS := ./assets/objects

# Files to manipulate
SO_SRC := $(shell find $(SO_DIRS) -name '*.c')
SO := $(SO_SRC:%=%.so)
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
${SO}: %.c.so :%.c
	${CC} ${SOFLAGS} $< -o $@

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
