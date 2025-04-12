#Compiler and flags
OUT = projet
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g 
#CXXFLAGS = -Wall -std=c++17 this one was in the new makefile provided in rendu 2
#LINKING = `pkg-config --cflags gtkmm-4.0`
#LDLIBS = `pkg-config --libs gtkmm-4.0`
CXXFILES = projet.cc \
	chaine.cc \
	jeu.cc \
	message.cc \
	mobile.cc \
	tools.cc \
	graphic.cc \
	gui.cc

OFILES = $(CXXFILES:.cc=.o)

all: $(OUT) 

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

graphic.o: graphic.cc graphic_gui.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ 

gui.o: gui.cc graphic_gui.h graphic.h gui.h jeu.h tools.h constantes.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ 

projet.o: projet.cc gui.h jeu.h graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ 

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o $@

#$(OUT): $(OFILES) -> replace witth this once gtkm is installed
#	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

# Detect Windows OS
IS_WINDOWS := $(OS)

clean: 
	@echo "*** EFFACE OBJET ET EXECUTABLE ***"
ifeq ($(IS_WINDOWS),Windows_NT)  # Windows
	@if exist $(OUT) del /q $(OUT)  
	@del /q /f *.o *.x *.cc~ *.h~ 2>nul *.exe
else  # Linux/macOS
#	@rm -f $(OUT)
#	@rm -f *.o *.x *.cc~ *.h~ *.exe //old makefile version

	@/bin/rm -f *.o *.x *.cc~ *.h~ $(OUT)
endif


#forcer la recompilation complete
rebuild: clean all 

# pour max (utile pour faire tourner mingw sur le terminal MSYS2)
# cd /c/Users/maxwc/git/IT_ProjectTest
# mingw32-make
