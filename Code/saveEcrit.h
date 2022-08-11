#ifndef saveEcrit_H
#define saveEcrit_H
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

void chargementTableauEquivPhono(vector <string>& phonemeLu, map<string, int>& tableauEquivPhono);
void chargementSave(int &scrollSave, vector <string>& listeFichierSave);
void enregistrement(vector <string> ecrit, vector <string>& listeFichierSave);
void recupSave(SDL_Event event, vector <string>& ecrit, vector <int>& selectionPhoneme, vector <string> phonemeLu, map<string, int> tableauEquivPhono,
			   int &scroll, int &compteurx, int &compteury, vector <int> selectionTouche, int emplacementSourisX, int emplacementSourisY, int positionTouches[79][2],
			   int &scrollSave, vector <string> listeFichierSave, int TIME, bool& play);
void suppSave(int emplacementSourisX, int emplacementSourisY, int &scrollSave, vector <string>& listeFichierSave, double ratioY, double ratioX);
void closeSave(vector <string>& listeFichierSave);

#endif