# Robot-Planning

NUME, PRENUME: Iuga, Florin-Eugen
GRUPA, SERIA: 312CA

DATA INCEPERII TEMEI: 22-03-2018
DATA FINALIZARII TEMEI: 25-03-2018

PROBLEMELE INTAMPINATE:
	-legat de coding style, nu am inteles de ce 
	referintele date ca parametri functiilor rezultau
	intr-o eroare de coding style
	-am avut o mica problema cu memory leaks, dar asta dintr-o
	greseala de-a mea, pe care am sesizat-o relativ repede
	-alte probleme majore nu am intampinat in rezolvarea temei

ALGORITMUL UTILIZAT:
	-am inceput prin implementarea structurilor de date stiva,
	respectiv coada, apoi am mai facut o clasa pentru comenzi numita
	Comanda.h, inca o clasa Robot.h in care am implementat functia 
	de printare a comenzilor pentru fiecare robot(printCommands()),
	respectiv functia care intoarce numarul de cutii al fiecarui robot.
	-in continuare, am optat pentru implementarea celorlalte functii in
	fisierul cod sursa principal, tema1.cpp. Astfel, in functia main() 
	am citit comenzile si le-am interpretat pe fiecare in parte in
	functie de parametri primiti(ex: id,x,y,priority etc.). In
	acest sens, la intalnirea unei anumite comenzi apelam functia 
	asociata.
	-de mentionat este faptul ca am utilizat o coada pentru fiecare robot 
	si 2 stive: una pentru comenzile de tip ADD si EXECUTE, care va avea
        un rol esential in functia undo(), respectiv una pentru comenzile
        EXECUTATE, pentru a avea acces rapid la ultima comanda executata,
	restul comenzilor nefiind implicate in cele 2 stive.
	
	
	->Functia execute(): 
	   -fac un pointer la prima comanda din coada robotului respectiv
	   -verific daca nu cumva coada robotului care ma intereseaza
	    este goala sau nu, in caz afirmativ afisand mesajul corespunzator.
	   -in caz contrar, verific tipul comenzii, iar in continuare fac
	    prelucrarile necesare asupra cutiilor si a timpului;
	    la final, elimin din coada robotului respectiv comanda si
	    adaug "EXECUTE" in stiva de comenzi date. 
	    (vezi comentariile din cod pentru mai multe detalii).

	->Functia undo():
	   -verific daca stiva de comenzi date este goala, daca da,
	    atunci afisez mesajul corespunzator, daca nu,verific tipul comenzii
	   -daca tipul comenzii este execute, obtin valorile 
	    ultimei comenzi executate, adaugand din nou in coada robotului
	    corespunzator comanda respectiva; mai apoi, comanda respectiva este
	    scoasa din stiva de comenzi executate.
	   -daca comanda este de tip ADD o elimin din coada
	    in functie de priority.
	   -scot comanda din stiva de comenzi date.
	   (vezi comentariile din cod pentru mai multe detalii)

	->Functia lastExecutedCommand():
	   -ma folosesc doar de stiva de comenzi executate; afisez
	    comanda daca stiva nu este goala.

	->Functia howMuchTime():
	   -am un contor pentru timp in main(), care se incrementeaza la 
	    citirea fiecarei comenzi si reprezinta timpul curent.
	   -afisez timpul ultimei comenzi executate
	   -timpul a fost introdus in functia main(), atunci cand adaug in
	    coada, reprezentand timpul curent.
	   -timpul respectiv a fost prelucrat in functia execute() si undo(), 
	    in execute() am scazut din timpul curent timpul din comanda din 
	    coada robotului, mai exact prima, iar in undo() resetez timpul
	    cu timpul curent.

	->Functia printCommands():
	   -am implementat-o in Robot.h pentru usurinta
	   -ma pozitionez la inceputul cozii cu un pointer si 
	    afisez, rand pe rand, comenzile din coada.

	->Functia getNrBoxes():
	   -implementata in Robot.h, intoarce efectiv numarul de 
	    cutii al robotului.

COMPLEXITATEA TEMEI:
	-consider ca a fost o tema relativ usoara in ceea ce priveste
	 algoritmul, insa avand un enunt destul de complex, plin de 
	 detalii si cazuri particulare, uneori ambiguu sau greu de inteles.

ALTE PRECIZARI:
	-tema aceasta m-a ajutat destul de mult sa inteleg mai bine
	 structurile de date stiva si coada, precum si implementarea lor.
