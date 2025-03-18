#Compiler and flags 			We can declare variables to make the makefile more readable
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g 
SRCS = main.cc \
	chaine.cc \
	jeu.cc \
	message.cc \
	mobile.cc \
	tools.cc

OBJ = $(BUILD_DIR)/main.o \
	$(BUILD_DIR)/chaine.o \
	$(BUILD_DIR)/jeu.o \
	$(BUILD_DIR)/message.o \
	$(BUILD_DIR)/mobile.o \
	$(BUILD_DIR)/tools.o 

EXEC = main

# Directories
BUILD_DIR = build

all: $(BUILD_DIR) $(EXEC)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/chaine.o: chaine.cc chaine.h tools.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/jeu.o: jeu.cc jeu.h tools.h chaine.h message.h mobile.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/message.o: message.cc message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/mobile.o: mobile.cc mobile.h message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tools.o: tools.cc tools.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cc jeu.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

clean: 
	@echo "*** EFFACE OBJET ET EXECUTABLE ***"
#@rm -rf $(BUILD_DIR) $(EXEC)
	@$(BUILD_DIR)/bin/rm -f *.o *.x *.cc~ *.h~
	

#forcer la recompilation complete
rebuild: clean all 