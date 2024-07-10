#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/board.h"
#include "../../include/tetromino.h"
#include "corner_fit.h"

void experience2(int nombre_plateaux, int taille_plateau) {
    // Initialiser la graine pour les nombres aléatoires
    srand(time(NULL));
    
    printf("Taille du sac\tScore moyen\tTemps moyen (s)\n");
    
    for (int taille_sac = 1; taille_sac <= 20; taille_sac++) {
        // Initialiser les statistiques pour cette taille de sac
        int total_points = 0;
        int parties_reussies = 0;
        double total_time = 0.0;
        
        for (int i = 0; i < nombre_plateaux; i++) {
            // Créer un nouveau plateau de la taille spécifiée
            board b = create_board(taille_plateau, taille_plateau, 0);  // Assume that '0' initializes the board to an empty state
            
            // Remplir le sac avec des tetrominos
            for (int j = 0; j < taille_sac; j++) {
                tetromino t = create_random_tetromino();
                add_tetromino_to_bag(t, b);
            }
            
            // Mesurer le temps de l'algorithme corner_fit
            clock_t start_time = clock();
            int points = corner_fit(b, taille_plateau, taille_sac);
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            
            if (points > 0) {
                parties_reussies++;
            }
            
            total_points += points;
            total_time += elapsed_time;
            
            // Libérer la mémoire du plateau
            free_board(&b);  // Pass the address of the pointer to free the board's memory
        }
        
        // Calculer les statistiques pour cette taille de sac
        double score_moyen = (double) total_points / nombre_plateaux;
        double temps_moyen = total_time / nombre_plateaux;
        
        // Afficher les résultats pour cette taille de sac
        printf("%d\t\t%.2f\t\t%.4f\n", taille_sac, score_moyen, temps_moyen);
    }
}

// Exemple d'utilisation de la fonction
int main() {
    int nombre_plateaux = 10;  // Par exemple, 100 parties
    int taille_plateau = 10;    // Par exemple, un plateau de taille 10x10
    
    experience2(nombre_plateaux, taille_plateau);
    
    return 0;
}
