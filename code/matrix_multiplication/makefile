CC = g++
CFLAGS = -Wall -O3
LIBS = -lpsapi
TARGET = matrix_exec
SRC = matrix_multiplication.cpp

all: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)
clean:
	rm -f $(TARGET)