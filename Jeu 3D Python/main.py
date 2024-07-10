import numpy as np
from matplotlib import pyplot as plt
from random import randint

couleurs = ["b","r","g","y","m","c"]

def afficher_3D(taille_x,taille_y,taille_z,terrain,sac,score) :
    plt.ion()
    fig, axes = plt.subplots(2, 2,subplot_kw={'projection': '3d'})
    for k in range(len(terrain)) : # Terrain
        for cube in terrain[k][0] :
            X, Z = np.meshgrid(np.linspace(cube[0] + terrain[k][3][0] , cube[0]+1 + terrain[k][3][0], 2), np.linspace(cube[2]+ terrain[k][3][2], cube[2]+1+ terrain[k][3][2] , 2))
            Y = np.linspace(cube[1]+ terrain[k][3][1], cube[1]+ terrain[k][3][1], 2)
            axes[0][0].plot_surface(X, Y, Z,color=terrain[k][1])
            X, Z = np.meshgrid(np.linspace(cube[0]+ terrain[k][3][0] , cube[0]+1+ terrain[k][3][0], 2), np.linspace(cube[2]+ terrain[k][3][2], cube[2]+1 + terrain[k][3][2], 2))
            Y = np.linspace(cube[1]+1+ terrain[k][3][1], cube[1]+1+ terrain[k][3][1], 2)
            axes[0][0].plot_surface(X, Y, Z,color=terrain[k][1])
            Y, Z = np.meshgrid(np.linspace(cube[1] + terrain[k][3][1], cube[1]+1+ terrain[k][3][1] , 2), np.linspace(cube[2]+ terrain[k][3][2], cube[2]+1 + terrain[k][3][2], 2))
            X = np.linspace(cube[0]+ terrain[k][3][0], cube[0]+ terrain[k][3][0], 2)
            axes[0][0].plot_surface(X, Y, Z,color=terrain[k][1])
            Y, Z = np.meshgrid(np.linspace(cube[1] + terrain[k][3][1], cube[1]+1+ terrain[k][3][1] , 2), np.linspace(cube[2]+ terrain[k][3][2], cube[2]+1 + terrain[k][3][2], 2))
            X = np.linspace(cube[0]+1+ terrain[k][3][0], cube[0]+1+ terrain[k][3][0], 2)
            axes[0][0].plot_surface(X, Y, Z,color=terrain[k][1])
            X, Y = np.meshgrid(np.linspace(cube[0] + terrain[k][3][0], cube[0]+1 + terrain[k][3][0], 2), np.linspace(cube[1]+ terrain[k][3][1], cube[1]+1 + terrain[k][3][1], 2))
            Z = np.zeros(np.shape(X)) + cube[2] + terrain[k][3][2] 
            axes[0][0].plot_surface(X, Y, Z,color=terrain[k][1])
            X, Y = np.meshgrid(np.linspace(cube[0]+ terrain[k][3][0] , cube[0]+1 + terrain[k][3][0], 2), np.linspace(cube[1]+ terrain[k][3][1], cube[1]+1 + terrain[k][3][1], 2))
            Z = np.zeros(np.shape(X)) + cube[2] + 1 + terrain[k][3][2]
            axes[0][0].plot_surface(X, Y, Z,color=terrain[k][1])
    axes[0][0].set_xlim(0, taille_x)
    axes[0][0].set_ylim(0, taille_y)
    axes[0][0].set_zlim(0, taille_z)
    axes[0][0].title.set_text("Score : "+str(score))
    axes[0][0].set_xlabel('x')
    axes[0][0].set_ylabel('y')
    axes[0][0].set_zlabel('z')
    axes[0][0].view_init(elev=20, azim=-135)
    for k in range(len(sac)) : # Sac de taille 3
        if k == 0 :
            k1 , k2 = 0 , 1
        elif k == 1 :
            k1 , k2 = 1 , 0
        elif k == 2 :
            k1 , k2 = 1 , 1
        for cube in sac[k][0] :
            X, Z = np.meshgrid(np.linspace(cube[0] , cube[0]+1 , 2), np.linspace(cube[2], cube[2]+1 , 2))
            Y = np.linspace(cube[1], cube[1], 2)
            axes[k1][k2].plot_surface(X, Y, Z,color=sac[k][1])
            X, Z = np.meshgrid(np.linspace(cube[0] , cube[0]+1 , 2), np.linspace(cube[2], cube[2]+1 , 2))
            Y = np.linspace(cube[1]+1, cube[1]+1, 2)
            axes[k1][k2].plot_surface(X, Y, Z,color=sac[k][1])
            Y, Z = np.meshgrid(np.linspace(cube[1] , cube[1]+1 , 2), np.linspace(cube[2], cube[2]+1 , 2))
            X = np.linspace(cube[0], cube[0], 2)
            axes[k1][k2].plot_surface(X, Y, Z,color=sac[k][1])
            Y, Z = np.meshgrid(np.linspace(cube[1] , cube[1]+1 , 2), np.linspace(cube[2], cube[2]+1 , 2))
            X = np.linspace(cube[0]+1, cube[0]+1, 2)
            axes[k1][k2].plot_surface(X, Y, Z,color=sac[k][1])
            X, Y = np.meshgrid(np.linspace(cube[0] , cube[0]+1 , 2), np.linspace(cube[1], cube[1]+1 , 2))
            Z = np.zeros(np.shape(X)) + cube[2]
            axes[k1][k2].plot_surface(X, Y, Z,color=sac[k][1])
            X, Y = np.meshgrid(np.linspace(cube[0] , cube[0]+1 , 2), np.linspace(cube[1], cube[1]+1 , 2))
            Z = np.zeros(np.shape(X)) + cube[2] + 1 
            axes[k1][k2].plot_surface(X, Y, Z,color=sac[k][1])
            maximum = dimension_max(sac[k]) + 1
            axes[k1][k2].set_xlim(0, maximum)
            axes[k1][k2].set_ylim(0, maximum)
            axes[k1][k2].set_zlim(0, maximum)
        axes[k1][k2].title.set_text("Pièce "+str(k+1)+" ("+str(sac[k][2])+" points)")
        axes[k1][k2].set_xticklabels([])
        axes[k1][k2].set_yticklabels([])
        axes[k1][k2].set_zticklabels([])
        axes[k1][k2].set_xlabel('x')
        axes[k1][k2].set_ylabel('y')
        axes[k1][k2].set_zlabel('z')
        axes[k1][k2].view_init(elev=20, azim=-135)
    plt.show()
    return

