/*
TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

SonoScript version 1 is a software intended for the development of phonemic awareness of young children.
Copyright (C) 2022 Mélissa Brunet

Université de Montréal, hereby disclaims all copyright interest
in the program "SonoScript" written by Mélissa Brunet.
The PDF document proving this can be provide on demand.

This program is free software; you can redistribute it and/or modify it under the terms of
the GNU General Public License version 2 as published by the Free Software Foundation.
Any version redistributed or modified must also use the GNU General Public License version 2.
Any version redistributed or modified must indicate that the original work was made by the programmer "Mélissa Brunet"
Any modified version must detail the modifications made in the new version and indicate that the use of the original work 
or of part of the original work "SonoScript" doesn't mean that the author of SonoScript approve of the modified version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License version 2 for more details.

You should have received a copy of the GNU General Public License version 2 in a text file
along with this program; if not, visit "https://www.gnu.org/licenses/old-licenses/gpl-2.0.fr.html#SEC3" to see it
or write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

To signal a bug or to ask a question, you can contact the programmer "Mélissa Brunet" by email at : "SonoScript@outlook.com".

*********************************************************************************************************************

ART WORK LICENSE

The art work used for this game (at the exception of the trademark "SonoScript") is licensed under
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License (CC-BY-NC-SA).
You should have received a copy of the CC-BY-NC-SA licence in a text file along with this program;
if not, to view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode.
The license is also available in other langages at the link just given.

As such, any image used in this game (at the exception of the trademark "SonoScript") may be copied, distributed or modified
only for non-commercial purpose and at the following conditions:
Any version redistributed or modified must also use
the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License (CC-BY-NC-SA).
Any version redistributed or modified must indicate that the original work was made by a collaboration of
the artist "Patricia Cormier" and the inventor "Mélissa Brunet"
and that the original work can be found in the program "SonoScript" made by "Mélissa Brunet".
Any modified version must detail the modifications made in the new version and indicate that the use of the original art work 
or of part of the original art work doesn't mean that the authors of the original work approve of the modified version.

For any other use, you must get the permission of both the artist "Patricia Cormier" and the inventor "Mélissa Brunet".
You can contact the artist "Patricia Cormier" by email at: "cormier.patricia.2@gmail.com".


TRADEMARK POLICY

The trademark "SonoScript" may only be use without prior autorisation if the version distributed is the original one as a whole
and if it is use with the original "SonoScript" program made by "Mélissa Brunet".

To use the trademark image of "SonoScript" in any other way, you must get the autorisation of the author of "SonoScript"
since the rights for the trademark image have been given to "Mélissa Brunet" by "Patricia Cormier".

To obtain permission, you can contact the author of "SonoScript", Mélissa Brunet, by email at : "SonoScript@outlook.com".
*/

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
#include "fonctionsRenderer.h"
#include "evenementSouris.h"
#include <iomanip>

using namespace std;

// declaration des variables globales (si certaines sont problematiques les transformer en fonctions)
SDL_Renderer* renderer;
SDL_Texture* screenTexture;
SDL_Texture* screenAccueil;
SDL_Texture* textureOngletSave;
SDL_Texture* tortueBasic;
SDL_Texture* textureCroix;
vector <SDL_Texture*> textureTableau;
vector <SDL_Texture*> texturePhonemes;
vector <SDL_Texture*> textureOngletPara;
vector <SDL_Texture*> textureBouche;


void affichageFenetre(SDL_Window* window, double& ratioY, double& ratioX)
{
double SCREEN_WIDTH = 1620;
double SCREEN_HEIGHT = 1080;
int DESK_WIDTH;
int DESK_HEIGHT;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		printf("SDL n'a pas pu être initialisé. SDL_Error : %s/n",SDL_GetError());
	}

	else
	{
		SDL_DisplayMode DM;

		window = SDL_CreateWindow("SonoScript", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		if( window == NULL )
		{
			printf("La fenêtre n'a pas pu être créée. SDL_Error: %s\n",
			SDL_GetError());
		}

		SDL_GetRendererOutputSize(renderer, &DESK_WIDTH, &DESK_HEIGHT);
		cout<<"largeur ecran" << DESK_WIDTH << endl;
		cout<<"largeur window" << SCREEN_WIDTH << endl;
		cout<<"hauteur ecran" << DESK_HEIGHT << endl;
		cout<<"hauteur window"<< SCREEN_HEIGHT<<endl;

		ratioX = DESK_WIDTH/SCREEN_WIDTH;
		ratioY = (DESK_HEIGHT-50)/SCREEN_HEIGHT;

		cout<<setprecision(8);
		cout<<"ratioX"<<ratioX<<endl;
		cout<<"ratioY"<<ratioY<<endl;

		SCREEN_WIDTH = SCREEN_WIDTH * ratioX;
		SCREEN_HEIGHT = SCREEN_HEIGHT * ratioY;
		
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, DESK_WIDTH, (DESK_HEIGHT-50));
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
}

