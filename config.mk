# dzen version
VERSION = 0.9.5-svn

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib
INCS = -I. -I${X11INC}

LIBS = -L${X11LIB}

# Solaris, uncomment for Solaris
#CFLAGS = -fast -xtarget=ultra
CFLAGS += ${INCS} -DVERSION=\"${VERSION}\"
PKG = x11

# Debugging
#CFLAGS += -std=gnu89 -pedantic -Wall -ggdb -W -Wundef -Wendif-labels -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Winline -Wdisabled-optimization -O2 -pipe

# Configure the features you want to be supported
# Uncomment: Remove # from the beginning of respective lines
# Comment  : Add # to the beginning of the respective lines

## with XFT
PKG += xft xrender
CFLAGS += -DDZEN_XFT

## with XPM
PKG += xpm
CFLAGS += -DDZEN_XPM

## with XINERAMA
PKG += xinerama
CFLAGS += -DDZEN_XINERAMA

# END of feature configuration

LIBS += `pkg-config --libs ${PKG}`
CFLAGS += `pkg-config --cflags ${PKG}`

LDFLAGS += ${LIBS}

# compiler and linker
CC ?= gcc
LD = ${CC}
