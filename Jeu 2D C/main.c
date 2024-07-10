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
    "\x1b[30;40m",
    "\x1b[31;41m",   // Rouge
    "\x1b[32;42m",   // Vert
    "\x1b[33;43m",   // Jaune
    "\x1b[34;44m",   // Bleu
    "\x1b[35;45m",   // Magenta
    "\x1b[36;46m" };

char * blanc = "\x1b[37;47m" ;
char* reset_color = "\x1b[0m" ;
int compteur = 0 ;

int tableau[19][8] = {{0, 0, 0, 1, 0, 2, 0, 3},
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
                     {0, 0, 0, 1, 1, 1, 1, 2},
                     {0, 1, 1, 0, 1, 1, 2, 1},
                     {0, 1, 0, 2, 1, 0, 1, 1},
                     {0, 0, 1, 0, 1, 1, 2, 1} } ;

int tableau2[7][8] ={{0, 0, 0, 1, 0, 2, 0, 3},
                     {0, 0, 0, 1, 1, 0, 1, 1},
                     {0, 0, 0, 1, 0, 2, 1, 1},
                     {0, 0, 0, 1, 0, 2, 1, 0},
                     {0, 0, 0, 1, 0, 2, 1, 2},
                     {0, 0, 0, 1, 1, 1, 1, 2},
                     {0, 1, 0, 2, 1, 0, 1, 1} } ;

const char* noms[20] = {
        "Thuy Vo",
        "David Roussel",
        "Abass Sagna",
        "Renaud Rioboo",
        "Kevin Goilard",
        "Laurence Bourard",
        "Massinissa Merabet",
        "Anne-Laure Ligozat",
        "Christophe Mouilleron",
        "Djibril-Aurelien Dembele-Cabot",
        "Lucienne Pacave",
        "Lawanda Gaydu",
        "Christine Matias",
        "Guillaume Burel",
        "Cyril Benezet",
        "Mathilde Mougeot",
        "Dimitri Watel",
        "Marie Szafranski",
        "Julien Forest",
        "Laurent Prével"} ;

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
        printf("La position k dépasse la taille de la liste.\n");
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
        printf("La position k dépasse la taille de la liste.\n") ;
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

typedef struct {char valeur[30] ; } carte ;

typedef struct {carte cartes[8] ; int nombre_de_cartes ; } deck ;

void afficher_deck(deck m) {
    for (int i = 0 ; i < m.nombre_de_cartes ; i++) {
        printf("%s\n",m.cartes[i].valeur) ; } }

deck initialiser_deck() {
    deck d ;
    d.nombre_de_cartes = 0 ;
    return d ;}

void ajouter_carte(deck *m, carte c) {
    if (m->nombre_de_cartes < 8) {
        strcpy(m->cartes[m->nombre_de_cartes].valeur,c.valeur) ;
        m->nombre_de_cartes ++ ; }
    else {
        printf("Main pleine.\n") ; } }

carte supprimer_carte(deck* d, int i) {
    carte carte_suprimée ;
    strcpy(carte_suprimée.valeur, "") ;
    if (i < 0 || i >= d->nombre_de_cartes) {
        printf("Indice invalide.\n") ;
        return carte_suprimée ; }
    strcpy(carte_suprimée.valeur, d->cartes[i].valeur) ;
    for (int j = i ; j < d->nombre_de_cartes - 1 ; j++) {
        strcpy(d->cartes[j].valeur, d->cartes[j + 1].valeur) ; }
    d->nombre_de_cartes-- ;
    return carte_suprimée ; }

carte carte_aléatoire() {
    carte c ;
    //int tab[] = {0,1,2,3,6,7,8,9,10,14,15,16,17};
    int indice = 0 ;
    strcpy(c.valeur, noms[indice]) ;
    return c ; }

typedef int row ;
typedef int col ;
typedef int value ;

typedef struct { Liste* plateau ; Liste* sac ; int score ; row lignes ; col colonnes ; value taille_sac ; int compteur_reserve[10] ; Liste* reserve ; deck d ; int cases_spéciales[32] ; int nombre_cases_spéciales ; int taille_reserve ;} board ;

