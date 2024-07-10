#ifndef __CORNER_FIT_H
#define __CORNER_FIT_H

#include "../../include/tetromino.h"
#include "../../include/board.h"


/*@requires a et b les elements a vérifier et taille*taille la taille du tableau espace
@assignes rien
@ensures Si (a,b) est présent dans espace la fonction renvoie 1 et si non elle renvoie 0
*/
int** create_tableau(int taille1, int taille2);



/* @requires un board b, ligne<taille, colonne<taille, taille du plateau, un tableau 
@assigns espace 
@ensures retourne la taille de l'espace a la place (ligne, colonne) */
int taille_espace(board b, int ligne, int colonne, int taille, int ** espace);



/* @requires un tableau (de tableau)
@assigns tab
@ensures on reinitialise le tableau a NULL */
void reinitialise_tab(int ** tab);



/* @requires un tableau (de tableau), 3 entiers (correspondant aux coordonnees de la place ou on peut mettre le tetromino et le numero du tetromino) 
@assigns tab 
@ensures on remplit une colonne du tableau */
void add_tab(int ** tab, int i, int j, int k);



/* @requires un tableau (de tableau)
@assigns rien 
@ensures retourne le maximum de la colonne 0 du tableau */
int maximum(int ** tab);


/* @requires taille est pair
@assigns rien 
@ensures retourne la distance par rapport au milieu */
int distance_milieu(int taille, int j);


/* @requires taille est pair
@assigns rien 
@ensures retourne le score associé au tetromino placé (c'est à dire celui qui ) */
int corner_fit(board b, int taille, int nb_tetro_bag);



#endif
