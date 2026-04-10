CC = g++
CFLAGS = -O3 -Wall
LIBS = -lpsapi

TARGET = sorting_exec

SRC = sorting.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)