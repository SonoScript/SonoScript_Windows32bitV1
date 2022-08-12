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

// ******************************* INCLUSION DES BIBLIOTHEQUES *****************************************
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>//pour faire des instructions simultanement

#include <stdio.h>
#include <stdlib.h> // pour commande system

#include <string> //ecrit
#include <sstream>//pour ostringstream
#include <vector> //tableau
#include <atomic>// synchronisation memoire thread
#include <cmath> //opérations mathématiques
#include <map>//pour tableau de correspondance
#include <thread>

#include <windows.h>

#include "fonctionsRenderer.h"
#include "saveEcrit.h"
#include "evenementSouris.h"
#include "sonTortue.h"

using namespace std;

// ******************************* DEFINITION DES VARIABLES GLOBALES *****************************************

SDL_Window* window;
SDL_Event event;

map<string, int> tableauEquivPhono;

bool operationel = 1;
bool suppressionTableau = 0;
bool play = 0;
bool mouvement = 0;
bool appuie = 0;
bool ongletSave = 0;
bool ongletEcrit = 1;
bool ongletParametres = 0;
bool ajoutSave = 0;

double ratioY;
double ratioX;

int actionsEvent = 0;
int compteMove = 0;
int verificationTouche = 0;
int ToucheArrivee = 0;
int toucheClavierSelectionnee;
int scroll = 0;
int scrollSave = 0;
int compteurx = 0;//emplacement tableau x
int compteury = 1;//emplacement tableau y
int system (const char* command); //demander des commandes a un autre programme
int TIME = 200;// changer en 2 tableau int (1 pour les 36 phonemes et un pour aller avec les ecrits dans le fichier)
/*int FREQ; ajouter 2 tableau int (1 pour les 36 phonemes et un pour aller avec les ecrits dans le fichier)
For a frequency of 133 Hz, maximum duration 7.5 sec. For a frequency of 66.5 Hz, it is 15 sec. For a frequency of 266 Hz, it is 3.75 sec.
int TIMEPOURCENT;*/
int sauvegardeTouche;
int sauvegardeSelectionnee;
int emplacementSourisX = 0;
int emplacementSourisY = 0;
int numeroVoix = 0;

int positionTouches[79][2];
vector <int> selectionTouche;
vector <int> selectionClavier;
vector <int> selectionPhoneme;
vector <string> ecrit;
vector <string> phonemeLu;
vector <string> listeFichierSave;
bool lock [37];

// ******************************* DÉFINITION DES FONCTIONS *****************************************
int file1(void* data)
{
	jouerSon(numeroVoix);
	return 0;
}

int file2(void* data)
{
	boucheTortue(TIME, selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
				 positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
				 ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix,  ratioY, ratioX);
	return 0;
}

int file3(void* data)
{
	jouerTouche(numeroVoix);
	return 0;
}

int file4(void* data)
{
	boucheTortueTouche(TIME, selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
						positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
						ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix,
						ratioY, ratioX, selectionClavier);
	return 0;
}

// ********************************** INITIALISATION *************************************************

