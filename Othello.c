#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Othello.h"

int mode_jeu()
{
  int mode;
  printf("Selectionner mode de jeu\n0/ 2 joueurs\n1/ VS joueur automatique\n2/ VS joueur automatique intelligent\n");
  printf("\n");
  scanf("%d", &mode);
  return mode;
}

int Autre_joueur(int joueur)
{
  if (joueur == BLANC)
    return NOIR;
  return BLANC;
}

/* Le plateau est numéroté à partir de 0,0 qui représente la case en haut à gauche */

void Initialiser_plateau(int plateau[H][H])
{
  int i, j;
  
  /* Initialiser toutes les cases à vide */
  for (i = 0; i < H; i++) {
    for (j = 0; j < H; j++) {
      plateau[i][j] = VIDE;
    }
  }
  
  /* Placer les pions initiaux */
  plateau[H/2 - 1][H/2 - 1] = BLANC;
  plateau[H/2][H/2 - 1] = NOIR;
  plateau[H/2 - 1][H/2] = NOIR;
  plateau[H/2][H/2] = BLANC;
}

/* Fonction auxiliaire pour copier le plateau */
void Copier_plateau(int src[H][H], int dest[H][H])
{
  int i, j;
  for (i = 0; i < H; i++) {
    for (j = 0; j < H; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

/* Compter et renvoyer le nombre de pions qui seront retournés pour une direction donnée */
int Gain_dir(int plateau[H][H], int iLigne, int iCol, int dirLigne, int dirCol, int couleurQuiJoue)
{
        int i = iLigne + dirLigne;
        int j = iCol + dirCol;
        int nb = 0;
        int couleurAdverse = Autre_joueur(couleurQuiJoue);
        
        /* Compter les pions adverses consécutifs dans cette direction */
	while(i >= 0 && j >= 0 && i < H && j < H && plateau[i][j] == couleurAdverse) {
		nb++;
		i += dirLigne;
		j += dirCol;
	}
  
        /* Valide seulement si on termine sur un de nos propres pions */
        if (i >= 0 && j >= 0 && i < H && j < H && plateau[i][j] == couleurQuiJoue && nb > 0) {
          return nb;
        }
        
  return 0;
}

/* Compter et renvoyer le nombre de pions qui seront retournés dans les 8 directions */
int Est_jouable_gain(int plateau[H][H], int iLigne, int iCol, int couleurQuiJoue)
{
  int nbPionsGagnes = 0;
  
  /* Vérifier que la case est vide */
  if (plateau[iLigne][iCol] != VIDE) {
    return 0;
  }
  
  /* Vérifier les 8 directions */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, 0, -1, couleurQuiJoue);   /* Gauche */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, 0, 1, couleurQuiJoue);    /* Droite */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, -1, 0, couleurQuiJoue);   /* Haut */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, 1, 0, couleurQuiJoue);    /* Bas */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, -1, -1, couleurQuiJoue);  /* Haut-Gauche */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, -1, 1, couleurQuiJoue);   /* Haut-Droite */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, 1, -1, couleurQuiJoue);   /* Bas-Gauche */
  nbPionsGagnes += Gain_dir(plateau, iLigne, iCol, 1, 1, couleurQuiJoue);    /* Bas-Droite */
  return nbPionsGagnes;
}

/* Renvoie la liste des positions jouables, associée chacune avec le gain (nb de pions retournés) */
cellule_t *Trouver_liste_pos_jouables(int plateau[H][H], int couleurQuiJoue)
{
  cellule_t *listePos = NULL;
  int i;
  
  for (i = 0; i < H; i++) {
    int j;
    for (j = 0; j < H; j++) {
      if (plateau[i][j] == VIDE) {
        int val = Est_jouable_gain(plateau, i, j, couleurQuiJoue);
        if (val > 0) {
	  /* Utiliser la fonction Inserer qui fait l'insertion triée */
	  listePos = Inserer(i, j, listePos, val);
        }
      }
    }
  }
  
  return listePos;
}

