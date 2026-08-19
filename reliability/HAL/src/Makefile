CXX := g++

CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

TARGET := temperature_monitor

SRCS := main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
