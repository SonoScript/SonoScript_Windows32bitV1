#ifndef fonctionsRenderer_H
#define fonctionsRenderer_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h> // Necessaire pour commande system
#include <iostream>
#include <fstream>
#include <string> //ecrit
#include <vector> //tableau
#include <cmath>
#include <map>
using namespace std;

void affichageFenetre(SDL_Window* window, double& ratioY, double& ratioX);

void positionTouche(int positionTouches[79][2], vector <int>& selectionTouche, double ratioY, double ratioX);

void chargementTextures();

void tableauCadenas(bool lock[37]);

void tableauPhonemelus(vector <string>& phonemeLu);

void afficheAccueil(double ratioY, double ratioX);

void reaffichageComplet(vector <int>& selectionPhoneme, vector <int>& selectionTouche, bool lock[37], int compteurx, int compteury,
						int& scroll, int positionTouches[79][2], bool mouvement, int emplacementSourisX, int emplacementSourisY,
						int sauvegardeTouche, bool ongletSave, bool ongletParametres, int scrollSave, map<string, int> tableauEquivPhono,
						vector <string> listeFichierSave, int numeroVoix,  double ratioY, double ratioX);

void presenteEcran();

void refreshTableau(vector <int> selectionPhoneme, int compteurx, int compteury);

void afficherSave(int scrollSave, map<string, int> tableauEquivPhono, vector <string> listeFichierSave, double ratioY, double ratioX);

void afficherPara(int numeroVoix, double ratioY, double ratioX);

void boucheTortue(int TIME, vector <int> selectionPhoneme, vector <int>& selectionTouche, bool lock[37], int compteurx, int compteury,
					int& scroll, int positionTouches[79][2], bool mouvement, int emplacementSourisX, int emplacementSourisY,
					int sauvegardeTouche, bool ongletSave, bool ongletParametres, int scrollSave, map<string, int> tableauEquivPhono,
					vector <string> listeFichierSave, int numeroVoix, double ratioY, double ratioX);

void boucheTortueTouche(int TIME, vector <int> selectionPhoneme, vector <int>& selectionTouche, bool lock[37], int compteurx, int compteury,
						int& scroll, int positionTouches[79][2], bool mouvement, int emplacementSourisX, int emplacementSourisY,
						int sauvegardeTouche, bool ongletSave, bool ongletParametres, int scrollSave, map<string, int> tableauEquivPhono,
						vector <string> listeFichierSave, int numeroVoix, double ratioY, double ratioX, vector <int> selectionClavier);

void nettoyageFermeture(SDL_Window* window);

#endif