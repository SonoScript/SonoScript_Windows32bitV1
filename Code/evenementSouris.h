#ifndef evenementSouris_H
#define evenementSouris_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h> // Necessaire pour commande system
#include <iostream>
#include <fstream>
#include <string> //ecrit
#include <vector> //tableau
#include <cmath>

using namespace std;

void insereTouche(bool &appuie, int &toucheClavierSelectionnee, vector <int>& selectionTouche, vector <string>& ecrit, vector <int>& selectionPhoneme,
				  int &scroll, bool lock [37], vector <string>& phonemeLu, int &compteurx, int &compteury, int TIME, vector <int>& selectionClavier);

void dragTouche(int toucheClavierSelectionnee, vector <int>& selectionTouche, bool lock [37], vector <string>& phonemeLu,
				int positionTouches[81][2], SDL_Event event, int emplacementSourisX, int emplacementSourisY, double ratioY, double ratioX);

void suppIndiv(double ratioY, double ratioX, int& scroll, int emplacementSourisX, int emplacementSourisY, vector <int>& selectionPhoneme,
			   vector <string>& ecrit, int TIME);
	
#endif