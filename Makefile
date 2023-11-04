CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
SOURCES = library.c main.c
EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LIBS)

clean:
	rm -f $(EXECUTABLE)