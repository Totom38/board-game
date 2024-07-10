import C2



def Score_moyen_empirique(n,M) :
    score_moyen=[0]*M
    m=0
    for i in range(M) :
        m+= C2.jeu(n,True)
        score_moyen[i]=m/(i+1)
    return score_moyen




