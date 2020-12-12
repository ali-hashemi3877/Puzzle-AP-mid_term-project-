CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/main.o ./obj/Puzzle.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/Puzzle.o: ./cpp/Puzzle.cpp
	$(CXX) $(CXXFLAGS) ./cpp/Puzzle.cpp -o ./obj/Puzzle.o
./obj/main.o: ./cpp/main.cpp ./h/Puzzle.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
