

import numpy as np
import matplotlib.pyplot as plt

# J'ai tout simplement repris les fonctions des tâches précédentes puis défini la mienne plus bas

#F.3
def Score_Moyen_Etape(p, q, r):
    # Matrice de transition P retrouvée à la tache F2
    P = np.array([[p, q, r], [0, 1-r, r], [0, 0, 1]])
    
    # Vecteur des scores moyens Y_k
    Y_k = np.array([p , q , r ])
    
    # Vecteur des scores moyens Y_k_plus_1
    Y_k_plus_1 = np.dot(P,Y_k)
    
    # Retourne l'espérance théorique de Y_{k+1}
    return Y_k_plus_1[0]+2*Y_k_plus_1[1]+3*Y_k_plus_1[2]

#F.4
def Evol_Probas(p, q, r):


    # Matrice de transition Q retrouvée à la tache F2
    Q = np.array([[1, 0, 0], [p, 1-p, 0], [p, q, r]])

    # Vecteur des scores moyens L_k
    L_k=np.array([p, q, r])

    # Vecteur des scores moyens l_K_plus_1
    L_k_plus_1 = np.dot(Q, L_k)

    return L_k_plus_1

def jeu2(n):

    p, q, r = 1/3, 1/3, 1/3
    
    score_total = 0
    
    grille = np.zeros((2 * n, 2 * n))
    
    for i in range(n):
        score_etape = Score_Moyen_Etape(p, q, r)
        score_total += score_etape
        p, q, r = Evol_Probas(p, q, r)
        
        grille[i * 2 : (i + 1) * 2, :] = score_total
    
    # Affichage de la grille
    plt.imshow(grille, cmap='viridis', interpolation='nearest')
    for i in range(2 * n):
        for j in range(2 * n):
            plt.text(j, i, int(grille[i, j]), ha='center', va='center', color='black')
    plt.title("Grille finale du jeu")
    plt.colorbar(label="Score des tétraminos")
    plt.show()
    
    return score_total

n = 3
score_final = jeu2(n)
print("Score total obtenu dans une grille de taille (", 2 * n, "x", 2 * n, ") :", score_final)