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
#include <iostream> // cin, cout
#include <fstream> //ofstream
#include <sstream> // semble servir a rien
#include <string> //ecrit
#include <vector> //tableau à grandeur variable
#include <cmath> 
#include <map>// tableaux associatifs
#include <windows.h>
#include "saveEcrit.h"

using namespace std;

int	compteurPageSave;
int numeroFichierSave = 0;
FILE *fichier;
FILE *save;

void chargementTableauEquivPhono(vector <string>& phonemeLu, map<string, int>& tableauEquivPhono)
{
	int compteTemp;
	
	for(compteTemp = 0; compteTemp<37; compteTemp++)
	{
		tableauEquivPhono[phonemeLu[compteTemp]]= compteTemp;
	}
}


void chargementSave(int &scrollSave, vector <string>& listeFichierSave) //test fonctionne
{
	string ligneSave;
	compteurPageSave=0;
	
	ifstream openSave("ListeSauvegardes.txt");
	if(openSave.is_open())
	{
		while(getline(openSave, ligneSave))
		{
			cout<<compteurPageSave<<ligneSave<<endl;
			listeFichierSave.push_back(ligneSave);
			numeroFichierSave=numeroFichierSave+1;
			compteurPageSave=compteurPageSave+1;
		}
		cout<<"fin boucle ecriture sauvegarde"<<endl;
		cout<<"nombre de save"<<listeFichierSave.size()<<endl;
		cout<<compteurPageSave<<endl;
		openSave.close();
	}

	else
	{
		cout << "ERREUR : impossible de charger la sauvegarde" << endl;
	}
}


void enregistrement(vector <string> ecrit, vector <string>& listeFichierSave) //test fonctionne
{
	string sequenceTemp;
	string stopper = "c";
	int compteurLettre;

	if(ecrit.size()!=0)
	{
		for(compteurLettre = 0; compteurLettre < ecrit.size(); compteurLettre++)
		{
			sequenceTemp = sequenceTemp + ecrit[compteurLettre] + stopper;
		}
		listeFichierSave.push_back(sequenceTemp);
		numeroFichierSave = numeroFichierSave + 1;
	}
}


void recupSave(SDL_Event event, vector <string>& ecrit, vector <int>& selectionPhoneme, vector <string> phonemeLu, map<string, int> tableauEquivPhono,
			   int &scroll, int &compteurx, int &compteury, vector <int> selectionTouche, int emplacementSourisX, int emplacementSourisY, int positionTouches[79][2],
			   int &scrollSave, vector <string> listeFichierSave, int TIME, bool& play)
{
	double valeurTemporaire;
	double hypoTemp;
	int emplacementsVerifies;
	int selectionFichierSave;
	int imageSave;
	int compteurTemp;
	int endroitScroll;
	string lettreSave;
	string charTemp;
	string copySaveTemp;
	
	for(emplacementsVerifies = 73; emplacementsVerifies < 79; emplacementsVerifies++)
	{
		cout<<"boucle emplacement positionTouche "<<emplacementsVerifies<<endl;
		hypoTemp = sqrt(pow((emplacementSourisX - positionTouches[emplacementsVerifies][0]), 2) + pow((emplacementSourisY - positionTouches[emplacementsVerifies][1]), 2));
		valeurTemporaire = 100;
		if(hypoTemp < valeurTemporaire)
		{
			valeurTemporaire = hypoTemp;
			cout<<valeurTemporaire<<endl;
			selectionFichierSave = ((emplacementsVerifies - 73)+scrollSave);
			cout<<"selection Espace"<<selectionFichierSave<<endl;
			cout<<"valeur scrollsave"<<scrollSave<<endl;
		}
	}

	if(selectionFichierSave < listeFichierSave.size())
	{
		copySaveTemp = listeFichierSave[selectionFichierSave];
		play=1;

		for(compteurTemp=0; compteurTemp < copySaveTemp.size(); compteurTemp++)
		{
			lettreSave = copySaveTemp[compteurTemp];
			charTemp = lettreSave;

			if(charTemp != "c")
			{
				compteurTemp++;
				charTemp = copySaveTemp[compteurTemp];
				if(charTemp != "c")
				{
					lettreSave = lettreSave + copySaveTemp[compteurTemp];
					ecrit.push_back(lettreSave);
					imageSave = tableauEquivPhono[lettreSave];
					selectionPhoneme.push_back(imageSave);
				
					ofstream fichier("fichierSon.pho", ios::app);//changer chemin une fois dossier save creer
					if(fichier.is_open())
					{
						fichier<<lettreSave<<" "<<TIME<<endl;
					}
						fichier.close();

					compteurx++;
					cout<<"compteurx ="<<compteurx<<endl;

					if(compteurx == 10)
					{
						compteury++;
						compteurx = 1;
					}

					if(compteury == 4)
					{
						endroitScroll = (selectionPhoneme.size() - 27);
						for(scroll = 0; scroll<endroitScroll; scroll = scroll + 9)
						{
							cout<<"ajustement scroll"<<scroll<<endl;
						}
						compteury = 3;
					}
				}
				else
				{
					ofstream fichier("fichierSon.pho", ios::app);//changer chemin une fois dossier save creer
					if(fichier.is_open())
					{
						fichier<<lettreSave<<" "<<TIME<<endl;
					}
						fichier.close();
					
					ecrit.push_back(lettreSave);
					imageSave = tableauEquivPhono[lettreSave];
					selectionPhoneme.push_back(imageSave);
					
					compteurx++;
					cout<<"compteurx ="<<compteurx<<endl;

					if(compteurx == 10)
					{
						compteury++;
						compteurx = 1;
					}

					if(compteury == 4)
					{
						endroitScroll = (selectionPhoneme.size() - 27);
						for(scroll = 0; scroll<endroitScroll; scroll = scroll + 9)
						{
							cout<<"ajustement scroll"<<scroll<<endl;
						}
						compteury = 3;
					}
				}
			}

			if(charTemp == "c")
			{
				cout<<"stop"<<endl;
			}
		}
		cout<<"size selectionphoneme"<<selectionPhoneme.size()<<endl;
		cout<<"fin boucle ecriture sauvegarde"<<endl;
	}
}


