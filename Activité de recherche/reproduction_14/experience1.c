#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/board.h"
#include "../../include/tetromino.h"
#include "corner_fit.h"

void experience1(int nombre_plateaux, int nombre_tetrominos) {
    // Initialiser la graine pour les nombres aléatoires
    srand(time(NULL));
    
    printf("Taille du tableau\tScore moyen\tTemps moyen (s)\n");
    
    for (int taille = 1; taille <= 20; taille++) {
        // Initialiser les statistiques pour cette taille
        int total_points = 0;
        int parties_reussies = 0;
        double total_time = 0.0;
        
        for (int i = 0; i < nombre_plateaux; i++) {
            // Créer un nouveau plateau de la taille spécifiée
            board b = create_board(taille, taille, 0);  // Assume that '0' initializes the board to an empty state
            
            // Remplir le sac avec des tetrominos
            for (int j = 0; j < nombre_tetrominos; j++) {
                tetromino t = create_random_tetromino();
                add_tetromino_to_bag(t, b);
            }
            
            // Mesurer le temps de l'algorithme corner_fit
            clock_t start_time = clock();
            int points = corner_fit(b, taille, nombre_tetrominos);
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
        
        // Calculer les statistiques pour cette taille
        double score_moyen = (double) total_points / nombre_plateaux;
        double temps_moyen = total_time / nombre_plateaux;
        
        // Afficher les résultats pour cette taille
        printf("%d\t\t\t%.2f\t\t%.4f\n", taille, score_moyen, temps_moyen);
    }
}

// Exemple d'utilisation de la fonction
int main() {
    int nombre_plateaux = 100;  // Par exemple, 100 parties
    int nombre_tetrominos = 7;  // Par exemple, 7 tetrominos dans le sac
    
    experience1(nombre_plateaux, nombre_tetrominos);
    
    return 0;
}
