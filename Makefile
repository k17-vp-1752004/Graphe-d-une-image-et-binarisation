# define compiler
CC= g++

# define compile flag
CCFLAGS= -std=c++14 -Wall -g

# define target file
TARGET= main

# define object files (build from source files)
OBJ= image.o \
	fordfulkerson.o \
	main.o

# neu em muon chay file main, thi sua TARGET= main, roi test.o = main.o

# define rule to build object file (.o)
# from source file (.cpp) with header (.h)
.o: .cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)

# rule to run main
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@