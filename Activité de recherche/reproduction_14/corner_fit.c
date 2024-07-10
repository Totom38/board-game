#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "../../include/board.h"
#include "../../include/tetromino.h"
#include "corner_fit.h"


/*@requires taille>=0
@assignes rien
@ensures renvoie un tableau avec des -1
*/
int** create_tableau(int taille1, int taille2){
    int** espace = malloc(taille1*sizeof(int*));
    for(int i=0; i<taille1; i++){
        espace[i]=malloc(taille2*sizeof(int));
    }
    for(int i=0; i<taille1; i++){
        for(int j=0; j<taille2; j++){
            espace[i][j]=-1;
        }
    }
    return espace;
}

/* @requires un board b, ligne<taille, colonne<taille, taille du plateau, un tableau 
@assigns espace 
@ensures retourne la taille de l'espace a la place (ligne, colonne) */
int taille_espace(board b, int ligne, int colonne, int taille, int ** espace){
    if(ligne>taille-1 || colonne>taille-1 || ligne<0 || colonne<0){
        return 0;
    }
    else if (get_tetromino(b, ligne, colonne)== NULL && espace[ligne][colonne]==-1){
        espace[ligne][colonne]=1;
        return 1 + taille_espace(b, ligne-1, colonne,taille, espace)+taille_espace(b, ligne, colonne-1,taille, espace)+
        taille_espace(b, ligne+1, colonne,taille, espace)+taille_espace(b, ligne, colonne+1,taille, espace);
    }
    else{
        return 0;
    }
}

/* @requires un tableau (de tableau)
@assigns tab
@ensures on reinitialise le tableau a NULL */
void reinitialise_tab(int ** tab) {
    int i = 0;
    while (tab[i][0] != -1) {
        for (int k = 0; k<3; k++) {
            tab[i][k] = -1 ;
        }
        i++ ;
    }
}

/* @requires un tableau (de tableau), 3 entiers (correspondant aux coordonnees de la place ou on peut mettre le tetromino et le numero du tetromino) 
@assigns tab 
@ensures on remplit une colonne du tableau */
void add_tab(int ** tab, int i, int j, int k) {
    int l = 0;
    while (tab[l][0] != -1) {
        l++;
    }
    tab[l][0] = i;
    tab[l][1] = j;
    tab[l][2] = k;
}


/* @requires un tableau (de tableau)
@assigns rien 
@ensures retourne le maximum de la colonne 0 du tableau */
int maximum(int ** tab) {
    int max = 0;
    int i = 0;
    while (tab[i][0]!=-1) {
        if (tab[i][0] > max ) {
            max = tab[i][0];
        }
        i++;
    }
    return max;
}

/* @requires taille est pair
@assigns rien 
@ensures retourne la distance par rapport au milieu */
int distance_milieu(int taille, int j) {
    int milieu = taille/2 + 0.5;
    if (milieu > j) { return milieu-j; }
    else { return j-milieu; }
}

int corner_fit(board b, int taille, int nb_tetro_bag) {
    /* on associera a la variable min_t_espace le minimum de la taille de l'espace disponible */
    int min_t_espace = taille*taille ;
    /* on cree un tableau (de tableau) qui regroupera les coordonnees (ligne + colonne) de la place ou on peut le tetromino et le numero de celui-ci dans list_tetrominos_in_bag
            0   1   2
    ---------------------
    0   |   i   j   k
    1   |
    2   |
    3   |
    ...
    ou i est l'indice de ligne de la place 
        j est l'indice de colonne de la place 
        k est le numero du tetromino que l'on peut mettre */
    int ** place_tetro_possible = create_tableau(taille*taille*nb_tetro_bag, 3);
    /* on recupere la liste des tetrominos presents dans le sac */
    tetromino * l_tetro = list_tetrominos_in_bag(b);
    /* on parcours toute la grille du jeu */
    for (int i = 0; i<taille; i++) {
        for (int j = 0; j<taille; j++) {
            /* pour chaque case, on regarde pour chacun des tetrominos si on peut le mettre a cette place.
            Si c'est le cas, on calcule la taille de l'espace disponible grace a la fonction taille_espace implementer precedemment */
            for (int k = 0; k<nb_tetro_bag; k++) {
                if (checkplace_tetromino(b,i,j,l_tetro[k]) == 1) {
                    int ** espace = create_tableau(taille, taille);
                    int t = taille_espace(b,i,j,taille,espace);
                    /* on compare la taille de l'espace calculee au minimum de la taille de l'espace */
                    if (t < min_t_espace) {
                        min_t_espace = t;
                        /* on reinitialise le tableau où on stock les places possibles du tetromino et le tetromino */
                        reinitialise_tab(place_tetro_possible);
                    }
                    if (t == min_t_espace) {
                        /* on ajoute au tableau la place que l'on vient de trouver  */
                        add_tab(place_tetro_possible, i, j, k);
                    }
                    /* on libere la memoire allouee par espace */
                    free(espace);
                }
            }
        }
    }
    /* on a donc remplie un tableau avec toutes les places disponibles et les tetrominos associes avec une taille de l'espace minimale (egale a min_t_espace).
    On parcours le tableau remplie pour trouver la place du tetromino le plus en bas et le plus loin du milieu 
    ainsi que le numero du tetromino associe a cette place */
    int n = 0;
    int max_i = maximum(place_tetro_possible);
    int dist_milieu = taille;
    int num_tetro_a_placer = 0 ;
    int j = -1 ;
    while (place_tetro_possible[n][0] != -1) {
        if (place_tetro_possible[n][0] == max_i && distance_milieu(taille, place_tetro_possible[n][1]) < dist_milieu) {
            dist_milieu = distance_milieu(taille, place_tetro_possible[n][1]);
            j = place_tetro_possible[n][1];
            num_tetro_a_placer = place_tetro_possible[n][2];
        }
        n++;
    }
    /* on libere la memoire allouee par place_tetro_possible */
    for(int i=0; i<taille*taille;i++){
        free(place_tetro_possible[i]);
    }
    free(place_tetro_possible);
    /* on retourne 0 si n=0 parce que cela signifie qu'il est impossible de placer un seul des tetrominos sur la grille */
    if (n == 0) {
        return 0;
    }
    /* on recupere le tetromino associe au numero trouve juste precedemment */
    tetromino tetro = l_tetro[num_tetro_a_placer] ;
    /* on retourne le nombre du points du tetromino place si ca a ete reussi et 0 sinon */
    if (place_tetromino(b, max_i, j, tetro) == 1) {
        return get_nb_points(tetro);
    }
    else {
        return 0; 
    }
}

