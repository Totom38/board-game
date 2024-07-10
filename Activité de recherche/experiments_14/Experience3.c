#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
void enable_ansi_escape_codes() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

char* couleurs[] = {
    "\x1b[30;40m",   // Noir
    "\x1b[31;41m",   // Rouge
    "\x1b[32;42m",   // Vert
    "\x1b[33;43m",   // Jaune
    "\x1b[34;44m",   // Bleu
    "\x1b[35;45m",   // Magenta
    "\x1b[36;46m" };

char * blanc = "\x1b[37;47m" ;
char* reset_color = "\x1b[0m" ;
int compteur = 0 ;

int tableau[19][8] = {{0, 0, 0, 1, 1, 1, 1, 2},
                     {0, 1, 0, 2, 1, 0, 1, 1},
                     {0, 0, 0, 1, 0, 2, 0, 3},
                     {0, 0, 1, 0, 2, 0, 3, 0},
                     {0, 0, 0, 1, 1, 0, 1, 1},
                     {0, 0, 0, 1, 0, 2, 1, 1},
                     {0, 1, 1, 0, 1, 1, 2, 1},
                     {0, 1, 1, 0, 1, 1, 1, 2},
                     {0, 0, 1, 0, 1, 1, 2, 0},
                     {0, 0, 0, 1, 0, 2, 1, 0},
                     {0, 0, 0, 1, 1, 1, 2, 1},
                     {0, 2, 1, 0, 1, 1, 1, 2},
                     {0, 0, 1, 0, 2, 0, 2, 1},
                     {0, 0, 0, 1, 0, 2, 1, 2},
                     {0, 1, 1, 1, 2, 0, 2, 1},
                     {0, 0, 1, 0, 1, 1, 1, 2},
                     {0, 0, 0, 1, 1, 0, 2, 0},
                     {0, 1, 1, 0, 1, 1, 2, 1},
                     {0, 0, 1, 0, 1, 1, 2, 1} } ;

typedef struct {int score ; int couleur ; int points[8] ;} tetromino ;

typedef struct Node {tetromino valeur ; struct Node *suivant ; } Node;

typedef struct {Node *tete ; } Liste;

Liste *initialiser_liste() {
    Liste *liste = (Liste *)malloc(sizeof(Liste));
    if (liste == NULL) {
        printf("Erreur d'allocation de mémoire pour la liste.\n") ;
        exit(EXIT_FAILURE) ; }
    liste->tete = NULL ;
    return liste ; }

void ajouter_element(Liste *liste, tetromino valeur) {
    Node *nouveau_node = (Node *)malloc(sizeof(Node));
    if (nouveau_node == NULL) {
        printf("Erreur d'allocation de mémoire pour le nouvel élément.\n") ;
        exit(EXIT_FAILURE) ; }
    nouveau_node->valeur = valeur ;
    nouveau_node->suivant = NULL ;
    if (liste->tete == NULL) {
        liste->tete = nouveau_node ; } 
    else {
        Node *courant = liste->tete ;
        while (courant->suivant != NULL) {
            courant = courant->suivant ; }
        courant->suivant = nouveau_node ; } }

void supprimer_element_k(Liste *liste, int k) {
    if (k < 0) {
        printf("La position k doit être positive.\n");
        return ; }
    if (liste->tete == NULL) {
        printf("La liste est vide.\n");
        return ; }
    if (k == 0) {
        Node *temp = liste->tete ;
        liste->tete = liste->tete->suivant ;
        free(temp) ;
        return ; }
    Node *courant = liste->tete ;
    Node *precedent = NULL ;
    int indice = 0 ;
    while (courant != NULL && indice < k) {
        precedent = courant ;
        courant = courant->suivant ;
        indice++ ; }
    if (courant == NULL) {
        printf("La position %d dépasse la taille de la liste pour la suppression d'un élement.\n",k);
        return ; }
    precedent->suivant = courant->suivant ;
    free(courant) ; }

void supprimer_element(Liste *liste, tetromino valeur) {
    Node *courant = liste->tete ;
    Node *precedent = NULL ;
    while (courant != NULL && memcmp(&(courant->valeur), &valeur, sizeof(tetromino)) != 0) {
        precedent = courant ;
        courant = courant->suivant ; }
    if (courant == NULL) {
        printf("L'élément à supprimer n'a pas été trouvé dans la liste.\n") ;
        return ; }
    if (precedent == NULL) {
        liste->tete = courant->suivant ; } 
    else {
        precedent->suivant = courant->suivant ; }
    free(courant) ; }

