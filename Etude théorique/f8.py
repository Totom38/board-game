import f5

import matplotlib.pyplot as plt

    
def Graphe_Score_Moyen(moyenne, n):
    # Création des abscisses (m) et ordonnées (moyenne[m])
    abscisses = range(len(moyenne))
    ordonnees = moyenne
    
    # Calcul du score total moyen théorique
    score_total_moyen = f5.Score_Total_Moyen(n)
    
    # Affichage du nuage de points
    plt.scatter(abscisses, ordonnees, label="Score moyen par étape (moyenne)")
    
    # Affichage de la droite horizontale
    plt.axhline(y=score_total_moyen, color='r', linestyle='--', label="Score total moyen théorique")
    
    # Ajout de labels et légendes
    plt.xlabel('Étapes (m)')
    plt.ylabel('Score moyen')
    plt.title('Nuage de points du score moyen par étape et score total moyen théorique')
    plt.legend()
    
    # Affichage du graphe
    plt.show()

# Exemple d'utilisation avec un vecteur de moyennes et n = 3
moyenne = [10, 20, 30, 40, 50]
n = 3
Graphe_Score_Moyen(moyenne, n)