def créer_pièce_aléatoire(taille_pièce,compteur_couleur,gamme_score) :
    pièce = [(0,0,0)]
    while len(pièce) < taille_pièce :
        départ , direction = randint(0,len(pièce)-1) , randint(0,2)
        if direction == 0 and (pièce[départ][0]+1,pièce[départ][1],pièce[départ][2]) not in pièce :
            pièce.append((pièce[départ][0]+1,pièce[départ][1],pièce[départ][2]))
        elif direction == 1 and (pièce[départ][0],pièce[départ][1]+1,pièce[départ][2]) not in pièce :
            pièce.append((pièce[départ][0],pièce[départ][1]+1,pièce[départ][2]))
        elif direction == 2 and (pièce[départ][0],pièce[départ][1],pièce[départ][2]+1) not in pièce :
            pièce.append((pièce[départ][0],pièce[départ][1],pièce[départ][2]+1))
    pièce.sort()
    while pièce[0][0] != 0 :
        for i in range(len(pièce)) :
            pièce[i] = (pièce[i][0]-1,pièce[i][1],pièce[i][2])
    while pièce[0][1] != 0 :
        for i in range(len(pièce)) :
            pièce[i] = (pièce[i][0],pièce[i][1]-1,pièce[i][2])
    while pièce[0][2] != 0 :
        for i in range(len(pièce)) :
            pièce[i] = (pièce[i][0],pièce[i][1],pièce[i][2]-1)
    if compteur_couleur == len(couleurs) :
        compteur_couleur = 0
    pièce = (pièce,couleurs[compteur_couleur],gamme_score[randint(0,len(gamme_score)-1)],(0,0,0))
    compteur_couleur += 1
    return pièce , compteur_couleur

def est_plaçable(terrain,pièce,x,y,z) :
    for cube in pièce[0] :
        for k in range(len(terrain)) :
            for cube_terrain in terrain[k][0] :
                if (cube[0]+x,cube[1]+y,cube[2]+z) == (cube_terrain[0]+terrain[k][3][0],cube_terrain[1]+terrain[k][3][1],cube_terrain[2]+terrain[k][3][2]) :
                    return False
    return True

def placer(terrain,pièce,x,y,z) :
    pièce = (pièce[0],pièce[1],pièce[2],(x,y,z))
    terrain.append(pièce)
    return

