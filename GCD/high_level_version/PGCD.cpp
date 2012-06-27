/*
 * ramSync.cpp
 *
 *  Created on: 16 mars 2010
 *      Author: remi
 */

#include "PGCD.h"

void PGCD::calcul()
    {//methode qui calcul le pgcdOut: credits: http://www.liafa.jussieu.fr/~gastin/DEUG/Programmes1.html
    //    cout << "PGCD Calcul \n";
    //	cout << "start: " << start.read() << "done: " << done << "pgcdReady "<< pgcdReady << " " << endl;
    //cas ou il ne faut pas travailler :
    if (start.read() != 1)
	{//cas ou il ne faut pas calculer
	return;
	}
    else
	{
	//note : pour plus de rapidité a l'execution , preferer la methode par soustraction successives
	int n, m, r;
	n = x.read();//lecture des variables d'entrée
	m = y.read();

	if (n < 0 || m < 0 || (n == 0 && m == 0))
	    cout
		    << "Vous n'avez pas donné deux entiers positifs non tous deux nuls.\n";
	else
	    {

	    while (m != 0)
		{
		r = n % m;
		n = m;
		m = r;
		}

	    }
	//le resultat du pgcdOut est dans n

	pgcdTemp = n;
	pgcdReady = true;
	return;

	}
    }

void PGCD::ecriture()
    {
    //    cout << "PGCD ecriture \n";
    //    	cout << "start: " << start.read() << "done: " << done << "pgcdReady "<< pgcdReady << " " << endl;
    //cas ou il ne faut pas ecrire:
    if (pgcdReady == false)
	{
	return;
	}
    else
	{//on ecrit sur la sortie pendant un cycle
	if (done.read() == false)//cas ou on est pas en train d'ecrire
	    {//on ecrit pour un cycle
	    pgcdReady = false;
	    done.write(true);
	    pgcdOut.write(pgcdTemp);
	    }
	else
	    {//on arrete d'ecrire pour un cycle
	    done.write(false);
	    pgcdOut.write(0);
	    pgcdReady = false;
	    }
	}

    }

int PGCD::pgcd(int a, int b){
    // credit source : http://www.siteduzero.com/forum-83-283272-p1-calculateur-de-pgcd-par-wowfan10893.html#r2581594
    while (a && (b %= a) && (a %= b));
    return a + b;
}

