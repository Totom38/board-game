# Nom de l'exécutable
EXEC = mon_programme

# Options de compilation
CFLAGS = -Wall -Wextra -pedantic -Ofast

# Liste des fichiers sources
SRCS = corner_fit2.c Experience1.c Experience2.c Experience3.c

# Liste des fichiers objets (remplace .c par .o)
OBJS = $(SRCS:.c=.o)

# Règle par défaut pour compiler l'exécutable
all: $(EXEC)

# Règle pour créer l'exécutable
$(EXEC): $(OBJS)
    gcc $(CFLAGS) -o $(EXEC) $(OBJS)

# Règle pour compiler les fichiers .c en .o
%.o: %.c
    gcc $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
    rm -f $(OBJS) $(EXEC)

# Règle pour exécuter le programme
run: $(EXEC)
    ./$(EXEC)

.PHONY: all clean run