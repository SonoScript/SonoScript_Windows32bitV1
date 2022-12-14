FFFFFFF   RRRRR         1
F         R    R      1 1
F         R     R   1   1
F         R    R        1
FFFFF     RRRR          1
F         R   R         1
F         R    R        1
F         R     R       1
F         R      R   1111111 release 2.050

--------------------------------------------------------------
Table of Contents
--------------------------------------------------------------

1.0 License
2.0 A brief description of the FR1 database
3.0 Distribution
4.0 Installation, and tests
5.0 Acknowledgments

--------------------------------------------------------------
1.0 License
--------------------------------------------------------------

This    database  is being    provided  to  "You",   the licensee,  by
Faculte Polytechnique de  Mons - Thierry Dutoit,   the "Author of  the
Database", under the following license.   

By obtaining,  using and/or copying  this database, you agree that you
have read, understood, and will comply with these terms and conditions:

Terms and conditions on the use of FR1
--------------------------------------

Permission is  granted to use   this database for synthesizing  speech
with and only with the  Mbrola program made  available from the MBROLA
project www homepage :  
   https://github.com/numediart/MBROLA/
   
following the terms and conditions on the use of the Mbrola program.

Terms and conditions for the distribution of FR1
------------------------------------------------

The distribution  of this database is submitted  to the same terms and
conditions as the distribution of   the Mbrola program. In   addition,
this database may  not be sold  or incorporated into any product which
is sold without prior permission from the Author of the Database. 

When no charge  is made, this database  may be copied  and distributed
freely, provided that this notice is copied and distributed with it.

Disclaimer
----------

THIS DATABASE CARRIES   NO WARRANTY, EXPRESSED  OR  IMPLIED.  THE USER
ASSUMES ALL  RISKS,  KNOWN  OR UNKNOWN,   DIRECT  OR INDIRECT,   WHICH 
INVOLVE  THIS DATABASE  IN  ANY  WAY. IN   PARTICULAR, THE AUTHOR   OF 
THE DATABASE DOES  NOT  TAKE ANY COMMITMENT IN   VIEW OF ANY  POSSIBLE
THIRD PARTY RIGHTS.