tetromino accéder_element(Liste *liste, int k) {
    if (k < 0) {
        printf("La position k doit être positive.\n") ;
        exit(EXIT_FAILURE); }
    Node *courant = liste->tete ;
    int indice = 0 ;
    while (courant != NULL && indice < k) {
        courant = courant->suivant ;
        indice++ ; }
    if (courant == NULL) {
        printf("La position %d dépasse la taille de la liste pour l'accès à l'élement.\n",k) ;
        exit(EXIT_FAILURE) ; }
    return courant->valeur ; }

int longueur_liste(Liste *liste) {
    int longueur = 0 ;
    Node *courant = liste->tete ;
    while (courant != NULL) {
        longueur++ ;
        courant = courant->suivant ; }
    return longueur ;}

void afficher_liste(Liste *liste) {
    Node *courant = liste->tete;
    while (courant != NULL) {
        // Affichage des points du tétrmino
        printf("Points du tétrmino :\n");
        for (int i = 0; i < 8; i++) {
            printf("(%d, %d)\n", courant->valeur.points[i], courant->valeur.points[i+1]);
            i++; // On incrémente i de 1 pour sauter à l'élément suivant
        }
        courant = courant->suivant;
    }
}

void inserer_tri(Liste *l, tetromino t) {
    Node *nouveau_noeud = malloc(sizeof(Node));
    if (nouveau_noeud == NULL) {
        fprintf(stderr, "Erreur : allocation mémoire échouée\n");
        exit(EXIT_FAILURE);
    }
    nouveau_noeud->valeur = t;
    nouveau_noeud->suivant = NULL;

    // Si la liste est vide ou si le premier tétraminos doit être inséré en premier
    if (l->tete == NULL || l->tete->valeur.points[0] > t.points[0]) {
        nouveau_noeud->suivant = l->tete;
        l->tete = nouveau_noeud;
    } else {
        Node *precedent = l->tete;
        Node *courant = l->tete->suivant;
        while (courant != NULL && courant->valeur.points[0] <= t.points[0]) {
            if (courant->valeur.points[0] == t.points[0] && courant->valeur.points[1] > t.points[1]) {
                break;
            }
            precedent = courant;
            courant = courant->suivant ; }
        nouveau_noeud->suivant = courant ;
        precedent->suivant = nouveau_noeud ; } }

typedef int row ;
typedef int col ;
typedef int value ;

typedef struct { Liste* plateau ; Liste* sac ; int score ; row lignes ; col colonnes ; value taille_sac ; } board ;

void add_tetromino_to_bag(tetromino t, board * b) {
    ajouter_element(b->sac,t) ; }

tetromino create_random_tetromino() {
    tetromino t ;
    t.score = rand()% 3 +1 ;
    t.couleur = compteur ;
    compteur = (compteur + 1) % 7;
    int indice = rand() % 19 ;
    for (int i = 0; i < 8; i++) {
        t.points[i] = tableau[indice][i] ; }
    return t ; }

tetromino select_tetromino_in_bag(board b) {
    int choix =  -1 ;
    int n = longueur_liste(b.sac) ;
    while (choix < 1 || choix > n) {
        printf("Choisissez une pièce dans le sac (entre 1 et %d): ",n) ;
        scanf("%d", &choix) ;
        if (choix < 1 || choix > n) {
            printf("Choix invalide.\n") ; } }
    return accéder_element(b.sac,(choix-1)) ; } 

board create_board(row n, col m, value k) {
    board b ;
    b.lignes = n ;
    b.colonnes = m ;
    b.taille_sac = k ;
    b.score = 0 ;
    b.plateau = initialiser_liste() ;
    b.sac = initialiser_liste() ;
    return b ; }

tetromino select_tetromino_on_grid(board b) {
    int choix = -1 ;
    int n = longueur_liste(b.plateau) ;
    while (choix < 1 || choix > n) {
        printf("Choisissez une pièce sur le plateau (entre 1 et %d) : ",n) ;
        scanf("%d", &choix) ;
        if (choix < 1 || choix > n) {
            printf("Choix invalide.\n") ; } }
    return accéder_element(b.plateau,(choix-1)) ; }

