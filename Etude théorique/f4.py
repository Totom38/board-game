import numpy as np

def Evol_Probas(p, q, r):


    # Matrice de transition Q retrouvée à la tache F2
    Q = np.array([[1, 0, 0], [p, 1-p, 0], [p, q, r]])

    # Vecteur des scores moyens L_k
    L_k=np.array([p, q, r])

    # Vecteur des scores moyens l_K_plus_1
    L_k_plus_1 = np.dot(Q, L_k)

    return L_k_plus_1


# Exemple d'utilisation
p = 0.2
q = 0.3
r = 0.5
print("Espérance théorique de L_{k+1} :", Evol_Probas(p, q, r))
