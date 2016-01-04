# Set up basic variables:
CC = gcc
CFLAGS = -c -Wall -std=c99
LDFLAGS =

# List of sources:
SOURCES = tumblrtv.c
OBJECTS = $(SOURCES:.c=.o)

# Name of executable target:
EXECUTABLE = tumblrtv

CFLAGS += `pkg-config --cflags gdk-2.0`
CFLAGS += `pkg-config --cflags gtk+-2.0`
CFLAGS += `pkg-config --cflags webkit-1.0`
LDFLAGS += `pkg-config --libs gdk-2.0`
LDFLAGS += `pkg-config --libs gtk+-2.0`
LDFLAGS += `pkg-config --libs webkit-1.0`

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)

install:
	cp $(EXECUTABLE) $(DESTDIR)/usr/lib/xscreensaver/