tetromino normaliser_tetromino(tetromino t) {
    tetromino tt ;
    tt.couleur = t.couleur ;
    tt.score = t.score ;
    int x = t.points[0] ;
    int y = t.points[1] ;
    for (int k = 0 ; k<4 ; k ++) {
        tt.points[2*k] = t.points[2*k] - x ;
        tt.points[2*k+1] = t.points[2*k+1] - y ; } 
    return tt ; }

void add_tetromino_to_bag(tetromino t, board b) {
    ajouter_element(b.sac,t) ; }

tetromino create_random_tetromino() {
    tetromino t ;
    t.score = rand()% 3 +1 ;
    t.couleur = compteur ;
    compteur = (compteur + 1) % 7;
    int indice = rand() % 19 ;
    for (int i = 0; i < 8; i++) {
        t.points[i] = tableau[indice][i] ; }
    return t ; }

tetromino create_tetromino(int indice) {
    tetromino t ;
    t.score = rand()% 3 +1 ;
    t.couleur = compteur ;
    compteur = (compteur + 1) % 7;
    for (int i = 0; i < 8; i++) {
        t.points[i] = tableau2[indice][i] ; }
    return t ; }

tetromino create_random_barre_horizontale(){
    tetromino t ;
    t.score = 0 ;
    t.couleur = compteur ;
    compteur = (compteur + 1) % 7;
    for (int i = 0; i < 8; i++) {
        t.points[i] = tableau[0][i] ; }
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

tetromino select_tetromino_in_reserve(board b) {
    int choix =  -1 ;
    int i = 0 ;
    while (b.compteur_reserve[i] > -1) {
        i++ ; }
    while (choix < 1 || choix > i) {
        printf("Choisissez une pièce dans la réserve (entre 1 et %d): ",i) ;
        scanf("%d", &choix) ;
        if (choix < 1 || choix > i) {
            printf("Choix invalide.\n") ; } }
    return accéder_element(b.reserve,(choix-1)) ; } 

board create_board(row n, col m, value k) {
    board b ;
    b.lignes = n ;
    b.colonnes = m ;
    b.taille_sac = k ;
    b.score = 0 ;
    b.plateau = initialiser_liste() ;
    b.sac = initialiser_liste() ;
    for (int i = 0 ; i<10 ; i++) {
        b.compteur_reserve[i] = -10 ;}
    b.reserve = initialiser_liste() ;
    b.d = initialiser_deck() ;
    int valeurs[16] = {0, 7, 1, 1, 2, 5, 3, 3, 4, 4, 5, 2, 6, 6, 7, 0};
    for (int i = 0; i < 16; i++) {
        b.cases_spéciales[i] = valeurs[i] ; }
    b.nombre_cases_spéciales = 8 ;
    b.taille_reserve = 2 ;
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
    int choix = -1 ;
    while (choix < 1 || choix > 6) {
        printf("Choisir une action\n- 1 pour placer une piece (sac)\n- 2 pour deplacer une piece\n- 3 pour quitter\n- 4 pour placer une piece de la réserve\n- 5 pour mettre une piece en réserve\n- 6 pour utiliser une carte\nRéponse : ") ;
        scanf("%d", &choix) ;
        if (choix < 1 || choix > 6) {
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
            printf("Pièce qui dépasse du plateau.\n") ;
            return 0 ; }
        else {
            for (int j = 0 ; j < longueur_liste(b.plateau) ; j++) {
                for (int k = 0 ; k < 4 ; k++) {
                    tetromino tt = accéder_element(b.plateau,j) ;
                    if (t.points[2*i]+r == tt.points[2*k] && t.points[2*i+1]+c == tt.points[2*k+1]) {
                        printf("Collision de pièces en (%d,%d).\n",t.points[2*i],t.points[2*i+1]+c) ;
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

void display_tetromino(tetromino t) {
    int nb_lignes = 0 ;
    int nb_colonnes = 0 ;
    for (int i = 0 ; i < 4 ; i++) {
        if (t.points[2*i] > nb_lignes) {
            nb_lignes = t.points[2*i] ; }
        if (t.points[2*i+1] > nb_colonnes) {
            nb_colonnes = t.points[2*i+1] ; } }
    nb_lignes++ ;
    nb_colonnes++ ;
    for (int i = 0 ; i < nb_lignes ; i ++) {
        for (int j = 0 ; j < nb_colonnes ; j ++) {
            int bool = 0 ;
            for (int l = 0 ; l < 4 ; l++) {
                if (t.points[2*l] == i && t.points[2*l+1] == j) {
                    bool = 1 ; } }
            if (bool) {
                printf("%sX%s",couleurs[t.couleur],reset_color) ; }
            else {
                printf("%s%sX%s",blanc,blanc,reset_color) ; } }
        printf("\n") ; } }

void display_liste(Liste *l) {
    int dimension = dimension_max(l) + 1 ;
    int n = longueur_liste(l) ;
    for (int i = 0 ; i < n * (dimension+3) ; i ++) {
        if (i % (dimension+3) == 0) {
            printf("%d",accéder_element(l,i / (dimension+3)).score) ; }
        else {
            printf(" ") ; } }
    printf("\n") ;
    for (int i = 0 ; i < dimension ; i ++) {
        for (int j = 0 ; j < n ; j ++) {
            tetromino t = accéder_element(l,j) ;
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
}

void display_board(board b) {
    printf("\nScore : %d\nSac :\n",b.score) ;
    display_liste(b.sac) ;
    int booleen = 0 ;
    for (int i = 0 ; i < 10 ; i++) {
        if (b.compteur_reserve[i] > -1) {
            booleen = 1 ; } }
    if (booleen) {
        printf("Réserve (taille maximale de %d) :\n",b.taille_reserve) ;
        display_liste(b.reserve) ; }
    else {
        printf("La réserve est vide.\n") ; }
    if (b.d.nombre_de_cartes == 0) {
        printf("La main est vide.\n") ; }
    else {
        printf("Main :\n") ;
        afficher_deck(b.d) ; }
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

void trier_points(int *points) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3 - i; j++) {
            // Si la coordonnée X du point actuel est supérieure à celle du suivant, ou
            // si les coordonnées X sont égales et que la coordonnée Y est supérieure, on échange les points
            if (points[2*j] > points[2*(j+1)] || 
               (points[2*j] == points[2*(j+1)] && points[2*j+1] > points[2*(j+1)+1])) {
                // Échange des coordonnées X
                int temp_x = points[2*j];
                points[2*j] = points[2*(j+1)];
                points[2*(j+1)] = temp_x;

                // Échange des coordonnées Y
                int temp_y = points[2*j+1];
                points[2*j+1] = points[2*(j+1)+1];
                points[2*(j+1)+1] = temp_y;
            }
        }
    }
}

void tourner(tetromino * t) {
    int nb_ligne = 0;
    int nouvelles_coordonnees[8]; // Pour stocker les nouvelles coordonnées tournées
    for (int i = 0; i < 4; i++) {
        if (t->points[2*i] > nb_ligne) {
            nb_ligne = t->points[2*i];
        }
    }

    // Calcul et stockage des nouvelles coordonnées tournées dans un tableau temporaire
    for (int i = 0; i < 4; i++) {
        int x = t->points[2*i];
        int y = t->points[2*i+1];
        nouvelles_coordonnees[2*i] = y;
        nouvelles_coordonnees[2*i+1] = nb_ligne - x; // Rotation de 90 degrés
    }

    trier_points(nouvelles_coordonnees); // Tri des points pour faciliter la comparaison (et l'affichage

    // Copie des nouvelles coordonnées dans t->points
    for (int i = 0; i < 8; i++) {
        t->points[i] = nouvelles_coordonnees[i];
    } }

int choix_tourner() {
    int choix = - 1 ;
    while (choix < 0) {
        printf("Nombre de rotations (horaires) de la pièce : ") ;
        scanf("%d", &choix) ;
        if (choix < 0) {
            printf("Choix invalide.\n") ; } }
    return choix ; }

int tetromino_égaux(tetromino t1, tetromino t2) {
    tetromino tt1 = normaliser_tetromino(t1) ;
    tetromino tt2 = normaliser_tetromino(t2) ;
    for (int i = 0 ; i < 8 ; i++) {
        if (tt1.points[i] != tt2.points[i]) {
            return 0 ; } }
    return 1 ; }

void utiliser_carte(carte c,board *b) {
    // 14 Cartes ont été implémentées sur les 20
    if (strcmp(c.valeur, "Thuy Vo") == 0) {
        tetromino t = select_tetromino_in_bag(*b) ;
        remove_tetromino_from_bag(t,*b) ;
        add_tetromino_to_bag(create_random_tetromino(),*b) ; }
    if (strcmp(c.valeur, "David Roussel" ) == 0|| strcmp(c.valeur,"Abass Sagna") ==0) {
        int k = 0 ;
        while (b->compteur_reserve[k] > -1) {
            k++ ; }
        if (k == 0) {
            printf("La réserve est vide.\n") ; }
        else {
            tetromino pièce_à_placer = select_tetromino_in_reserve(*b) ;
            k = 0 ;
            for (int i = 0 ; k<10 ; i++) {
                tetromino t = accéder_element(b->reserve,i) ;
                if (tetromino_égaux(t,pièce_à_placer)) {
                    k = i ;
                    break ; } } 
            for (int i = k ; i < 9; i++) {
                b->compteur_reserve[i] = b->compteur_reserve[i + 1] ; }
            b->compteur_reserve[9] = -10 ; 
            supprimer_element_k(b->reserve,k) ; } 
            if (strcmp(c.valeur, "Abass Sagna") == 0) {
                int i = 0 ;
                while (b->compteur_reserve[i] > -1) {
                    i++ ; }
                ajouter_element(b->reserve,create_random_tetromino()) ;
                b->compteur_reserve[i] = 0 ; } }
    if (strcmp(c.valeur, "Renaud Rioboo") == 0) {
        int choix = -1 ;
        while (choix <0 || choix > longueur_liste(b->plateau)) {
        printf("Choisir un nombre de pièces à retirer du plateau (0 et %d)\nRéponse : ",longueur_liste(b->plateau)) ;
        scanf("%d", &choix) ;
        if (choix < 0 || choix > longueur_liste(b->plateau)) {
            printf("Choix invalide.\n") ; } 
        while (getchar() != '\n') ; }
        for (int i = 0 ; i < choix ; i++) {
            tetromino t = select_tetromino_on_grid(*b) ;
            int * pr = NULL ;
            int * pc = NULL ;
            remove_tetromino(b,pc,pr,t) ;
            b->score = b->score - 1 ; } }
    if (strcmp(c.valeur, "Kevin Goilard") == 0) {}
    if (strcmp(c.valeur, "Laurence Bourard") == 0) {}
    if (strcmp(c.valeur, "Massinissa Merabet") == 0) {
        if (longueur_liste(b->reserve) >= b->taille_reserve) {
            printf("La réserve est pleine.\n") ; }
        else {
            tetromino t = select_tetromino_on_grid(*b) ;
            int i = 0 ;
            while (b->compteur_reserve[i] > -1) {
                i++ ; }
            ajouter_element(b->reserve,t) ;
            b->compteur_reserve[i] = 0 ; } }
    if (strcmp(c.valeur, "Anne-Laure Ligozat") == 0) {
        int i = 0 ;
        while (i < 3 || longueur_liste(b->plateau) < 1) {
            tetromino pièce_à_supprimer = select_tetromino_on_grid(*b) ;
            int x = -1 ;
            int y = -1 ;
            b->score = b->score + pièce_à_supprimer.score ;
            remove_tetromino(b,&x,&y,pièce_à_supprimer) ;
            i++ ; } }
    if (strcmp(c.valeur, "Christophe Mouilleron") == 0) {
        for (int i = 0 ; i<b->taille_sac ; i++) {
            tetromino t = accéder_element(b->sac,0) ;
            remove_tetromino_from_bag(t,*b) ; }
        for (int i = 0 ; i<b->taille_sac ; i++) {
            add_tetromino_to_bag(create_random_tetromino(),*b) ; } }
    if (strcmp(c.valeur, "Djibril-Aurelien Dembele-Cabot") == 0) {
        int possible = 0 ;
        for (int i = 0 ; i < longueur_liste(b->plateau) ; i ++) {
            for (int j = 0 ; j < longueur_liste(b->plateau) ; j++) {
                if (i != j && tetromino_égaux(accéder_element(b->plateau,i),accéder_element(b->plateau,j))) {
                    possible = 1 ; } } }
        if (possible) {
            printf("Action impossible, aucun tetrominos identiques") ; }
        else {
            tetromino t1 = select_tetromino_on_grid(*b) ;
            tetromino t2 = select_tetromino_on_grid(*b) ;
            if (! tetromino_égaux(t1,t2)) {
                printf("Vous n'avez pas choisi une paire.\n") ; 
                exit(EXIT_FAILURE) ; }
            else {
                b->score = b->score + t1.score ;
                b->score = b->score + t2.score ;
                int * pr = NULL ;
                int *pc = NULL ;
                remove_tetromino(b,pr,pc,t1) ;
                remove_tetromino(b,pr,pc,t2) ; } } }
    if (strcmp(c.valeur, "Lucienne Pacave") == 0) {
        int booléen = 1 ;
        int * i = NULL;
        int * j = NULL;
        while (booléen) {
            *i = (rand() % 8) ;
            *j = (rand() % 8) ;
            booléen = 0 ;
            for (int k = 0 ; k < b->nombre_cases_spéciales ; k++) {
                if (*i==b->cases_spéciales[2*k] && *j==b->cases_spéciales[2*k+1]) {
                    booléen = 1 ; } } }
        b->nombre_cases_spéciales++ ;
        b->cases_spéciales[2*b->nombre_cases_spéciales] = *i ;
        b->cases_spéciales[2*b->nombre_cases_spéciales+1] = *j ; }
    if (strcmp(c.valeur, "Lawanda Gaydu") == 0) {}
    if (strcmp(c.valeur, "Christine Matias") == 0) {}
    if (strcmp(c.valeur, "Guillaume Burel") == 0) {}
    if (strcmp(c.valeur, "Cyril Benezet") == 0) {
        int choix = -1 ;
        while (choix < 1 || choix > 7) {
        printf("Choisir une pièce\n- 1 Barre\n- 2 Carré\n- 3 Triangle\n- 4 L\n- 5 L inversé\n- 6 Z\n- 7 S\nRéponse : ") ;
        scanf("%d", &choix) ;
        if (choix < 1 || choix > 7) {
            printf("Choix invalide.\n") ; } 
        while (getchar() != '\n') ; }
        tetromino t = create_tetromino(choix - 1) ;
        int k = 0 ;
        while (longueur_liste(b->sac) > 0) {
            tetromino à_supprimer = accéder_element(b->sac,0) ;
            remove_tetromino_from_bag(à_supprimer,*b) ;
            k ++ ; }
        for (int i = 0 ; i < k ; i++) {
            add_tetromino_to_bag(t,*b) ; } }
    if (strcmp(c.valeur, "Mathilde Mougeot") == 0) {
        b->colonnes = b->colonnes + 4 ;
        tetromino t ;
        t.couleur = 0 ;
        t.score = 0 ;
        t.points[0] = 0 ;
        t.points[1] = 0 ;
        t.points[2] = 0 ;
        t.points[3] = 1 ;
        t.points[4] = 0 ;
        t.points[5] = 2 ;
        t.points[6] = 0 ;
        t.points[7] = 3 ;
        for (int i = 0 ; i<4 ; i++) {
            place_tetromino(b,i,b->colonnes-4,t) ; } }
    if (strcmp(c.valeur, "Dimitri Watel") == 0) {
        b->taille_reserve ++ ; }
    if (strcmp(c.valeur, "Marie Szafranski") == 0) {
        b->taille_sac ++ ;
        add_tetromino_to_bag(create_random_tetromino(),*b) ; }
    if (strcmp(c.valeur, "Julien Forest") == 0) {
        int nombre_pièce = longueur_liste(b->plateau) ;
        while (longueur_liste(b->plateau) != 0) {
            int *pr = NULL;
            int* pc = NULL ;
            remove_tetromino(b,pr,pc,accéder_element(b->plateau,0)) ; }
        for (int i = 0 ; i < nombre_pièce ; i ++) {
            tetromino t = create_random_tetromino() ;
            int colonne = -10 ;
            if (i % 2 == 0) {
                colonne = 0 ; }
            else {
                colonne = 4 ; }
            place_tetromino(b,i/2,colonne,t) ; } }
    if (strcmp(c.valeur, "Laurent Prével") == 0) {} } 

int main() {
    srand(time(NULL));
    board b = create_board(8,8,4) ;
    for (int i = 0 ; i < b.taille_sac ; i ++) {
        add_tetromino_to_bag(create_random_tetromino(),b) ; }
    while (1) {
        display_board(b) ;
        int choix = choose_action() ;
        if (choix == 2) { // Quitter
            display_end_game(b) ;
            free_board(b) ;
            break ; }
        else { 
            if (choix == 0) { // Placer une pièce
                tetromino pièce_à_placer = select_tetromino_in_bag(b) ;
                remove_tetromino_from_bag(pièce_à_placer,b) ;
                add_tetromino_to_bag(create_random_tetromino(),b) ;
                int pr = -1;
                int pc = -1;
                int nb_rotations = choix_tourner() ;
                for (int i = 0 ; i < nb_rotations; i++) {
                    tourner(&pièce_à_placer) ; }
                display_tetromino(pièce_à_placer) ;
                ask_place_tetromino(b,&pr,&pc,pièce_à_placer) ;
                if (! place_tetromino(&b,pr,pc,pièce_à_placer)) {
                    printf("La pièce n'a pu être placée.\n") ; 
                    exit(EXIT_FAILURE); }
                int break_variable = 0;
                for (int i = 0 ; i < 4 ; i++) {
                    for (int j = 0 ; j < b.nombre_cases_spéciales ; j++) {
                        if (pièce_à_placer.points[2*i]+pr == b.cases_spéciales[2*j] && pièce_à_placer.points[2*i+1]+pc == b.cases_spéciales[2*j+1]) {
                            for (int k = j ; k < b.nombre_cases_spéciales - 1; k++) {
                                b.cases_spéciales[2*k] = b.cases_spéciales[2*(k+1)] ;
                                b.cases_spéciales[2*k+1] = b.cases_spéciales[2*(k+1)+1] ; }
                            ajouter_carte(&(b.d),carte_aléatoire()) ;
                            break ; } } 
                    if (break_variable) break ; }
                for (int i = 0 ; i < longueur_liste(b.reserve) ; i ++) {
                    if (b.compteur_reserve[i] > -1) {
                        b.compteur_reserve[i] ++ ; } } }
            else { 
                if (choix == 1) { // Déplacer une pièce
                    if (longueur_liste(b.plateau) > 0) {
                        tetromino pièce_à_déplacer = select_tetromino_on_grid(b) ;
                        int pr = -1;
                        int pc = -1;
                        int x = -1 ;
                        int y = -1 ;
                        remove_tetromino(&b,&x,&y,pièce_à_déplacer) ;
                        for (int i = 0 ; i < 4 ; i++) {
                            pièce_à_déplacer.points[2*i] = pièce_à_déplacer.points[2*i] - x ;
                            pièce_à_déplacer.points[2*i+1] = pièce_à_déplacer.points[2*i+1] - y ; }
                        int nb_rotations = choix_tourner() ;
                        for (int i = 0 ; i < nb_rotations; i++) {
                            tourner(&pièce_à_déplacer) ; }
                        display_tetromino(pièce_à_déplacer) ;
                        ask_place_tetromino(b,&pr,&pc,pièce_à_déplacer) ;
                        if (! place_tetromino(&b,pr,pc,pièce_à_déplacer)) {
                            printf("La pièce n'a pu être déplacée.\n") ; 
                            exit(EXIT_FAILURE) ;
                        int break_variable = 0;
                        for (int i = 0 ; i < 4 ; i++) {
                            for (int j = 0 ; j < b.nombre_cases_spéciales ; j++) {
                                if (pièce_à_déplacer.points[2*i]+pr == b.cases_spéciales[2*j] && pièce_à_déplacer.points[2*i+1]+pc == b.cases_spéciales[2*j+1]) {
                                    for (int k = j ; k < b.nombre_cases_spéciales - 1; k++) {
                                        b.cases_spéciales[2*k] = b.cases_spéciales[2*(k+1)] ;
                                        b.cases_spéciales[2*k+1] = b.cases_spéciales[2*(k+1)+1] ; }
                                    ajouter_carte(&(b.d),carte_aléatoire()) ;
                                    break ; } } 
                            if (break_variable) break ; } } }
                    else {
                        printf("Le plateau est vide.\n") ; } }
                else { 
                    if (choix == 4) { // Mettre en réserve
                        if (longueur_liste(b.reserve) >= b.taille_reserve) {
                            printf("La réserve est pleine.\n") ; }
                        else {
                            if (longueur_liste(b.plateau) > 0) {
                                tetromino pièce_à_mettre_en_reserve = select_tetromino_on_grid(b) ;
                                int pr = -1 ;
                                int pc = -1 ;
                                remove_tetromino(&b,&pr,&pc,pièce_à_mettre_en_reserve) ;
                                int i = 0 ;
                                while (b.compteur_reserve[i] > -1) {
                                    i++ ; }
                                ajouter_element(b.reserve,pièce_à_mettre_en_reserve) ;
                                b.compteur_reserve[i] = 0 ; } 
                            else {
                                printf("Le plateau est vide.\n") ; } } }
                    else {
                        if (choix == 3) { // Placer une pièce de la réserve
                            if (*(b.compteur_reserve) < 0) {
                                printf("La réserve est vide.\n") ; }
                            else {
                                int pr = -1 ;
                                int pc = -1 ;
                                tetromino pièce_à_placer = select_tetromino_in_reserve(b) ;
                                int k = 0 ;
                                for (int i = 0 ; k<10 ; i++) {
                                    tetromino t = accéder_element(b.reserve,i) ;
                                    if (tetromino_égaux(t,pièce_à_placer)) {
                                        k = i ;
                                        break ; } }
                                int nb_rotations = choix_tourner() ;
                                for (int i = 0 ; i < nb_rotations; i++) {
                                    tourner(&pièce_à_placer) ; }
                                display_tetromino(pièce_à_placer) ;
                                ask_place_tetromino(b,&pr,&pc,pièce_à_placer) ;
                                if (! place_tetromino(&b,pr,pc,pièce_à_placer)) {
                                    printf("La pièce n'a pu être placée.\n") ; 
                                    exit(EXIT_FAILURE); } 
                                for (int i = k ; i < 9; i++) {
                                    b.compteur_reserve[i] = b.compteur_reserve[i + 1] ; }
                                b.compteur_reserve[9] = -10 ; 
                                supprimer_element_k(b.reserve,k) ; } } 
                        else {
                            if (choix == 5) {
                                int choix = -1 ;
                                while (choix < 1 || choix > b.d.nombre_de_cartes) {
                                    printf("Choisir une carte (entre 1 et %d)\nRéponse : ",b.d.nombre_de_cartes) ;
                                    scanf("%d", &choix) ;
                                    if (choix < 1 || choix > b.d.nombre_de_cartes) {
                                        printf("Choix invalide.\n") ; } 
                                    while (getchar() != '\n') ; }
                                utiliser_carte(supprimer_carte(&(b.d),choix-1),&b) ; } } } } } } 
        for (int i = 0 ; i < 10 ; i++) {
            if (b.compteur_reserve[i] > 1) {
                supprimer_element_k(b.reserve,i) ; 
                for (int j = i ; j < 9; j++) {
                    b.compteur_reserve[j] = b.compteur_reserve[j + 1] ; }
                b.compteur_reserve[9] = -10 ; }
            }
        } } 

int main() ;

// cd ...
// gcc -Wall -Wextra -o program main.c
// program