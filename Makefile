CXX = g++
CXXFLAGS = -I. -std=c++17 -MMD -MP

SRC = $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all
