#structure
#target: dependencies
#    command

main: main.o tools.o# main.o is a dependency of main. Main is the target.
	g++ -o main main.o tools.o
# g++ -o main main.o is the command to create the target main from the dependency main.o

#We can declare variables to make the makefile more readable
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 #compiler flags for warnings and standard selection
SRCS = main.cpp utils.cpp #list of all source files
OBJ = main.o utils.o #list of all object files
EXEC = main #name of the final executable

#compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@