void suppSave(int emplacementSourisX, int emplacementSourisY, int &scrollSave, vector <string>& listeFichierSave, double ratioY, double ratioX)
{
	double valeurTemporaire;
	double hypoTemp;
	int emplacementsVerifies;
	int rectangle;
	int selectionFichierSave=7;
	int posxCroix[] = {890,1165,1450,890,1165,1450};
	int posyCroix[] = {555,555,555,775,775,775};
	
	for(emplacementsVerifies = 0; emplacementsVerifies < 6; emplacementsVerifies++)
	{
		cout<<"liste fichier save "<<listeFichierSave.size()<<endl;
		hypoTemp = sqrt(pow((emplacementSourisX - (posxCroix[emplacementsVerifies]*ratioX)), 2) + pow((emplacementSourisY - (posyCroix[emplacementsVerifies]*ratioY)), 2));
		cout<<"hypo temp "<<hypoTemp<<endl;
		valeurTemporaire = (150*ratioX);
		if(hypoTemp < valeurTemporaire)
		{
			valeurTemporaire = hypoTemp;
			rectangle = emplacementsVerifies;
			selectionFichierSave = rectangle+scrollSave;
			cout<<"selection supp save "<<selectionFichierSave<<endl;
		}
	}
	
	cout<<"grandeur tableau fichier save "<<listeFichierSave.size()<<endl;
	cout<<"selection supp save "<<selectionFichierSave<<endl;

	if(selectionFichierSave < listeFichierSave.size())
	{
		listeFichierSave.erase(listeFichierSave.begin() + selectionFichierSave); //enlever la sauvegarde du tableau
		numeroFichierSave=numeroFichierSave-1;
		compteurPageSave=compteurPageSave-1;

		if(compteurPageSave==0)
		{
			if(scrollSave!=0)
			{
				scrollSave=scrollSave-6;
				compteurPageSave=6;
			}
		}
	}
}


void closeSave(vector <string>& listeFichierSave)
{
	int compteur;
	
	remove("fichierSon.pho");
	remove("fichierSonTouche.pho");
	system("del fichierSonTouche.wav");
	system("del ListeSauvegardes.txt");

	ofstream repertoireSave("ListeSauvegardes.txt", ios::app); // ouverture en ecriture et efface le contenu du fichier avant
	if(repertoireSave.is_open())
	{
		cout<<"ofstream marche"<<endl;
		if(numeroFichierSave!= 0)
		{
			repertoireSave<<listeFichierSave[0];
		
			for(compteur = 1; compteur < numeroFichierSave; compteur++)
			{
				repertoireSave<<endl<<listeFichierSave[compteur];
			}
			repertoireSave<<flush;
		}
		repertoireSave.close();
	}

	else
	{
		cout << "ERREUR : sauvegarde echoue" << endl;
	}
}