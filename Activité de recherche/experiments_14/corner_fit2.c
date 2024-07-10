#include "corner_fit2.h"
#include "../include/board.h"
#include "../include/tetromino.h"

int* corner_fit2(board* b, int num_pieces) {
    int min_distance = 100;
    int* best_position = NULL;
    int* best_corner = NULL;

    // Coins du plateau
    int corners[4][2] = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};

    // Parcourir tous les tétraminos dans le sac
    tetromino** bag = list_tetrominos_in_bag(b);
    for (int i = 0; i < num_pieces; i++) {
        // Obtenir les cellules du tétraminos actuel
        int* cells = get_cells(bag[i]);

        // Parcourir les cellules du tétraminos pour trouver la plus proche du coin
        for (int j = 0; j < 8; j += 2) {
            int row = cells[j];
            int col = cells[j + 1];
            
            // Parcourir tous les coins du plateau
            for (int k = 0; k < 4; k++) {
                int corner_row = corners[k][0];
                int corner_col = corners[k][1];

                // Calculer la distance en norme 1 jusqu'au coin
                int distance = abs(row - corner_row) + abs(col - corner_col);

                // Mettre à jour la meilleure position et le meilleur coin si la distance est plus petite
                if (distance < min_distance) {
                    min_distance = distance;
                    // Sauvegarder la position de la cellule la plus proche du coin
                    best_position = &cells[j];
                    // Sauvegarder le coin le plus proche
                    best_corner = corners[k];
                }
            }
        }

    
        
        // Libérer la mémoire allouée pour les cellules du tétraminos actuel
        free(cells);
    }

    // Retourner la meilleure position trouvée
    return best_position;
}
