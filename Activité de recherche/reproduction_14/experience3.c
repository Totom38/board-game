#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/board.h"
#include "../../include/tetromino.h"
#include "corner_fit.h"

void experience3(int nombre_plateaux, int taille_plateau, int taille_sac) {
    // Initialiser la graine pour les nombres aléatoires
    srand(time(NULL));
    
    printf("Types de Tetrominos\tScore moyen\tTemps moyen (s)\n");
    
    // Définir les types de tetrominos à tester
    int tetrominos_types[7] = {0, 1, 2, 3, 4, 5, 6}; // Types de tetrominos (I, O, T, L, J, S, Z)
    
    // Tester chaque combinaison de deux types de tetrominos
    for (int i = 0; i < 6; i++) {
        for (int j = i + 1; j < 7; j++) {
            int type1 = tetrominos_types[i];
            int type2 = tetrominos_types[j];
            
            // Initialiser les statistiques pour cette combinaison de types
            int total_points = 0;
            int parties_reussies = 0;
            double total_time = 0.0;
            
            for (int k = 0; k < nombre_plateaux; k++) {
                // Créer un nouveau plateau de la taille spécifiée
                board b = create_board(taille_plateau, taille_plateau, 0);  // Assume that '0' initializes the board to an empty state
                
                // Remplir le sac avec des tetrominos des types spécifiés
                for (int l = 0; l < taille_sac; l++) {
                    int type = (rand() % 2 == 0) ? type1 : type2;
                    tetromino t = create_tetromino(type, 0, 10);
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
            
            // Calculer les statistiques pour cette combinaison de types
            double score_moyen = (double) total_points / nombre_plateaux;
            double temps_moyen = total_time / nombre_plateaux;
            
            // Afficher les résultats pour cette combinaison de types
            printf("(%d, %d)\t\t\t%.2f\t\t%.4f\n", type1, type2, score_moyen, temps_moyen);
        }
    }
}

// Exemple d'utilisation de la fonction
int main() {
    int nombre_plateaux = 10;  // Par exemple, 100 parties
    int taille_plateau = 10;    // Par exemple, un plateau de taille 10x10
    int taille_sac = 7;         // Par exemple, 7 tetrominos dans le sac
    
    experience3(nombre_plateaux, taille_plateau, taille_sac);
    
    return 0;
}