void positionTouche(int positionTouches[79][2], vector <int>& selectionTouche, double ratioY, double ratioX)
{
	int positionToucheX;
	int positionToucheY;
	int compteurTouche;
	double resultMulti;
	
	ifstream repertoireTouches("Repertoires/RepertoireTouches.txt");
	if(repertoireTouches.is_open())
	{
		for(compteurTouche = 0; compteurTouche<79; compteurTouche++)
		{
			repertoireTouches >> positionToucheX; //récupère la position x
			repertoireTouches >> positionToucheY; //récupère la position y
			
			resultMulti = positionToucheX*ratioX;
			positionTouches[compteurTouche][0] = resultMulti;//stocke la position x dans le tableau
			resultMulti = positionToucheY*ratioY;
			positionTouches[compteurTouche][1] = resultMulti;//stocke la position y dans le tableau
		}
		repertoireTouches.close();
		compteurTouche=0;
		cout<<"fin boucle position Touche"<<endl;
	}
		
	else
	{
		cout << "ERREUR : impossible de définir les rectangles" << endl;
	}

	for(compteurTouche = 0; compteurTouche<37; compteurTouche++)
	{
		selectionTouche.push_back(compteurTouche);
	}
	compteurTouche = 0;
}



void chargementTextures()
{
	string ligne;
	SDL_Surface* Background;
	SDL_Surface* ongletSave;
	SDL_Surface* tortueBase;
	SDL_Surface* tempPlay;
	SDL_Surface* tempTrash;
	SDL_Surface* tempCroix;
	
	Background = IMG_Load("ImagesJeu/Background.png");
	if (Background == NULL)
	{
		printf("Erreur chargement Background");
	}
	screenTexture = SDL_CreateTextureFromSurface(renderer, Background);
	SDL_FreeSurface(Background); // liberation de la memoire
	
	
	Background = IMG_Load("ImagesJeu/accueil.png");
	if (Background == NULL)
	{
		printf("Erreur chargement accueil");
	}
	screenAccueil = SDL_CreateTextureFromSurface(renderer, Background);
	SDL_FreeSurface(Background); // liberation de la memoire
	
	
	ifstream repertoireImageTouches("Repertoires/RepertoireImageTouches.txt");
	if(repertoireImageTouches.is_open())
	{
		while(getline(repertoireImageTouches, ligne))
		{
			SDL_Surface* surfaceTemporaire;
			surfaceTemporaire = IMG_Load(ligne.c_str());
			
			if (surfaceTemporaire == NULL)
			{
				cout<<"Erreur chargement images phonèmes"<<endl;
			}
			
			else
			{
				texturePhonemes.push_back(SDL_CreateTextureFromSurface(renderer, surfaceTemporaire));
				SDL_FreeSurface(surfaceTemporaire);
			}
		}
		repertoireImageTouches.close();
	}
	else
	{
		cout << "ERREUR : impossible d'ouvrir le répertoire d'images touches." << endl;
	}

	ifstream repertoireImageTableau("Repertoires/RepertoireImageTableau.txt");
	if(repertoireImageTableau.is_open())
	{
		while(getline(repertoireImageTableau, ligne))
		{
			SDL_Surface *surfaceTemporaire;
			surfaceTemporaire = IMG_Load(ligne.c_str());
			textureTableau.push_back(SDL_CreateTextureFromSurface(renderer, surfaceTemporaire));
			SDL_FreeSurface(surfaceTemporaire);
		
			if (surfaceTemporaire == NULL)
			{
				cout<<"Erreur chargement images tableau"<<endl;
			}
		}
		repertoireImageTableau.close();
	}
	else
	{
		cout << "ERREUR : impossible d'ouvrir le répertoire d'images tableau." << endl;
	}

	ifstream RepertoireImagePara("Repertoires/RepertoireImagePara.txt");
	if(RepertoireImagePara.is_open())
	{
		while(getline(RepertoireImagePara, ligne))
		{
			SDL_Surface* surfaceTemporaire;
			surfaceTemporaire = IMG_Load(ligne.c_str());
			
			if (surfaceTemporaire == NULL)
			{
				cout<<"Erreur chargement images ongletPara"<<endl;
			}
			
			else
			{
				textureOngletPara.push_back(SDL_CreateTextureFromSurface(renderer, surfaceTemporaire));
				SDL_FreeSurface(surfaceTemporaire);
			}
		}
		RepertoireImagePara.close();
	}
	
	ifstream RepertoireBouche("Repertoires/RepertoireBouche.txt");
	if(RepertoireBouche.is_open())
	{
		while(getline(RepertoireBouche, ligne))
		{
			SDL_Surface* surfaceTemporaire;
			surfaceTemporaire = IMG_Load(ligne.c_str());
			
			if (surfaceTemporaire == NULL)
			{
				cout<<"Erreur chargement images bouches"<<endl;
			}
			
			else
			{
				textureBouche.push_back(SDL_CreateTextureFromSurface(renderer, surfaceTemporaire));
				SDL_FreeSurface(surfaceTemporaire);
			}
		}
		RepertoireBouche.close();
	}
	
	ongletSave = IMG_Load("ImagesJeu/ongletSave.png");
	if (ongletSave == NULL)
	{
		printf("Erreur chargement ongletSave");
	}
	textureOngletSave = SDL_CreateTextureFromSurface(renderer, ongletSave);
	SDL_FreeSurface(ongletSave); // liberation de la memoire


	tortueBase = IMG_Load("ImagesJeu/Tortue/tortueBase.png");
	if (tortueBase == NULL)
	{
		printf("Erreur chargement tortueBase");
	}
	tortueBasic = SDL_CreateTextureFromSurface(renderer, tortueBase);
	SDL_FreeSurface(tortueBase); // liberation de la memoire
	
	
	tempCroix = IMG_Load("ImagesJeu/Icones/croix.png");
	if (tempCroix == NULL)
	{
		printf("Erreur chargement de la croix");
	}
	textureCroix = SDL_CreateTextureFromSurface(renderer, tempCroix);
	SDL_FreeSurface(tempCroix); // liberation de la memoire
}