def dimension_max(pièce) :
    maximum = 0
    for cube in pièce[0] :
        if cube[0] > maximum :
            maximum = cube[0]
        if cube[1] > maximum :
            maximum = cube[1]
        if cube[2] > maximum :
            maximum = cube[2]
    return maximum 

def main(taille_x,taille_y,taille_z,taille_pièce,gamme_score,proportion_obstacle) :
    terrain , sac , score , compteur_couleur = [] , [] , 0 , 0
    for _ in range(3) :
        pièce , compteur_couleur = créer_pièce_aléatoire(taille_pièce,compteur_couleur,gamme_score)
        sac.append(pièce)
    for i in range(taille_x) :
        for j in range(taille_y) :
            for k in range(taille_z) :
                if randint(0,100) < proportion_obstacle*100 :
                    pièce = ([(0,0,0)],"k",0,(0,0,0))
                    placer(terrain,pièce,i,j,k)
    while True :
        afficher_3D(taille_x,taille_y,taille_z,terrain,sac,score)
        choix = int(input("- 1 pour placer une pièce\n- 2 pour déplacer une pièce\n- 3 pour quitter\nChoix : "))
        while choix not in [1,2,3] :
            choix = int(input("Saisie incorrecte, veuillez réessayer : "))
        if choix == 1 : # Placer
            choix = int(input("Choisissez une pièce à placer depuis le sac (1,3): "))
            while choix not in range(1,len(sac)+1) :
                choix = int(input("Saisie incorrecte, veuillez réessayer : "))
            # Rotation en 3 dimensions
            x = int(input("Choisissez x (0,"+str(taille_x-1)+"): "))
            while x not in range(taille_x) :
                x = int(input("Saisie incorrecte, veuillez réessayer : "))
            y = int(input("Choisissez y (0,"+str(taille_y-1)+"): "))
            while y not in range(taille_y) :
                y = int(input("Saisie incorrecte, veuillez réessayer : "))
            z = int(input("Choisissez z (0,"+str(taille_z-1)+"): "))
            while z not in range(taille_z) :
                z = int(input("Saisie incorrecte, veuillez réessayer : "))
            if est_plaçable(terrain,sac[choix-1],x,y,z) :
                placer(terrain,sac[choix-1],x,y,z)
                score += sac.pop(choix-1)[2]
                pièce_à_ajouter , compteur_couleur = créer_pièce_aléatoire(taille_pièce,compteur_couleur,gamme_score)
                sac.append(pièce_à_ajouter)
            else :
                print("Impossible de placer la pièce ici.")
        elif choix == 2 : # Déplacer
            choix = int(input("Choisissez une pièce à déplacer depuis le terrain (1,"+str(len(terrain))+"): "))
            while choix not in range(1,len(terrain)+1) :
                choix = int(input("Saisie incorrecte, veuillez réessayer : "))
            # Rotation en 3 dimensions
            x = int(input("Choisissez x (0,"+str(taille_x-1)+"): "))
            while x not in range(taille_x) :
                x = int(input("Saisie incorrecte, veuillez réessayer : "))
            y = int(input("Choisissez y (0,"+str(taille_y-1)+"): "))
            while y not in range(taille_y) :
                y = int(input("Saisie incorrecte, veuillez réessayer : "))
            z = int(input("Choisissez z (0,"+str(taille_z-1)+"): "))
            while z not in range(taille_z) :
                z = int(input("Saisie incorrecte, veuillez réessayer : "))
            pièce_à_déplacer = terrain.pop(choix-1)
            if est_plaçable(terrain,pièce_à_déplacer,x,y,z) :
                placer(terrain,pièce_à_déplacer,x,y,z)
            else :
                print("Impossible de placer la pièce ici.")
                # Ajouter en laissant la liste triée ?
                terrain.append(pièce_à_déplacer)
        elif choix == 3 : # Quitter
            print("Score final : "+str(score))
            break
        plt.close()
    return

taille_x , taille_y , taille_z , taille_pièce , gamme_score , proportion_obstacle = 9 , 9 , 9 , 3 , [1,2,3,4,5] , 0
          


# Paramètres du jeu

# - taille_x : taille du terrain en x
# - taille_y : taille du terrain en y
# - taille_z : taille du terrain en z
# - taille_pièce : taille des pièces
# - gamme_score : liste des scores possibles pour une pièce
# - proportion_obstacle : proportion d'obstacles sur le terrain

main(taille_x,taille_y,taille_z,taille_pièce,gamme_score,proportion_obstacle)