import numpy as np
import matplotlib.pyplot as plt

def Graphe_Score_Empirique( moyenne, n, esperance):

    # Création du nuage de points
    plt.scatter(range(n), moyenne)
    
    # Tracer de la droite horizontale de l'espérance théorique
    plt.axhline(y=esperance_theorique, color='r', linestyle='-')
    
    
    plt.title('Nuage de points du score moyen et espérance théorique')
    plt.xlabel('m')
    plt.ylabel('Score moyen')
    
    # Affichage du graphique
    plt.show()


moyenne = [190,205,195,205,200]  # exemple de vecteur moyenne
n = 5  # exemple de valeur de n
esperance_theorique = (190+205+195+200+205)/5 # exemple de valeur de l'espérance théorique de G_n

Graphe_Score_Empirique(moyenne, n, esperance_theorique)