void tableauCadenas(bool lock[37])
{
	int compteurTouche;
	
	for(compteurTouche = 0; compteurTouche < 37; compteurTouche++)
	{
		lock[compteurTouche] = 0;
	}
}


void tableauPhonemelus(vector <string>& phonemeLu)
{
	string ligne;
	
	ifstream repertoireTableauEcrit("Repertoires/RepertoireTableauEcrit.txt");
	if(repertoireTableauEcrit.is_open())
	{
		while(getline(repertoireTableauEcrit, ligne))
		{	
			phonemeLu.push_back(ligne);
		}
		repertoireTableauEcrit.close();
	}

	else
	{
		cout << "ERREUR : impossible de définir le tableau des phonèmes écrits" << endl;
	}
}


void afficheAccueil(double ratioY, double ratioX)
{
	int grandeurEcranW = (1620*ratioX);
	int grandeurEcranH = (1080*ratioY);
	SDL_Rect grandeurEcran = {0, 0, grandeurEcranW, grandeurEcranH};
	
	SDL_RenderCopy(renderer, screenAccueil, NULL, &grandeurEcran);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
}


void reaffichageComplet(vector <int>& selectionPhoneme, vector <int>& selectionTouche, bool lock[37], int compteurx, int compteury,
						int& scroll, int positionTouches[79][2], bool mouvement, int emplacementSourisX, int emplacementSourisY,
						int sauvegardeTouche, bool ongletSave, bool ongletParametres, int scrollSave, map<string, int> tableauEquivPhono,
						vector <string> listeFichierSave, int numeroVoix, double ratioY, double ratioX)
{
	int compteurTouche;
	int compteurlock;
	int grandeurEcranW = (1620*ratioX);
	int grandeurEcranH = (1080*ratioY);
	int positionTortueX = (100*ratioX);
	int positionTortueY = (210*ratioY);
	int positionTortueW = (428*ratioX);
	int positionTortueH = (695*ratioY);
	int touchesClavierW = (107*ratioX);
	int touchesClavierH = (86*ratioY);
	int cadenasW = (31*ratioX);
	int cadenasH = (40*ratioY);
	int positionTableauW = (70*ratioX);
	int positionTableauH = (70*ratioY);
	int positionCroixW = (20*ratioX);
	int positionCroixH = (20*ratioY);
	int touchesDeplaceW = (107*ratioX);
	int touchesDeplaceH = (86*ratioY);
	
	SDL_Rect grandeurEcran = {0, 0, grandeurEcranW, grandeurEcranH};
	SDL_Rect positionTortue = {positionTortueX,positionTortueY,positionTortueW,positionTortueH};
	SDL_Rect touchesClavier{0, 0, touchesClavierW, touchesClavierH};
	SDL_Rect cadenas{0, 0, cadenasW, cadenasH};
	SDL_Rect positionTableau{0, 0, positionTableauW, positionTableauH};
	SDL_Rect positionCroix{0,0,positionCroixW,positionCroixH};
	SDL_Rect touchesDeplace{0, 0, touchesDeplaceW, touchesDeplaceH};
	
	
	SDL_RenderClear(renderer);//effacer l'affichage
	SDL_RenderCopy(renderer, screenTexture, NULL, &grandeurEcran);//afficher arrière-plan
	SDL_RenderCopy(renderer, tortueBasic, NULL, &positionTortue);//afficher Tortue de base
	
	for(compteurTouche = 0; compteurTouche<36; compteurTouche++)//Afficher les touches du clavier;
	{
		touchesClavier.x = positionTouches[compteurTouche][0];
		touchesClavier.y = positionTouches[compteurTouche][1];
		SDL_RenderCopy(renderer, texturePhonemes[selectionTouche[compteurTouche]], NULL, &touchesClavier);//erreur Segmentation ici
	}

	compteurlock = 0;
	
	for(compteurTouche = 36; compteurTouche < 72; compteurTouche++)
	{
		if(lock[compteurlock] != 0)
		{
			cadenas.x = positionTouches[compteurTouche][0];
			cadenas.y = positionTouches[compteurTouche][1];
			SDL_RenderCopy(renderer, texturePhonemes[36], NULL, &cadenas); //choisir emplacement texture et rectangle position
		}
		compteurlock++;
	}
		compteurTouche = 0;
		compteurx = 0;
		compteury = 1;

	for(compteurTouche = 0; compteurTouche < 27; compteurTouche++)//affichage tableau
	{
		if((scroll+compteurTouche) < (selectionPhoneme.size()))
		{
			compteurx++;

			if(compteurx == 10)
			{
				compteury++;
				compteurx = 1;
			}

			positionTableau.x = (750*ratioX) + (compteurx * (65*ratioX));
			positionTableau.y = (70*ratioY) + (compteury * (95*ratioY));
			SDL_RenderCopy(renderer, textureTableau[selectionPhoneme[(scroll+compteurTouche)]], NULL, &positionTableau);

			positionCroix.x = (805*ratioX) + (compteurx * (65*ratioX));
			positionCroix.y = (70*ratioY) + (compteury * (95*ratioY));
			SDL_RenderCopy(renderer, textureCroix, NULL, &positionCroix);
		}

		else
		{
			break;
		}
	}
	compteurTouche = 0;
	
	if(mouvement!=0)
	{
		if(sauvegardeTouche<36)
		{
			touchesDeplace.x = emplacementSourisX;
			touchesDeplace.y = emplacementSourisY;
			SDL_RenderCopy(renderer, texturePhonemes[sauvegardeTouche], NULL, &touchesDeplace);
		}
		
		else if(sauvegardeTouche = 36)
		{
			cadenas.x = emplacementSourisX;
			cadenas.y = emplacementSourisY;
			SDL_RenderCopy(renderer, texturePhonemes[36], NULL, &cadenas);
		}
	}
	
	if(ongletSave!=0)
	{
		afficherSave(scrollSave, tableauEquivPhono, listeFichierSave, ratioX, ratioY);
	}
					
	if(ongletParametres!=0)
	{
		afficherPara(numeroVoix,ratioX, ratioY);
	}
}


