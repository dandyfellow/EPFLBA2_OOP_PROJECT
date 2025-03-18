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

all: check_build $(EXEC)

check_build:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		echo "Erreur: Le dossier $(BUILD_DIR) n'existe pas. Créez-le avec 'mkdir $(BUILD_DIR)'"; \
		exit 1; \
	fi
$(BUILD_DIR)/chaine.o: chaine.cc chaine.h tools.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/jeu.o: $(MODULE_DIR)/jeu/jeu.cc $(MODULE_DIR)/keu/jeu.h $(MODULE_DIR)/tools/tools.h $(MODULE_DIR)/chaine/chaine.h $(MODULE_DIR)/message/message.h $(MODULE_DIR)/mobile/mobile.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/message.o: $(MODULE_DIR)/message/message.cc $(MODULE_DIR)/message/message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/mobile.o: $(MODULE_DIR)/mobile/mobile.cc $(MODULE_DIR)/mobile/mobile.h $(MODULE_DIR)/message/message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tools.o: $(MODULE_DIR)/tools/tools.cc $(MODULE_DIR)/tools/tools.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cc $(MODULE_DIR)/jeu/jeu.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main: $(MODULE_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

clean: 
	@echo "*** EFFACE MODULES OBJET ET EXECUTABLE ***"
#inutile @/bin/rm -f *.o *.x *.cc~ *.h~
	@rm -rf $(BUILD_DIR) $(EXEC)

#forcer la recompilation complete
rebuild: clean all 