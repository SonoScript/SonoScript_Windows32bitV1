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
#include <vector> //tableau à grandeur variable
#include <cmath> 
#include <map>// tableaux associatifs

#include <windows.h>
#include <mmsystem.h>

#include "saveEcrit.h"

using namespace std;


void jouerSon(int numeroVoix)
{
	const char* voix[] = 
	{
	"mbrola mbrola/fr2/fr2 fichierSon.pho fichierSon.wav",//voix meuf 1
	"mbrola mbrola/fr1/fr1 fichierSon.pho fichierSon.wav",//voix homme aigu
	"mbrola mbrola/fr4/fr4 fichierSon.pho fichierSon.wav",//voix meuf 2 femme
	"mbrola mbrola/fr3/fr3 fichierSon.pho fichierSon.wav",//voix homme grave
	};
	
	system((voix[numeroVoix]));
	PlaySound("fichierSon.wav", GetModuleHandle(NULL), SND_FILENAME);
}


void jouerTouche(int numeroVoix)
{
	const char* voixTouche[] = 
	{
	"mbrola mbrola/fr2/fr2 fichierSonTouche.pho fichierSonTouche.wav",//voix meuf 1
	"mbrola mbrola/fr1/fr1 fichierSonTouche.pho fichierSonTouche.wav",//voix homme aigu
	"mbrola mbrola/fr4/fr4 fichierSonTouche.pho fichierSonTouche.wav",//voix meuf 2 femme
	"mbrola mbrola/fr3/fr3 fichierSonTouche.pho fichierSonTouche.wav",//voix homme grave
	};
	
	system((voixTouche[numeroVoix]));
	PlaySound("fichierSonTouche.wav", GetModuleHandle(NULL), SND_FILENAME);
}


void changeVoix(int emplacementSourisX, int emplacementSourisY, int& numeroVoix, double ratioX, double ratioY)
{
	double resultat;
	double hypo;
	int verificationVoix;
	int pos1 = (907*ratioX);
	int pos2 = (1012*ratioX);
	int pos3 = (1212*ratioX);
	int pos4 = (1412*ratioX);

	int positionVoixX[] = {pos1,pos2,pos3,pos4};
	int positionVoixY = (800*ratioY);

	resultat = 150;
	for(verificationVoix = 0; verificationVoix < 4; verificationVoix++)
	{
		hypo = sqrt(pow((emplacementSourisX - positionVoixX[verificationVoix]), 2) + pow((emplacementSourisY - positionVoixY), 2));
		if(hypo < resultat)
		{
			resultat = hypo;
			cout<<resultat<<endl;
			numeroVoix = verificationVoix;
			cout<<"Voix"<<numeroVoix<<endl;
		}
	}
}