CC = g++
CFLAGS = -std=c++11 -Wall

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = qap_solver

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)
