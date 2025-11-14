#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> 
#include "Othello.h"
#include "Affichage.h"
#include "ListePos.h"


int main(int argc, char **argv)
	{
	
	int mode = mode_jeu();
	int plateau[H][H];
	Initialiser_plateau(plateau);
 	Creer_fenetre("2 joueurs");
 	
 	int pi, pj, JoueurCourant = NOIR;
 	cellule_t *liste;
 	
	while(1) {
		
		liste = Trouver_liste_pos_jouables(plateau, JoueurCourant); 
		if (liste == NULL) {
			Dessine_plateau_graph(plateau, JoueurCourant);
			break;
		}
		
		if (mode == 1 && JoueurCourant == BLANC) {
			cellule_t *meilleur = Max_liste(liste);
			pi = meilleur->i;
			pj = meilleur->j;
		}
		
		else if (mode == 2 && JoueurCourant == BLANC) {
			Joueur_Auto_2(plateau, &pi, &pj, liste);
			assert(Est_dans_liste(liste,pi,pj));
		}
		
		else {
			int k;
			do {
				k = Loop_until_play(plateau,&pi,&pj,JoueurCourant);
				if (k == -1) {
					Detruire_liste(liste);
					Detruire_fenetre();
					return 0;
				}
			} while(!Est_dans_liste(liste,pi,pj));
		}
			
			
		plateau[pi][pj] = JoueurCourant;
		Jouer_pion(plateau, pi, pj, JoueurCourant);
		JoueurCourant = Autre_joueur(JoueurCourant);
		Detruire_liste(liste);
	}
	
	liste = Detruire_liste(liste);
	Detruire_fenetre();
	
	int nbN = 0, nbB = 0;
	Nb_pions(plateau, &nbN, &nbB);
	printf("Blanc : %d - Noir : %d\n",nbB, nbN);
	if (nbB > nbN) printf("Victoire Blanc\n");
	else if (nbN > nbB) printf("Victoire Noir\n");
	else printf("Match nul\n");
	
	return 0;
}
