#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ListePos.h"


/*Renvoie une cellule_t */
cellule_t *Creer_cellule(int i, int j, int val)
{
    cellule_t *nCell=malloc(sizeof(cellule_t));
    if (nCell == NULL) {
        fprintf(stderr, "Erreur : malloc\n");
        exit(EXIT_FAILURE);
    }
    nCell->i = i;
    nCell->j = j;
    nCell->val = val;
    nCell->suivant = NULL;
    return nCell;
}

/*
Affiche les champs donnee des elements de la liste
*/
void Afficher_liste(cellule_t *liste)
{
 	while(liste != NULL) {
 		printf("En (%d,%d), retourne %d pions\n",liste->j,liste->i,liste->val);
 		liste = liste->suivant;
 	}
 	printf("\n");
}


/*Renvoie la liste, liste à laquelle un élément de valeur d
a été ajouté en maintenant l'ordre décroissant de val*/
cellule_t *Inserer(int i, int j, cellule_t *liste, int val)
{
	cellule_t *n=Creer_cellule(i,j,val);
  
  /*Liste vide ou nouvelle valeur >= premier élément */
  if (liste == NULL || val >= liste->val) {
    n->suivant = liste;
    return n;
  }
  
  /* Cas 2: Trouver la position d'insertion */
  cellule_t *courant = liste;
  while (courant->suivant != NULL && courant->suivant->val > val) {
    courant = courant->suivant;
  }
  
  n->suivant = courant->suivant;
  courant->suivant = n;
  
  return liste;
}

int Est_dans_liste(cellule_t *liste, int i, int j)
{
 	while(liste != NULL) {
 		if(liste->i == i && liste->j == j) return 1;
 		liste = liste->suivant;
	}
 	return 0;
}

cellule_t *Detruire_liste(cellule_t *liste)
{
	cellule_t *tmp;
 	while(liste != NULL) {
		tmp = liste->suivant;
		free(liste);
		liste = tmp;
		}
	return NULL;
}

/* Retourne le maximum de la liste*/
cellule_t *Max_liste(cellule_t *liste)
{
  /* Comme la liste est triée par ordre décroissant, 
   le max est simplement le premier élément */
  return liste;
}
