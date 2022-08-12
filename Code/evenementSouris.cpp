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
#include <sstream>//pour ostringstream
#include <string> //ecrit
#include <vector> //tableau
#include <cmath>
#include "evenementSouris.h"
#include "fonctionsRenderer.h"

using namespace std;


void insereTouche(bool &appuie, int &toucheClavierSelectionnee, vector <int>& selectionTouche, vector <string>& ecrit, vector <int>& selectionPhoneme,
				  int &scroll, bool lock [37], vector <string>& phonemeLu, int &compteurx, int &compteury, int TIME, vector <int>& selectionClavier)
{
	int sauvegardeTouche;
	int endroitScroll;
	cout << "appuie" << endl;
	
	selectionClavier.clear();

	if(toucheClavierSelectionnee < 36)
	{		
		if(lock[toucheClavierSelectionnee]!=0)
		{
			while(lock[toucheClavierSelectionnee] != 0) // pour trouver la première touche de la suite
			{
				toucheClavierSelectionnee = toucheClavierSelectionnee-1;
				cout<<"toucheSerie"<<toucheClavierSelectionnee<<endl;
			}
		}

		sauvegardeTouche = selectionTouche[toucheClavierSelectionnee];//aller chercher quelle image de touche est rendue à l'endroit appuyé
		selectionPhoneme.push_back(sauvegardeTouche);//stockage du numero de ligne contenant le chemin image pour le tableau textureTableau
		ecrit.push_back(phonemeLu[toucheClavierSelectionnee]);//aller chercher la lettre associée à l'endroit appuyée
		selectionClavier.push_back(sauvegardeTouche);//sauvegarder le numero pour les bouches temporaires
	
		ofstream fichier("fichierSon.pho", ios::app);
		if(fichier.is_open())
		{
			fichier<<phonemeLu[toucheClavierSelectionnee]<<" "<<TIME<<endl;
		}
			fichier.close();
		
		ofstream fichierTouche("fichierSonTouche.pho");
		if(fichierTouche.is_open())
		{
			fichierTouche<<phonemeLu[toucheClavierSelectionnee]<<" "<<TIME<<endl;
		}
			fichierTouche.close();

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

		else
		{
			refreshTableau(selectionPhoneme, compteurx, compteury);
		}

		while(lock[(toucheClavierSelectionnee + 1)] != 0) // ajouter une par une les touches tant qu’elles sont liées
		{
			cout<<"liaison verifier"<<(toucheClavierSelectionnee + 1)<<endl;
			toucheClavierSelectionnee = toucheClavierSelectionnee+1;
								
			sauvegardeTouche = selectionTouche[toucheClavierSelectionnee];
			
			ofstream fichier("fichierSon.pho", ios::app);//changer chemin une fois dossier save creer
			if(fichier.is_open())
			{
				fichier<<phonemeLu[toucheClavierSelectionnee]<<" "<<TIME<<endl;
			}
				fichier.close();
			
			ofstream fichierTouche("fichierSonTouche.pho", ios::app);
			if(fichierTouche.is_open())
			{
				fichierTouche<<phonemeLu[toucheClavierSelectionnee]<<" "<<TIME<<endl;
			}
				fichierTouche.close();

			ecrit.push_back(phonemeLu[toucheClavierSelectionnee]);
			selectionPhoneme.push_back(sauvegardeTouche);
			selectionClavier.push_back(sauvegardeTouche);
			cout<<"tableau selectionPhoneme"<<selectionPhoneme.size()<<endl;

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
	toucheClavierSelectionnee = 0;
	appuie = 0;
}


void dragTouche(int toucheClavierSelectionnee, vector <int>& selectionTouche, bool lock [37], vector <string>& phonemeLu, int positionTouches[79][2], SDL_Event event,
				int emplacementSourisX, int emplacementSourisY, double ratioY, double ratioX)
{	
	string phonemeSaveTemp;
	double resultat;
	double hypo;
	int verificationTouche;
	int toucheArrivee;
	int sauvegardeTouche;
						
	if(toucheClavierSelectionnee < 36)
	{	
		phonemeSaveTemp = phonemeLu[toucheClavierSelectionnee];
		sauvegardeTouche = selectionTouche[toucheClavierSelectionnee];
						
		if(emplacementSourisX < (1550*ratioX) && emplacementSourisX > (620*ratioX) && emplacementSourisY < (930*ratioY) && emplacementSourisY > (550*ratioY))
		{
			resultat = 100;
			for(verificationTouche = 0; verificationTouche < 36; verificationTouche++)
			{
				hypo = sqrt(pow((emplacementSourisX - (positionTouches[verificationTouche][0])-(54*ratioX)), 2) + pow((emplacementSourisY - positionTouches[verificationTouche][1]-(40*ratioY)), 2));
				if(hypo < resultat)
				{
					resultat = hypo;
					cout<<resultat<<endl;
					toucheArrivee = verificationTouche;
					cout<<"touche"<<toucheArrivee<<endl;
				}
			}
			selectionTouche[toucheClavierSelectionnee] = selectionTouche[toucheArrivee];
			selectionTouche[toucheArrivee] = sauvegardeTouche;
			phonemeLu[toucheClavierSelectionnee] = phonemeLu[toucheArrivee];
			phonemeLu[toucheArrivee] = phonemeSaveTemp;
		}
		toucheArrivee = 0;
		verificationTouche = 0;
	}

	else if(toucheClavierSelectionnee == 36)
	{					
		resultat = 100;
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
		
		if(toucheClavierSelectionnee != 36 && toucheClavierSelectionnee != 45 && toucheClavierSelectionnee!= 54 && toucheClavierSelectionnee!= 63)
		{
			cout<<"emplacement lock "<<(toucheClavierSelectionnee-36)<<endl;
			lock[(toucheClavierSelectionnee - 36)] = 1;
			cout<<"lock"<<toucheClavierSelectionnee<<lock[(toucheClavierSelectionnee - 36)]<<endl;
		}
	}
}


void suppIndiv(double ratioY, double ratioX, int& scroll, int emplacementSourisX, int emplacementSourisY, vector <int>& selectionPhoneme,
			   vector <string>& ecrit, int TIME)
{
	double valeurTemporaire;
	double hypoTemp;
	int emplacementsVerifies;
	int rectangle;
	int selectionPho =-1;
	int compteurx = 0;
	int compteury = 1;
	int emplacementX;
	int emplacementY;
	int valeur;
	int compare;
	int blob;
	
	compare = ecrit.size() - scroll;
	cout<<"compare "<<compare<<endl;

	for(emplacementsVerifies = 0; emplacementsVerifies < compare; emplacementsVerifies++)
	{
		compteurx++;

		if(compteurx == 10)
		{
			compteury++;
			compteurx = 1;
		}

		emplacementX = (805*ratioX) + (compteurx * (65*ratioX));
		emplacementY = (70*ratioY) + (compteury * (95*ratioY));

		hypoTemp = sqrt(pow((emplacementSourisX - emplacementX), 2) + pow((emplacementSourisY - emplacementY), 2));
		valeurTemporaire = (30*ratioX);
		cout<<"hypo temp supp "<<hypoTemp<<endl;

		if(hypoTemp < valeurTemporaire)
		{
			valeurTemporaire = hypoTemp;
			rectangle = emplacementsVerifies;
			selectionPho = rectangle+scroll;
			cout<<"selection pho "<<selectionPho<<endl;
		}
	}
	
	if(selectionPho > -1)
	{
		if(selectionPho < ecrit.size())
		{
			selectionPhoneme.erase(selectionPhoneme.begin() + selectionPho);
			ecrit.erase(ecrit.begin() + selectionPho);

			valeur = (ecrit.size()-scroll)-27;

			if(valeur<0)
			{
				if(scroll!=0)
				{
					scroll=scroll-9;
				}
			}
		}
		
		ofstream fichier("fichierSon.pho");
		if(fichier.is_open())
		{
			for(blob = 0; blob < ecrit.size(); blob++)
			{
				fichier<<ecrit[blob]<<" "<<TIME<<endl;
			}
		}
			fichier.close();
	}
}