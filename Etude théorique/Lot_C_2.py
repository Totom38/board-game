from random import randint
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def afficher_image(matrice):
    labels_légende = {'3 points': 3, '2 points': 2, '1 point': 1}
    couleurs_légende = {3: 'red', 2: 'orange', 1: 'yellow'}
    patches = [mpatches.Patch(color=couleurs_légende[val], label=label) for label, val in labels_légende.items()]
    plt.imshow(matrice, extent=[0, 2 * len(matrice),0, 2 * len(matrice[0])], cmap='autumn')
    plt.legend(handles=patches, loc='upper left', bbox_to_anchor=(1.05, 1))
    plt.show()

def jeu1(n,affichage) :
    n = n // 2
    matrice = [[randint(1,3) for _ in range(n)] for _ in range(n)]
    if affichage :
        afficher_image(matrice)
    somme = 0
    for i in range(len(matrice)) :
        for j in range(len(matrice[0])) :
            somme += matrice[i][j]
    return somme

jeu1(20,True)