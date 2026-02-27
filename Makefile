
# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -IC:/SFML-3.0.2/include
LDFLAGS = -LC:/SFML-3.0.2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Files
SRC = sand.cpp
OUT = sand.exe

# Rules
all:
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LDFLAGS)

run: all
	./$(OUT)

clean:
	del $(OUT)

