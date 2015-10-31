# Set up basic variables:
CC = gcc
CFLAGS = -c -Wall
LDFLAGS =

# List of sources:
SOURCES = tumblrtv.c
OBJECTS = $(SOURCES:.c=.o)

# Name of executable target:
EXECUTABLE = tumblrtv

CFLAGS += `pkg-config --cflags gdk-3.0`
CFLAGS += `pkg-config --cflags gtk+-3.0`
CFLAGS += `pkg-config --cflags atk`
CFLAGS += `pkg-config --cflags webkit2gtk-4.0`
LDFLAGS += `pkg-config --libs x11`
LDFLAGS += `pkg-config --libs gdk-3.0`
LDFLAGS += `pkg-config --libs gtk+-3.0`
LDFLAGS += `pkg-config --libs atk`
LDFLAGS += `pkg-config --libs webkit2gtk-4.0`
#LDFLAGS += `pkg-config --libs glib-2.0`

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