void presenteEcran()
{
	SDL_RenderPresent(renderer);
}


void refreshTableau(vector <int> selectionPhoneme, int compteurx, int compteury)
{
	SDL_Rect positionTableau{0, 0, 70, 70};
	
	positionTableau.x = 750 + (compteurx * 75);
	positionTableau.y = 70 + (compteury * 95);
	SDL_RenderCopy(renderer, textureTableau[selectionPhoneme[(selectionPhoneme.size()-1)]], NULL, &positionTableau);
	SDL_RenderPresent(renderer);
}


void afficherSave(int scrollSave, map<string, int> tableauEquivPhono, vector <string> listeFichierSave, double ratioY, double ratioX)
{
	int compteurTemp = 0;
	int compteurImage;
	int textureSave;
	int temporaire;
	int adiScroll;
	int xTemp=0;
	int yTemp=1;
	string imageSave;
	string lettreSave;
	string charTemp;
	int posxTemp[] ={610,890,1165,610,890,1170};
	int posyTemp[] ={530,530,530,750,750,750};
	
	int positionCroixW = (30*ratioX);
	int positionCroixH = (30*ratioY);
	
	SDL_Rect positionCroix{0,0,positionCroixW,positionCroixH};
	int posxCroix[] = {890,1165,1450,890,1165,1450};
	int posyCroix[] = {555,555,555,775,775,775};
	
	int positionSaveW = (44*ratioX);
	int positionSaveY = (35*ratioY);
	SDL_Rect positionSave{0,0,positionSaveW,positionSaveY};// grandeur des images a ajuster
	
	int positionOngletSaveX = (612*ratioY);
	int positionOngletSaveY = (465*ratioX);
	int positionOngletSaveW = (952*ratioY);
	int positionOngletSaveH = (557*ratioX);
	SDL_Rect positionOngletSave{positionOngletSaveX,positionOngletSaveY,positionOngletSaveW,positionOngletSaveH};

	cout<<"position x onglet save "<<positionOngletSaveX<<endl;
	cout<<"position y onglet save "<<positionOngletSaveY<<endl;
	cout<<"ratio x "<<ratioX<<endl;
	cout<<"ratio y "<<ratioY<<endl;
	
	SDL_RenderCopy(renderer, textureOngletSave, NULL, &positionOngletSave);

	for(compteurTemp=0; compteurTemp<6; compteurTemp++)
	{
		adiScroll = scrollSave+compteurTemp;
		temporaire = listeFichierSave.size();

		if(adiScroll < temporaire)
		{
			imageSave = listeFichierSave[adiScroll];
			int xTemp=0;
			int yTemp=1;

			for(compteurImage = 0; compteurImage < imageSave.size(); compteurImage++)
			{
				if(yTemp < 6)
				{
					lettreSave = imageSave[compteurImage];
					charTemp = lettreSave;

					if(charTemp != "c")
					{
						compteurImage++;
						charTemp = imageSave[compteurImage];
						if(charTemp != "c")
						{
							lettreSave = lettreSave + imageSave[compteurImage];
							textureSave = tableauEquivPhono[lettreSave];

							xTemp = xTemp +1;
							if(xTemp==10)
							{
								yTemp=yTemp+1;
								xTemp=1;
							}

							if(yTemp<6)
							{
								positionSave.x = (posxTemp[compteurTemp]*ratioY) + (xTemp * (28*ratioY));
								positionSave.y = (posyTemp[compteurTemp]*ratioX) + (yTemp * (40*ratioX));
								SDL_RenderCopy(renderer, textureTableau[textureSave], NULL, &positionSave);
							}
						}
						
						else
						{
							textureSave = tableauEquivPhono[lettreSave];

							xTemp = xTemp +1;
							if(xTemp==10)
							{
								yTemp=yTemp+1;
								xTemp=1;
							}
							
							if(yTemp<6)
							{
								positionSave.x = (posxTemp[compteurTemp]*ratioY) + (xTemp * (28*ratioY));
								positionSave.y = (posyTemp[compteurTemp]*ratioX) + (yTemp * (40*ratioX));
								SDL_RenderCopy(renderer, textureTableau[textureSave], NULL, &positionSave);
							}
						}
					}

					if(charTemp == "c")
					{
					}
				}
			}
			positionCroix.x = (posxCroix[compteurTemp]*ratioY);
			positionCroix.y = (posyCroix[compteurTemp]*ratioX);
			SDL_RenderCopy(renderer, textureCroix, NULL, &positionCroix);//copier texture croix au coin des rectangles
		}
	}
}


