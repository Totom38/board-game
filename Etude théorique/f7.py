import f6

def Score_moyen_empirique(n,M) :
    score_moyen=[0]*M
    m=0
    for i in range(M) :
        m+= f6.jeu2(n)
        score_moyen[i]=m/(i+1)
    return score_moyen[0]




# Exemple d'utilisation
n = 3
M = 10
print("Score moyen empirique pour n =", n, "et M =", M, ":", Score_moyen_empirique(n, M))