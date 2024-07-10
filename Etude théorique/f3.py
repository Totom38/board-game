import numpy as np

def Score_Moyen_Etape(p, q, r):
    # Matrice de transition P retrouvée à la tache F2
    P = np.array([[p, q, r], [0, 1-r, r], [0, 0, 1]])
    
    # Vecteur des scores moyens Y_k
    Y_k = np.array([p , q , r ])
    
    # Vecteur des scores moyens Y_k_plus_1
    Y_k_plus_1 = np.dot(P,Y_k)
    
    # Retourne l'espérance théorique de Y_{k+1}
    return Y_k_plus_1[0]+2*Y_k_plus_1[1]+3*Y_k_plus_1[2]

# Exemple d'utilisation
p = 0.2
q = 0.3
r = 0.5
print("Espérance théorique de Y_{k+1} :", Score_Moyen_Etape(p, q, r))
