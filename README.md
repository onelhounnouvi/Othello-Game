## Othello (Reversi)

Implémentation en C du jeu de plateau classique Othello avec interface graphique SDL.

### À propos du jeu

**Règles :** Consulter [Othello sur Wikipedia](https://fr.wikipedia.org/wiki/Othello_(jeu))

### Modes de jeu disponibles

Le programme propose trois modes de jeu au démarrage :

 **Mode 0 : Deux joueurs**
 **Mode 1 : VS Joueur automatique**
    - Choisit toujours le meilleur coup disponible (celui qui rapporte le plus de pions)

 **Mode 2 : VS Joueur automatique intelligent**
    - Avec anticipation : Simule 2 coups à l'avance
    - Pour chaque coup possible au tour i, il supposera que l’adversaire au tour i+1 jouera le meilleur coup et calculera quel est alors le meilleur coup possible au
    tour i+2.

### Interface graphique
![Texte alternatif](https://imgur.com/OqyXGDq)
- **Pions noirs** : Joueur humain
- **Pions blancs** : IA ou second joueur
- Le pion en haut à gauche indique le joueur actuel
  
### Comment jouer

1. Lancer le programme
2. Choisir un mode (0, 1 ou 2)
3. Cliquer sur une case valide pour placer votre pion
5. La partie se termine quand aucun joueur ne peut jouer

## Organisation

Le programme est organisé en quatre fichiers .c et trois fichiers .h:
- `Affichage.c` et `Affichage.h` qui contiennent toutes les fonctions permettant l’affichage du plateau de jeu
- `ListePos.c` et `ListePos.h` qui contiennent toutes les fonctions de manipulation de listes
- `Othello.c` et `Othello.h` qui contiennent toutes les fonctions concernant le jeu lui même.
- `Main.c` qui est le programme principal.

### Compilation
```bash
make
./Othello
```

### Dépendances

- **SDL2** : Pour l'interface graphique
- **Compilateur C** : gcc ou équivalent

---

*Projet réalisé dans le cadre de l'UE LU1IN002. Les fonctions d'affichages graphiques nous ont été fournies*