/* Retourner les pions dans une direction donnée */
void Retourner_pions(int plateau[H][H], int iLigne, int iCol, int dirLigne, int dirCol, int couleurQuiJoue)
{
  int gain = Gain_dir(plateau, iLigne, iCol, dirLigne, dirCol, couleurQuiJoue);
  
  if (gain > 0) {
    int i = iLigne + dirLigne;
    int j = iCol + dirCol;
    
    /* Retourner tous les pions dans cette direction */
    while (gain > 0) {
      plateau[i][j] = couleurQuiJoue;
      i += dirLigne;
      j += dirCol;
      gain--;
    }
  }
}

/* Placer un pion et retourner tous les pions adverses concernés */
void Jouer_pion(int plateau[H][H], int iLigne, int iCol, int couleurQuiJoue)
{
  /* Placer le pion */
  plateau[iLigne][iCol] = couleurQuiJoue;
  
  /* Retourner les pions dans les 8 directions */
  Retourner_pions(plateau, iLigne, iCol, 0, -1, couleurQuiJoue);   /* Gauche */
  Retourner_pions(plateau, iLigne, iCol, 0, 1, couleurQuiJoue);    /* Droite */
  Retourner_pions(plateau, iLigne, iCol, -1, 0, couleurQuiJoue);   /* Haut */
  Retourner_pions(plateau, iLigne, iCol, 1, 0, couleurQuiJoue);    /* Bas */
  Retourner_pions(plateau, iLigne, iCol, -1, -1, couleurQuiJoue);  /* Haut-Gauche */
  Retourner_pions(plateau, iLigne, iCol, -1, 1, couleurQuiJoue);   /* Haut-Droite */
  Retourner_pions(plateau, iLigne, iCol, 1, -1, couleurQuiJoue);   /* Bas-Gauche */
  Retourner_pions(plateau, iLigne, iCol, 1, 1, couleurQuiJoue);    /* Bas-Droite */
}

/* Compter le nombre de pions pour chaque joueur */
void Nb_pions(int plateau[H][H], int *NbN, int *NbB)
{
  int i, j;
  *NbN = 0;
  *NbB = 0;
  
  for (i = 0; i < H; i++) {
    for (j = 0; j < H; j++) {
      if (plateau[i][j] == NOIR) {
        (*NbN)++;
      } else if (plateau[i][j] == BLANC) {
        (*NbB)++;
      }
    }
  }
}

/* Joueur automatique avec anticipation de 2 coups */
void Joueur_Auto_2(int plateau[H][H], int *pi, int *pj, cellule_t *liste)
{
	int meilleur_gain = -1;
	cellule_t *coup = liste;
	
	/* Pour chaque coup possible au tour i */
	while (coup != NULL) {
		int plateau_temp[H][H];
		int gain_final = 0;
		
		Copier_plateau(plateau, plateau_temp);
		
		/* Jouer le coup c au tour i (BLANC) */
		Jouer_pion(plateau_temp, coup->i, coup->j, BLANC);
		
		/* Calculer les coups possibles de l'adversaire au tour i+1 */
		cellule_t *liste_adv = Trouver_liste_pos_jouables(plateau_temp, NOIR);
		
		if (liste_adv != NULL) {
			/* Trouver le meilleur coup de l'adversaire au tour i+1 */
			cellule_t *meilleur_adv = Max_liste(liste_adv);
			
			/* Jouer ce coup au tour i+1 */
			Jouer_pion(plateau_temp, meilleur_adv->i, meilleur_adv->j, NOIR);
			
			Detruire_liste(liste_adv);
			
			/* Calculer les coups possibles pour nous au tour i+2 */
			cellule_t *liste_i2 = Trouver_liste_pos_jouables(plateau_temp, BLANC);
			
			if (liste_i2 != NULL) {
				/* Trouver le meilleur coup au tour i+2 */
				cellule_t *meilleur_i2 = Max_liste(liste_i2);
				
				/* Calculer le gain réel de ce coup sur le plateau temporaire */
				gain_final = Est_jouable_gain(plateau_temp, meilleur_i2->i, meilleur_i2->j, BLANC);
				
				Detruire_liste(liste_i2);
			}
		}
		
		/* Garder le coup c si le gain final est meilleur */
		if (gain_final > meilleur_gain) {
			*pi = coup->i;
			*pj = coup->j;
			meilleur_gain = gain_final;
		}
		
		coup = coup->suivant;
	}
}