void afficherPara(int numeroVoix, double ratioY, double ratioX)
{
	int compteur;
	int select;

	int positionOngletSaveX = (612*ratioY);
	int positionOngletSaveY = (465*ratioX);
	int positionOngletSaveW = (952*ratioY);
	int positionOngletSaveH = (557*ratioX);
	
	int positionVoixY = (805*ratioX);
	int positionVoixW = (73*ratioY);
	int positionVoixH = (73*ratioX);
	int posVoixX1 = (870*ratioY);
	int posVoixX2 = (1010*ratioY);
	int posVoixX3 = (1190*ratioY);
	int posVoixX4 = (1350*ratioY);
	
	SDL_Rect positionOngletSave= {positionOngletSaveX,positionOngletSaveY,positionOngletSaveW,positionOngletSaveH};
	SDL_Rect positionVoix{0,positionVoixY,positionVoixW,positionVoixH};
	int positionVoixX[]={posVoixX1, posVoixX2, posVoixX3, posVoixX4};

	SDL_RenderCopy(renderer, textureOngletPara[0], NULL, &positionOngletSave);
	positionVoix.x = positionVoixX[numeroVoix];
	SDL_RenderCopy(renderer, textureOngletPara[1], NULL, &positionVoix);
}


void boucheTortue(int TIME, vector <int> selectionPhoneme, vector <int>& selectionTouche, bool lock[37], int compteurx, int compteury,
					int& scroll, int positionTouches[79][2], bool mouvement, int emplacementSourisX, int emplacementSourisY,
					int sauvegardeTouche, bool ongletSave, bool ongletParametres, int scrollSave, map<string, int> tableauEquivPhono,
					vector <string> listeFichierSave, int numeroVoix, double ratioY, double ratioX)
{
	int positionBoucheX = (270*ratioX);
	int positionBoucheY = (350*ratioY);
	int positionBoucheW = (98*ratioX);
	int positionBoucheH = (58*ratioY);
	
	SDL_Rect positionBouche{positionBoucheX,positionBoucheY, positionBoucheW, positionBoucheH};
	int numeroBouche[] = {0,3,2,7,11,10,9,2,1,2,2,2,8,9,8,4,7,9,10,8,8,11,11,5,6,6,11,9,8,8,4,2,8,6,0,9,12};
	int compte;
	
	for(compte = 0; compte < selectionPhoneme.size(); compte++)
	{
		reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
							positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
							ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix,  ratioY, ratioX);
		SDL_RenderCopy(renderer, textureBouche[numeroBouche[(selectionPhoneme[compte])]], NULL, &positionBouche);
		SDL_RenderPresent(renderer);
		SDL_Delay(TIME);
	}
}

