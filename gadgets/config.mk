# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
INCS = -I. -I${X11INC}

X11LIB = /usr/X11R6/lib

CFLAGS += -O2 ${INCS} 
LDFLAGS += ${LIBS}

# compiler and linker
CC ?= gcc
LD = ${CC}