int main (int argc, char* args[])
{	
	//Initialisation
	affichageFenetre(window, ratioY, ratioX);
	chargementTextures();
	tableauPhonemelus(phonemeLu);
	positionTouche(positionTouches, selectionTouche, ratioY, ratioX);
	tableauCadenas(lock);
	remove("fichierSon.pho");
	
	//Initialisation sauvegardes
	chargementTableauEquivPhono(phonemeLu, tableauEquivPhono);
	chargementSave(scrollSave, listeFichierSave);
	
	//Initialisation affichage
	afficheAccueil(ratioY, ratioX);
	reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
						positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
						ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
	presenteEcran();

// *************************************** REPERAGE DES EVENEMENTS ********************************************************
	while (operationel)
	{	
		while(SDL_PollEvent(&event))
		{			
			switch(event.type)
			{
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					{
						operationel = 0;
						break;
					}
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						operationel = 0;
						break;
					}
					break;

				case SDL_MOUSEBUTTONDOWN:			
					if(play == 0 && event.button.button==SDL_BUTTON_LEFT)
					{
						emplacementSourisX = event.button.x;
						emplacementSourisY = event.button.y;
						actionsEvent = 1;
					}

					else
					{
						break;
					}
					break;

				case SDL_FINGERDOWN:			
					if(play == 0)
					{
						emplacementSourisX = (event.tfinger.x * (ratioX*1620));
						emplacementSourisY = (event.tfinger.y * (ratioY*1080));
						actionsEvent = 1;
					}
					break;

				case SDL_MOUSEMOTION:
					if(play == 0 && event.button.button==SDL_BUTTON_LEFT && appuie != 0)
					{
						compteMove = compteMove +1;
						
						if(compteMove == 33)
						{
							if(toucheClavierSelectionnee<36)
							{
								emplacementSourisX = (event.motion.x -(54*ratioX));
								emplacementSourisY = (event.motion.y -(40*ratioY));
							}

							else if(toucheClavierSelectionnee == 36)
							{
								emplacementSourisX = (event.motion.x - (20*ratioX));
								emplacementSourisY = (event.motion.y - (20*ratioY));
							}
							actionsEvent = 2;
						}
					}
					break;				

				case SDL_FINGERMOTION:
					if(play == 0 && appuie != 0)
					{
						compteMove = compteMove +1;
						
						if(compteMove == 33)
						{
							if(toucheClavierSelectionnee<36)
							{
								emplacementSourisX = ((event.tfinger.x * (ratioX*1620)) -(54*ratioX));
								emplacementSourisY = ((event.tfinger.y * (ratioY*1080)) -(40*ratioY));
							}

							else if(toucheClavierSelectionnee == 36)
							{
								emplacementSourisX = ((event.tfinger.x * (ratioX*1620))-(20*ratioX));
								emplacementSourisY = ((event.tfinger.y * (ratioY*1080))-(20*ratioY));
							}
							actionsEvent = 2;
						}
					}
					break;	

				case SDL_MOUSEBUTTONUP:
					emplacementSourisX = event.button.x;
					emplacementSourisY = event.button.y;
					actionsEvent = 3;
					break;

				case SDL_FINGERUP:
					emplacementSourisX = (event.tfinger.x * (ratioX*1620));
					emplacementSourisY = (event.tfinger.y * (ratioY*1080));
					actionsEvent = 3;
					break;

				default:
					break;
			}
			
			switch (actionsEvent)
			{
				case 0:
					break;
					
				case 1:
					//reperage de l'onglet
					if(emplacementSourisX < (910*ratioX) && emplacementSourisX > (690*ratioX) && emplacementSourisY < (540*ratioY) && emplacementSourisY > (475*ratioY))
					{
						ongletEcrit = 1;
						ongletSave = 0;
						ongletParametres = 0;
						cout<<"onglet Phonemes"<<endl;
						reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
											positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
											ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
						presenteEcran();
						break;
					}

					if(emplacementSourisX < (1220*ratioX) && emplacementSourisX > (990*ratioX) && emplacementSourisY < (540*ratioY) && emplacementSourisY > (475*ratioY))
					{
						ongletSave = 1;
						ongletEcrit = 0;
						ongletParametres = 0;
						cout<<"onglet Save"<<endl;
						afficherSave(scrollSave, tableauEquivPhono, listeFichierSave, ratioX, ratioY);
						presenteEcran();
						break;
					}

					if(emplacementSourisX < (1500*ratioX) && emplacementSourisX > (1280*ratioX) && emplacementSourisY < (540*ratioY) && emplacementSourisY > (475*ratioY))
					{
						ongletParametres = 1;
						ongletSave = 0;
						ongletEcrit = 0;
						cout<<"onglet Parametres"<<endl;
						afficherPara(numeroVoix, ratioX, ratioY);
						presenteEcran();
						break;
					}

					if(ongletEcrit!=0)
					{
						if(emplacementSourisX < (1550*ratioX) && emplacementSourisX > (620*ratioX) && emplacementSourisY < (930*ratioY) && emplacementSourisY > (550*ratioY))//reperage de la touche appuyee
						{
							int tempSourisX;
							int tempSourisY;
							double hypo = 0;
							double resultat = (65*ratioX);
								
							tempSourisX = emplacementSourisX;
							tempSourisY = emplacementSourisY;
								
							emplacementSourisX = tempSourisX - (54*ratioX);
							emplacementSourisY = tempSourisY - (40*ratioY);

							for(verificationTouche = 0; verificationTouche < 36; verificationTouche++)
							{
								cout<<"comparaison emplacementSouris "<<emplacementSourisX<<" avec coordonnees position touche "<<positionTouches[verificationTouche][0]<<endl;

								hypo = sqrt(pow((emplacementSourisX - positionTouches[verificationTouche][0]), 2) + pow((emplacementSourisY - positionTouches[verificationTouche][1]), 2));
								if(hypo < resultat)
								{
									resultat = hypo;
									cout<<resultat<<endl;
									toucheClavierSelectionnee = verificationTouche;
								}
							}
								
							emplacementSourisX = (tempSourisX - (20*ratioX));
							emplacementSourisY = (tempSourisY - (20*ratioY));

							for(verificationTouche = 37; verificationTouche < 72; verificationTouche++)
							{
								hypo = sqrt(pow((emplacementSourisX - positionTouches[verificationTouche][0]), 2) + pow((emplacementSourisY - positionTouches[verificationTouche][1]), 2));
								if(hypo < resultat)
								{
									resultat = hypo;
									cout<<resultat<<endl;
									toucheClavierSelectionnee = verificationTouche;
								}
							}
							
							//evenements en fonction de la touche appuyee
							cout << "num touche" << toucheClavierSelectionnee << endl;

							if(toucheClavierSelectionnee < 36)
							{
								cout<<"touche"<<endl;
								appuie = 1;
							}

							else if(toucheClavierSelectionnee > 35 && toucheClavierSelectionnee < 72)
							{
								if(lock[(toucheClavierSelectionnee - 36)] = 1)
								{
									lock[(toucheClavierSelectionnee - 36)] = 0;
									reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
														positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
														ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
									presenteEcran();
								}
							}
						}
							
						if(emplacementSourisX < (1275*ratioX) && emplacementSourisX > (895*ratioX) && emplacementSourisY < (995*ratioY) && emplacementSourisY > (935*ratioY))//touche silence
						{
							cout<<"silence"<<endl;
							ecrit.push_back(phonemeLu[36]);
							selectionPhoneme.push_back(36);
								
							compteurx++;
							cout<<"compteurx ="<<compteurx<<endl;
								
							if(compteurx == 10)
							{
								compteury++;
								compteurx = 1;
							}
								
							if(compteury == 4)
							{
								scroll = scroll + 9;
								compteury = 3;
							}
								
							ofstream fichier("fichierSon.pho", ios::app);
							if(fichier.is_open())
							{
								fichier<<phonemeLu[36]<<" "<<TIME<<endl;
							}
							fichier.close();
								
							reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
												positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
												ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
							presenteEcran();
						}
					}

					if(ongletSave!=0)
					{
						if(emplacementSourisX < (1480*ratioX) && emplacementSourisX > (640*ratioX) && emplacementSourisY < (995*ratioY) && emplacementSourisY > (565*ratioY))
						{								
							if((emplacementSourisX < (920*ratioX) && emplacementSourisX > (890*ratioX) && emplacementSourisY < (585*ratioY) && emplacementSourisY > (555*ratioY)) ||
								(emplacementSourisX < (920*ratioX) && emplacementSourisX > (890*ratioX) && emplacementSourisY < (805*ratioY) && emplacementSourisY > (775*ratioY)) ||
								(emplacementSourisX < (1195*ratioX) && emplacementSourisX > (1165*ratioX) && emplacementSourisY < (585*ratioY) && emplacementSourisY > (555*ratioY)) ||
								(emplacementSourisX < (1195*ratioX) && emplacementSourisX > (1165*ratioX) && emplacementSourisY < (805*ratioY) && emplacementSourisY > (775*ratioY)) ||
								(emplacementSourisX < (1480*ratioX) && emplacementSourisX > (1450*ratioX) && emplacementSourisY < (585*ratioY) && emplacementSourisY > (555*ratioY)) ||
								(emplacementSourisX < (1480*ratioX) && emplacementSourisX > (1450*ratioX) && emplacementSourisY < (805*ratioY) && emplacementSourisY > (775*ratioY)))
							{
								suppSave(emplacementSourisX, emplacementSourisY, scrollSave, listeFichierSave, ratioY, ratioX);
								reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
													positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
													ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);	
								presenteEcran();
							}

							else
							{
								ajoutSave = 1;
							}
						}

						//monte vers les saves
						if(emplacementSourisX < (1540*ratioX) && emplacementSourisX > (1490*ratioX) && emplacementSourisY < (765*ratioY) && emplacementSourisY > (675*ratioY) && scrollSave>0)//remonter save
						{
							cout<<"num scrollSave "<<scrollSave<<endl;
							scrollSave = scrollSave - 6;
							afficherSave(scrollSave, tableauEquivPhono, listeFichierSave, ratioX, ratioY);//reafficher uniquement l'onglet
							presenteEcran();
						}

						//descend vers les saves
						if(emplacementSourisX < (1540*ratioX) && emplacementSourisX > (1490*ratioX) && emplacementSourisY < (890*ratioY) && emplacementSourisY > (800*ratioY))//descendre save
						{
							int temporaire;
							temporaire = listeFichierSave.size();
							temporaire = temporaire-6;
							if(scrollSave < temporaire)
							{
								cout<<"num scrollSave "<<scrollSave<<endl;
								scrollSave = scrollSave + 6;
								afficherSave(scrollSave, tableauEquivPhono, listeFichierSave, ratioX, ratioY);//reafficher uniquement l'onglet
								presenteEcran();
							}
						}
					}

					if(ongletParametres!=0)
					{
						if(emplacementSourisX < (1480*ratioX) && emplacementSourisX > (810*ratioX) && emplacementSourisY < (910*ratioY) && emplacementSourisY > (645*ratioY))
						{	
							int voixTemp;
							voixTemp = numeroVoix;

							changeVoix(emplacementSourisX, emplacementSourisY, numeroVoix, ratioX, ratioY);
								
							if(voixTemp!=numeroVoix)
							{
								afficherPara(numeroVoix, ratioX, ratioY);
								presenteEcran();
								play = 1;
							}
						}
					}

					//lier
					if(emplacementSourisX<(1330*ratioX)  && emplacementSourisX>(1295*ratioX)  && emplacementSourisY<(990*ratioY) && emplacementSourisY>(940*ratioY))
					{
						cout<<"cadenas"<<endl;
						toucheClavierSelectionnee = 36;
						sauvegardeTouche = 36;
						appuie = 1;
					}

					//sauvegarder
					if(emplacementSourisX<(735*ratioX) && emplacementSourisX>(670*ratioX) && emplacementSourisY>(260*ratioY) && emplacementSourisY<(325*ratioY))
					{
						cout<<"Bouton sauvegarde"<<endl;
						enregistrement(ecrit, listeFichierSave);
						ongletSave = 1;
						ongletEcrit = 0;
						ongletParametres = 0;
						afficherSave(scrollSave, tableauEquivPhono, listeFichierSave, ratioX, ratioY);
						presenteEcran();
					}

					//supprimer
					if(emplacementSourisX<(750*ratioX) && emplacementSourisX>(670*ratioX) && emplacementSourisY>(365*ratioY) && emplacementSourisY<(435*ratioY))
					{
						cout<<"suppression totale du tableau"<<endl;
						suppressionTableau = 1;
					}

					//flèche haut pour remonter vers 0
					if(emplacementSourisX < (1500*ratioX) && emplacementSourisX > (1440*ratioX) && emplacementSourisY > (185*ratioY) && emplacementSourisY < (275*ratioY) && scroll>0)
					{
						scroll = scroll - 9;
						cout<<"remonte"<<scroll<<endl;
						reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
											positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
											ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
						presenteEcran();
					}

					//flèche bas pour aller vers taille max soit selectionPhoneme.size()
					if(emplacementSourisX < (1500*ratioX) && emplacementSourisX > (1440*ratioX) && emplacementSourisY > (310*ratioY) && emplacementSourisY < (405*ratioY))
					{
						int temporaire;
						temporaire = selectionPhoneme.size();
						temporaire = temporaire-27;

						if(scroll<temporaire)
						{
							scroll = scroll +9;
							cout<<"descend"<<scroll<<endl;
							reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
												positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
												ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
							presenteEcran();
						}
					}
						
					//play
					if(emplacementSourisX<(735*ratioX)  && emplacementSourisX>(670*ratioX)  && emplacementSourisY<(220*ratioY) && emplacementSourisY>(160*ratioY))
					{
						play = 1;
					}
						
					if(emplacementSourisX<(1430*ratioX)  && emplacementSourisX>(800*ratioX)  && emplacementSourisY<(445*ratioY) && emplacementSourisY>(145*ratioY))
					{
						suppIndiv(ratioY, ratioX, scroll, emplacementSourisX, emplacementSourisY, selectionPhoneme, ecrit, TIME);
						reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
											positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
											ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
						presenteEcran();
					}

				actionsEvent = 0;
				break;
					
				case 2:	
					sauvegardeTouche = selectionTouche[toucheClavierSelectionnee];
					mouvement = 1;
					cout <<"mouvement"<< endl;
					reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
										positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
										ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
					presenteEcran();
					compteMove = 0;
					actionsEvent = 0;
				break;

				case 3:
					if(ongletEcrit!=0)
					{
						if(mouvement != 0)
						{
							appuie = 0;
							dragTouche(toucheClavierSelectionnee, selectionTouche, lock, phonemeLu, positionTouches, event, emplacementSourisX, emplacementSourisY, ratioY, ratioX);
							mouvement = 0;
							reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
												positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
												ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
							presenteEcran();
						}

						if(appuie != 0 && toucheClavierSelectionnee < 36)
						{
							insereTouche(appuie, toucheClavierSelectionnee, selectionTouche, ecrit, selectionPhoneme, scroll, lock, phonemeLu, compteurx,
										compteury, TIME, selectionClavier);
							
							SDL_Thread *sonTouche;
							SDL_Thread *imageTouche;
							sonTouche = SDL_CreateThread(file3, "sonTouche", NULL);
							imageTouche = SDL_CreateThread(file4, "imageTouche", NULL);
							SDL_WaitThread(sonTouche, NULL);
							
							reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
												positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
												ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
							presenteEcran();
							cout<<"appuie"<<appuie<<endl;
						}
					}

					if(ajoutSave!=0)
					{
						recupSave(event, ecrit, selectionPhoneme, phonemeLu, tableauEquivPhono,scroll, compteurx, compteury, selectionTouche, emplacementSourisX,
								  emplacementSourisY, positionTouches, scrollSave,listeFichierSave, TIME, play);
						reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
											positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
											ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
						presenteEcran();
						cout<<"grandeur de l'écrit"<<ecrit.size()<<endl;
						ajoutSave = 0;

						cout<<"endroit"<<emplacementSourisX<<endl;
						cout<<"endroit"<<emplacementSourisY<<endl;
					}

					if(play!=0)
					{
						SDL_Thread *son;
						SDL_Thread *image;
						son = SDL_CreateThread(file1, "son", NULL);
						image = SDL_CreateThread(file2, "image", NULL);
						SDL_WaitThread(son, NULL);

						reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
											positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
											ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
						presenteEcran();
						play = 0;
						break;
					}

					if(suppressionTableau!=0)
					{
						compteurx = 0;
						compteury = 1;
						ecrit.clear();
						selectionPhoneme.clear();
						remove("fichierSon.pho");
						scroll = 0;
						reaffichageComplet(selectionPhoneme, selectionTouche, lock, compteurx, compteury, scroll,
											positionTouches, mouvement, emplacementSourisX, emplacementSourisY, sauvegardeTouche,
											ongletSave, ongletParametres, scrollSave, tableauEquivPhono, listeFichierSave, numeroVoix, ratioY, ratioX);
						presenteEcran();

						suppressionTableau = 0;
					}

					actionsEvent = 0;
					break;
					
				default:
					break;
			}
		}
	}
closeSave(listeFichierSave);
nettoyageFermeture(window); //destruction des variables affichage utilisees
return 0;
}