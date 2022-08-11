#ifndef sonTortue_H
#define sonTortue_H
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

void jouerSon(int numeroVoix);
void jouerTouche(int numeroVoix);
void changeVoix(int emplacementSourisX, int emplacementSourisY, int& numeroVoix, double ratioY, double ratioX);

#endif