int choose_action() {
    int choix = 4 ;
    while (choix < 1 || choix > 3) {
        printf("Choisir une action\n- 1 pour placer une piece\n- 2 pour deplacer une piece\n- 3 pour quitter\nRéponse : ") ;
        scanf("%d", &choix) ;
        if (choix < 1 || choix > 3) {
            printf("Choix invalide.\n") ; } 
        while (getchar() != '\n') ; }
    return choix-1 ; } 

void display_message(char * chaîne){
    printf("%s",chaîne) ; }

void remove_tetromino_from_bag(tetromino t, board b) {
    supprimer_element(b.sac,t) ; }

int checkplace_tetromino(board b, int r,int c, tetromino t) {
    for (int i = 0 ; i < 4 ; i++) {
        if (t.points[2*i]+r < 0 || t.points[2*i+1]+c < 0 || t.points[2*i]+r > b.lignes -1 || t.points[2*i+1]+c > b.colonnes -1) {
            return 0 ; }
        else {
            for (int j = 0 ; j < longueur_liste(b.plateau) ; j++) {
                tetromino tt = accéder_element(b.plateau,j) ;
                for (int k = 0 ; k < 4 ; k++) {
                    if (t.points[2*i]+r == tt.points[2*k] && t.points[2*i+1]+c == tt.points[2*k+1]) {
                        return 0 ; } } } } }
    return 1 ; }

void ask_place_tetromino(board b,int* pc, int* pr,tetromino t) {
    while (*pc < 0 || *pr < 0 || *pc > b.lignes - 1|| *pr > b.colonnes - 1 || ! checkplace_tetromino(b,*pc,*pr,t)) {
        printf("Veuillez saisir la ligne (entre 0 et %d) : ",b.lignes-1) ;
        scanf("%d", pc) ;
        while (getchar() != '\n') ;
        printf("Veuillez saisir la colonne (entre 0 et %d) : ",b.colonnes-1) ;
        scanf("%d", pr) ; 
        while (getchar() != '\n') ;
        if (*pc < 0 || *pr < 0 || *pc > b.lignes - 1|| *pr > b.colonnes - 1 || ! checkplace_tetromino(b,*pc,*pr,t)) {
            printf("Choix invalide.\n") ; } }
    return ; }

int place_tetromino(board * b,int r,int c, tetromino t ) {
    for (int i = 0; i < 4; i++) {
        t.points[2*i] = t.points[2*i] + r ;
        t.points[2*i+1] = t.points[2*i+1] + c ; }
    inserer_tri(b->plateau,t) ; 
    b->score = b->score + t.score ;
    return 1 ; }

void display_end_game(board b) {
    printf("Fin de la partie avec un score final de %d.\n",b.score) ; }

void free_board(board b) {
    free(b.plateau) ;
    free(b.sac) ; 
    }

void remove_tetromino(board * b, int* pr, int* pc, tetromino t ) {
    supprimer_element(b->plateau,t) ;
    *pr = t.points[0] ; 
    *pc = t.points[1] ; 
    b->score = b->score - t.score ; }

int dimension_max(Liste *l) {
    int max = 1 ;
    for (int i = 0 ; i < longueur_liste(l) ; i++) {
        tetromino t = accéder_element(l,i) ;
        for (int j = 0 ; j < 8 ; j ++) {
            if (t.points[j] > max) {
                max = t.points[j] ; } } }
    return max ; }

void display_board(board b) {
    printf("\nScore : %d\nSac :\n",b.score) ;
    int dimension = dimension_max(b.sac) + 1 ;
    for (int i = 0 ; i < b.taille_sac * (dimension+3) ; i ++) {
        if (i % (dimension+3) == 0) {
            printf("%d",accéder_element(b.sac,i / (dimension+3)).score) ; }
        else {
            printf(" ") ; } }
    printf("\n") ;
    for (int i = 0 ; i < dimension ; i ++) {
        for (int j = 0 ; j < b.taille_sac ; j ++) {
            tetromino t = accéder_element(b.sac,j) ;
            for (int k = 0 ; k < dimension ; k ++) {
                int bool = 0 ;
                for (int l = 0 ; l < 4 ; l++) {
                    if (t.points[2*l] == i && t.points[2*l+1] == k) {
                        bool = 1 ; } }
                if (bool) {
                    printf("%sX%s",couleurs[t.couleur],reset_color) ; }
                else {
                    printf("%s%sX%s",blanc,blanc,reset_color) ; } } 
            printf("   ") ; }
        printf("\n") ; } 
    printf("Plateau :\n") ;
    for (int i = 0 ; i < b.lignes ; i ++) {
        for (int j = 0 ; j < b.colonnes ; j++) {
            int bool = -1 ;
            for (int k = 0 ; k < longueur_liste(b.plateau) ; k++) {
                tetromino t = accéder_element(b.plateau,k) ;
                for (int l = 0 ; l < 4 ; l ++) {
                    if (t.points[2*l] == i && t.points[2*l+1] == j) {
                        bool = t.couleur ; } } }
            if (bool > -1) {
                printf("%sX%s",couleurs[bool],reset_color) ; }
            else {
                printf("%s%sX%s",blanc,blanc,reset_color) ; } } 
        printf("\n") ; }
    printf("\n") ; }

