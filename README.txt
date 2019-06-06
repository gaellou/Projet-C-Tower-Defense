Comment jouer ?


Ouvrir le dossier dans un terminal.
(Optionnel : pour supprimer les fichiers présents dans le dossier bin, utiliser la commande “make clean”)
Lancer la compilation avec la commande  “make”.
Après compilation, le joueur doit lancer le programme du fichier bin/itd. 
Le programme lui demandera d’entrer le nom du fichier de la carte qu’il souhaite jouer (Ex : map1.itd). Si le nom de fichier n’existe pas, le programme s’arrête. Si le fichier existe, la fenêtre SDL s’ouvre, les variables utiles au jeu sont implémentées, la carte est affichée. Le jeu commence directement avec l’envoie de la première vague.
Le joueur doit cliquer sur les zones constructibles pour ajouter les tours. Par défaut, ce sont les tours de type 1 (les aubergines) qui seront ajouté au clique.  Il est possible de changer le type de tour construite à l’aide des touches suivantes :
        C : Tour de type 1 (aubergine)
        V : Tout de type 2 (poivron)
        B : Tour de Type 3 (pomme)
        N : Tour de type 4 (tomate)
Il faut disposer de suffisamment d’argent pour construire les tours :
        Tour de type 1 : 15 coins 
        Tour de type 2 : 20 coins
        Tour de type 3 : 30 coins
        Tour de type 4 : 10 coins
Si un monstre est dans le rayon d’action d’une tour, la tour tir, le monstre perd de la vie.
Lorsque toutes les vagues de monstres ont été vaincues,  l’écran de victoire d’affiche : le joueur a gagné. Si des monstres atteignent le point de sortie : le joueur a perdu, l’écran e défaite s’affiche.
Il est possible de quitter le jeu à tout moment en appuyant sur la touche Echap ou Q.