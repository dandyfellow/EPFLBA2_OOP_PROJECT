#structure
#target: dependencies
#    command

main: main.o tools.o# main.o is a dependency of main. Main is the target.
	g++ -o main main.o tools.o
# g++ -o main main.o is the command to create the target main from the dependency main.o

#We can declare variables to make the makefile more readable
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g#compiler flags for warnings and standard selection
SRCS = main.cpp utils.cpp #list of all source files
OBJ = main.o utils.o #list of all object files
EXEC = main #name of the final executable

#compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


//nouveau makefile

 # Définir le compilateur et les options de compilation
CC = g++                 # Nom du compilateur (tu peux le changer si tu veux utiliser un autre compilateur)
CFLAGS = -Wall           # Options de compilation (ici, affichage des avertissements)

# Répertoires
SRC_DIR = src            # Répertoire contenant les fichiers source .cpp
OBJ_DIR = obj            # Répertoire où seront stockés les fichiers objets .o
BIN_DIR = bin            # Répertoire où sera stocké l'exécutable final

# Nom de l'exécutable
EXEC = $(BIN_DIR)/mon_programme  # Remplace "mon_programme" par le nom de ton exécutable

# Fichiers source (ici, tous les fichiers .cpp dans src)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)  # Trouve tous les fichiers .cpp dans le répertoire src

# Fichiers objets (correspondants aux fichiers source)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)  # Remplace les .cpp par .o dans le répertoire obj

# Cible par défaut (tout construire)
all: $(EXEC)

# Règle pour l'exécutable
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)  # Lier les fichiers objets pour créer l'exécutable

# Règle pour compiler les fichiers .cpp en fichiers .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@  # Compiler chaque fichier .cpp en .o dans le répertoire obj

# Cible pour nettoyer les fichiers générés
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)  # Supprimer les fichiers objets et l'exécutable