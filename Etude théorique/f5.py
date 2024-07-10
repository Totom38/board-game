import numpy as np

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


#F.5 Score total moyen
def Score_Total_Moyen(n):
    p, q, r = 1/3, 1/3, 1/3
    Score_Total_Moyen=0
    for i in range(n):
        Score_Total_Moyen+=Score_Moyen_Etape(p, q, r)
        p, q, r = Evol_Probas(p, q, r)
    return Score_Total_Moyen



