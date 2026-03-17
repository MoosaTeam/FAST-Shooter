CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -I/opt/sfml2/include
LDFLAGS = -L/opt/sfml2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -Wl,-rpath=/opt/sfml2/lib

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = game_build

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
