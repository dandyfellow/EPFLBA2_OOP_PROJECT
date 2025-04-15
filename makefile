#Compiler and flags
OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++17
LINKING = `pkg-config --cflags gtkmm-4.0`
LDLIBS = `pkg-config --libs gtkmm-4.0`
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
	$(CXX) $(CXXFLAGS) $(LINKING)  -c $< -o $@

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

#$(OUT): $(OFILES) -> old makefile version
#	$(CXX) $(CXXFLAGS) $(OFILES) -o $@

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

# Always use Unix tools in MSYS2
RM = /bin/rm -f
NULL = /dev/null

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ $(OUT)


#forcer la recompilation complete
rebuild: clean all 

# pour maxwc (utile pour faire tourner mingw sur le terminal MSYS2)
# cd /c/Users/maxwc/git/EPFLBA2_OOP_PROJECT
# mingw32-make