int corner_fit_2(board * b) {
    int distance_min = 1000 ;
    int meilleur_position[3] = {-1, -1,-1}; // ligne, colonne, indice dans le sac,
    int coins[4][2] = {{0, 0}, {0, b->colonnes-1}, {b->lignes-1, 0}, {b->lignes-1, b->colonnes-1}};
    for (int k = 0 ; k < longueur_liste(b->sac) ; k++) { // Pour chaque pièce
        tetromino t = accéder_element(b->sac,k) ;
        for (int i = 0 ; i < b->lignes ; i++) { // Pour chaque ligne
            for (int j = 0 ; j < b->colonnes ; j ++) { // Pour chaque colonne
                if (checkplace_tetromino(*b,i,j,t)) {
                    for (int l = 0 ; l < 4 ; l++) { // Pour chaque coin
                        int distance = 0 ;
                        for (int m = 0 ; m < 4 ; m++) { // Pour cube du tétrominos
                            distance = distance + abs(t.points[2*m] + i - coins[l][0]) + abs(t.points[2*m+1] + j - coins[l][1]) ; }
                        if (distance < distance_min) {
                            distance_min = distance ;
                            meilleur_position[0] = i ;
                            meilleur_position[1] = j ;
                            meilleur_position[2] = k ; } } } } } }
    if (distance_min == 1000) {
        return 0 ; }
    else {
        tetromino t = accéder_element(b->sac,meilleur_position[2]) ;
        remove_tetromino_from_bag(t,*b) ;
        place_tetromino(b,meilleur_position[0],meilleur_position[1],t) ;
        return 1 ; } } 

int main() {
    srand(time(NULL)) ;
    #ifdef _WIN32
        enable_ansi_escape_codes();
    #endif
    board b = create_board(8,8,3) ;
    for (int k = 0 ; k < b.taille_sac ; k++) {
        add_tetromino_to_bag(create_random_tetromino(),&b) ; }
    while (corner_fit_2(&b)) {
        add_tetromino_to_bag(create_random_tetromino(),&b) ;
        display_board(b) ; }
    printf("Fin de l'exemple d'execution d'un corner fit 2.\n") ;
    printf("Resultats finaux (taile du plateau n x n,temps,score,densite)\n") ;
    for (int i = 3 ; i < 21 ; i++) { // Pour chaque taille de plateau, on fait 10 tests puis on fait une moyenne des temps et des scores
        double temps_total = 0 ;
        int score_total = 0 ;
        int remplissage = 0 ;
        for (int j = 0 ; j < 10 ; j++) {
            board b = create_board(i,i,3) ;
            for (int k = 0 ; k < b.taille_sac ; k++) {
                add_tetromino_to_bag(create_random_tetromino(),&b) ; }
            clock_t debut = clock() ;
            while (corner_fit_2(&b)) {
                add_tetromino_to_bag(create_random_tetromino(),&b) ; }
            clock_t fin = clock() ;
            temps_total = temps_total + (double)(fin - debut) / CLOCKS_PER_SEC ;
            score_total = score_total + b.score ;
            remplissage = remplissage + longueur_liste(b.plateau) * 4 ;
            free_board(b) ; }
        printf("%d,%f,%f,%f\n",i,temps_total/10,(double)score_total / 10,(double)remplissage/(10*i*i)) ; }
    return 0 ; }

int main() ; 

// gcc code.c -o mon_programme -Wall -Wextra -pedantic -std=c99 || ./mon_programme
