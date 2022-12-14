FFFFFFF   RRRRR       333333
F         R    R     3      3
F         R     R           3
F         R    R            3
FFFFF     RRRR        333333
F         R   R             3
F         R    R            3
F         R     R    3      3 
F         R      R    333333  release 2.060

--------------------------------------------------------------
Table of Contents
--------------------------------------------------------------

1.0 A brief description of the FR3 database
2.0 Distribution
3.0 Installation, and tests
4.0 Author

--------------------------------------------------------------
1.0 A brief description of FR3
--------------------------------------------------------------

FR3 2.060 release is a French diphone database provided in the context
of the MBROLA project see: https://github.com/numediart/MBROLA/

It  provides  a French  female   voice  to  be  used  with the  MBROLA
program. The central  pitch of the database  is 110Hz, and the nominal
sampling rate is 16000Hz. 

Input files    use the SAMPA  (SAM    Phonetic Alphabet)  notation  as
recommended by  the EEC-SAM  Project.  Here is a  list  of the  French
phonemes it accounts for, with examples. 

(NB :  the  table below  is encoded  as ASCII ISO8859-1;  use an ASCII
editor to see it correctly ) 

SAMPA	EXAMPLES
i	idiot, ami
e	ému, été
E	perdu, maison
a	alarme, patte
O	obstacle, corps
o	auditeur, beau
u	coupable, loup
y	punir, élu
2	creuser, deux
9	malheureux, peur
@	petite, fortement
e~	peinture, matin
a~	vantardise, temps
o~	rondeur, bon
9~	lundi, brun
j	piétiner, choyer
w	quoi, fouine
H	huile, nuage
p	patte, repas, cap
t	tête, net
k	carte, écaille, bec
b	bête, habile, robe
d	dire, rondeur, chaud
g	gauche, égal, bague
f	feu, affiche, chef
s	soeur, assez, passe
S	chanter, machine, poche
v	vent, inventer, rêve
z	zéro, raisonner, rose
Z	jardin, manger, piège
l	long, élire, bal
R	rond, charriot, sentir
m	madame, aimer, pomme
n	nous, punir, bonne
N  ping, pong
_	(silence marker)

Limitations:
-----------
Notice that SAMPA 'h' (halte,hop) is not defined.

SAMPA 'J'  (agneau, peigner, règne) should  be entered as two separate
phonemes : 'n' and 'j'.

--------------------------------------------------------------
2.0 Distribution
--------------------------------------------------------------

This distribution of mbrola contains the following files :

   fr3        : the database itself
   fr3.txt    : This file
   license.txt: must read before using the database
    
and a number of example .PHO files : 

bonjour.pho      greetings
levai.pho        Long press review
nouspouvons.pho  Plato, 300 before JC
ceserait.pho     Leonard Euler
jaiete.pho       Made in Belgium
mavoix.pho       mbrola
kundera.pho      Milan Kundera "L'insoutenable legereté de l'être"
claire.pho    -> popular song, A la claire fontaine
trenet.pho    -> song of Charles Trenet (Je chante soir et matin)
tagada.pho       that's all folks

Additional languages  and  voices, as  well as other   example command
files,  are or   will  be available in   the   context of  the  MBROLA
project. Please consult the MBROLA project homepage : 
   https://github.com/numediart/MBROLA/

Registered users will automatically be notified of the availability of
new   databases.  To   freely  register,  simply   send an   email  to
mbrola-interest-request@tcts.fpms.ac.be  with the word 'subscribe'  in
the message title.

--------------------------------------------------------------
3.0 Installation and Tests
--------------------------------------------------------------

If you  have not copied  the MBROLA software   yet, please consult the
MBROLA project homepage and get it.

Copy fr3.zip into the mbrola directory and unzip it : 

   unzip fr3.zip (or pkunzip on PC/DOS)
   (don't forget to delete the .zip file when this is done)

On PC-Windows register fr3 with the Wizard in the control panel.

On unix platforms, try:

   mbrola fr3 TEST/bonjour.pho bonjour.wav

to create a sound  file for the word  'bonjour'.  In this  example the
audio file follows the RIFF Wav format. But depending on the extension
bonjour.au,  bonjour.aif, or   bonjour.raw you can  obtain other  file
formats. Listen to  it with your  favorite  sound editor, and  try the
other command files (*.pho)  to have a better idea  of the quality  of
speech you can synthesize with the MBROLA technique.

On Unix systems you can pipe the audio ouput to the sound player as on
a HP : mbrola fr3 TEST/bonjour.pho - | splayer -srate 16000 -l16 

Also refer  to the readme.txt file  provided with  the mbrola software
for using it.

--------------------------------------------------------------
4.0 Author
--------------------------------------------------------------

This  database was recorded by  Vincent  Pagel for Babel Technologies
SA.  For  questions   concerning   the   database   itself    contact
pagel@babeltech.com 

Contact mbrola@tcts.fpms.ac.be,  for general information, questions on
the installation of software and databases.
