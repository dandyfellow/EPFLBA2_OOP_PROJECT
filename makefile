#Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g 
SRCS = projet.cc \
	chaine.cc \
	jeu.cc \
	message.cc \
	mobile.cc \
	tools.cc

OBJ = projet.o \
	chaine.o \
	jeu.o \
	message.o \
	mobile.o \
	tools.o 

EXEC = projet

# Directories

all: $(EXEC) 

chaine.o: chaine.cc chaine.h tools.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

jeu.o: jeu.cc jeu.h tools.h chaine.h message.h mobile.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

message.o: message.cc message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

mobile.o: mobile.cc mobile.h message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

tools.o: tools.cc tools.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

projet.o: projet.cc jeu.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# Detect Windows OS
IS_WINDOWS := $(OS)

clean: 
	@echo "*** EFFACE OBJET ET EXECUTABLE ***"
ifeq ($(IS_WINDOWS),Windows_NT)  # Windows
	@if exist $(EXEC) del /q $(EXEC)  
	@del /q /f *.o *.x *.cc~ *.h~ 2>nul *.exe
else  # Linux/macOS
	@rm -f $(EXEC)
	@rm -f *.o *.x *.cc~ *.h~ *.exe
endif


#forcer la recompilation complete
rebuild: clean all 