--------------------------------------------------------------
2.0 A brief description of FR1
--------------------------------------------------------------
FR1-BE 2.00b  release  (alias SAMPA  release )   is a  French  diphone
database  provided   in the   context  of   the  MBROLA   project (see
https://github.com/numediart/MBROLA/). 

It provides  a French male voice  (the  author's one, actually)  to be
used with the MBROLA program. 

Input  files  use  the  SAMPA (SAM   Phonetic   Alphabet)  notation as
recommended  by the EEC-SAM  Project. Here  is  a  list of the  French
phonemes it accounts for, with examples. 

(NB : the table   below is encoded as  ASCII  ISO8859-1; use an  ASCII 
editor to see it correctly )

SAMPA	EXAMPLES
i	idiot, ami
e	??mu, ??t??
E	perdu, maison
a	alarme, patte
A	b??ton, patte
O	obstacle, corps
o	auditeur, beau
u	coupable, loup
y	punir, ??lu
2	creuser, deux
9	malheureux, peur
@	petite, fortement
e~	peinture, matin
a~	vantardise, temps
o~	rondeur, bon
9~	lundi, brun
j	pi??tiner, choyer
w	quoi, fouine
H	huile, nuage
p	patte, repas, cap
t	t??te, net
k	carte, ??caille, bec
b	b??te, habile, robe
d	dire, rondeur, chaud
g	gauche, ??gal, bague
f	feu, affiche, chef
s	soeur, assez, passe
S	chanter, machine, poche
v	vent, inventer, r??ve
z	z??ro, raisonner, rose
Z	jardin, manger, pi??ge
l	long, ??lire, bal
R	rond, charriot, sentir
m	madame, aimer, pomme
n	nous, punir, bonne
N	jumping, smoking
_	(silence marker)

Limitations:
-----------
Notice that  SAMPA 'h' (halte,hop) is not  accepted by MBROLA and that
SAMPA 'J'  (agneau, peigner, r??gne) should be  entered as two separate
phonemes : 'n' and 'y'. 

Note   also  that not   all diphones   are possible   in  French. Some
"impossible" ones will trigger a replacement one:  

9-a,9-@,9-i,9-O,9-y,9-o,9-u,9-e,9-E,9-9
9-2,9-a~,9-o~,9-e~,9-9~,9-k,9-S,9-d,9-j,9-m
9-s,9-t,9-z,9-ng,9-H,9-w,9-_ 
trigger their @-* equivalent. 

N-N (rather unlikely, isn't it ?) will trigger N-g

H-@,H-y,H-u,H-b,H-k,H-S,H-d,H-f,H-g,H-l,H-m,
H-n,H-p,H-R,H-s,H-t,H-v,H-z,H-N,H-H,H-w,H-j,
H-_
will trigger y-*

Of course  those units may  not have the quality   you request, but we
recommend not generating them from the start, in your TTS system. They
potentially imply wrong vocalic hamonizations  for 9-* and wrong rules
with H-*. 

--------------------------------------------------------------
3.0 Distribution
--------------------------------------------------------------

This distribution of mbrola contains the following files : 

   fr1      : the database itself
   fr1.txt  : This file
    
and a number of example .PHO files : 

   bonjour.pho            "bonjour"
   ceserait.pho           "ce serait certes une invention considerable ...
	claire                 "a la claire fontaine, m'en allant promener ...
   coup.pho					  "qu'est-ce t'as la ...
   jaiete.pho             "j'ai ete concu dans les laboratoires de la ...
   mavoix.pho				  "ma voix est synthetise grace a ....
   nouspouv.pho           "nous pouvons definir le son comme un coup ...
   tagada.pho             "tagada tagada, tsoin tsoin"
   trenet.pho             "je chante, je chante soir et matin ...

The file mbroli.ini, when used with the Mbroli  pho play under windows
platforms automatically   set the database to  fr1.  It means  you can
double click on any of the .pho file and listen to the voice.

Additional  languages and  voices,  as well as   other example command
files,   are or  will  be  available  in  the  context of  the  MBROLA
project. Please consult the MBROLA project homepage :  
   https://github.com/numediart/MBROLA/

Registered users will automatically be notified of the availability of
new  databases.   To    freely register, simply   send   an   email to
mbrola-interest-request@tcts.fpms.ac.be  with  the word 'subscribe' in
the message title. 

--------------------------------------------------------------
4.0 Installation and Tests
--------------------------------------------------------------

If you have  not copied the  MBROLA  software yet, please  consult the
MBROLA project homepage and get it. 

Copy fr1.zip into the mbrola directory and unzip it : 

   unzip fr1.zip (or pkunzip on PC/DOS)
   (don't forget to delete the .zip file when this is done)

Try 

   mbrola fr1/fr1 TEST/bonjour.pho bonjour.wav

to create  a sound file for the  word  'bonjour'. In this  example the
audio file follows the RIFF Wav format. But depending on the extension
bonjour.au, bonjour.aif, or  bonjour.raw you   can obtain other   file
formats. Listen  to it  with your  favorite sound  editor, and try the
other command files  (*.pho) to have a better  idea of the  quality of
speech you can synthesize with the MBROLA technique. 

On  Unix systems you can pipe  the audio ouput  to the sound player as
on a HP : mbrola fr1 bonjour.pho - | splayer -srate 16000 -l16

Also refer to  the readme.txt file  provided with the mbrola  software
for using it.  

--------------------------------------------------------------
5.0 Acknowledgments
--------------------------------------------------------------
I would  like to thank   Vincent Pagel for his   help  in building  an
efficient version of this database.

--------------------------------------------------------------

Dr Thierry Dutoit

Faculte Polytechnique de Mons, TCTS Lab,
31, bvd Dolez, B-7000 Mons, Belgium.
tel   : /32/65/374133
fax   : /32/65/374129
e-mail: mbrola@tcts.fpms.ac.be, for general information, 
questions on the installation of software and databases.