void boucheTortueTouche(int TIME, vector <int> selectionPhoneme, vector <int>& selectionTouche, bool lock[37], int compteurx, int compteury,
						int& scroll, int positionTouches[79][2], bool mouvement, int emplacementSourisX, int emplacementSourisY,
						int sauvegardeTouche, bool ongletSave, bool ongletParametres, int scrollSave, map<string, int> tableauEquivPhono,
						vector <string> listeFichierSave, int numeroVoix, double ratioY, double ratioX, vector <int> selectionClavier)
{
	int positionBoucheX = (270*ratioX);
	int positionBoucheY = (350*ratioY);
	int positionBoucheW = (98*ratioX);
	int positionBoucheH = (58*ratioY);
	
	SDL_Rect positionBouche{positionBoucheX,positionBoucheY, positionBoucheW, positionBoucheH};
	int numeroBouche[] = {0,3,2,7,11,10,9,2,1,2,2,2,8,9,8,4,7,9,10,8,8,11,11,5,6,6,11,9,8,8,4,2,8,6,0,9,12};
	int compte;
	
	for(compte = 0; compte < selectionClavier.size(); compte++)
	{
		reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
							positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
							ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix,  ratioY, ratioX);
		SDL_RenderCopy(renderer, textureBouche[numeroBouche[(selectionClavier[compte])]], NULL, &positionBouche);
		SDL_RenderPresent(renderer);
		SDL_Delay(TIME);
	}
}


void nettoyageFermeture(SDL_Window* window)
{
	SDL_DestroyTexture(screenTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	void TTF_Quit(void);
	void SDL_Quit(void);
}