/*
 * PGCDTest.cpp
 *
 *  Created on: 16 mars 2010
 *      Author: remi
 */

#include "systemc.h"
#include "PGCD.h"

void next_cycle(sc_signal<bool> &signal_clk);

int sc_main(int argc, char * argv[])
    {

    //les entrées du modèle
    sc_signal<bool> clk;//declaration de l'horloge
    sc_signal<unsigned char> x;
    sc_signal<unsigned char> y;
    sc_signal<unsigned char> pgcdOut;
    sc_signal<bool> start;
    sc_signal<bool> done;

    sc_trace_file *my_trace_file;//creation du fichier et de trace et ajout des traces a afficher
    my_trace_file = sc_create_vcd_trace_file("PGCD_traces");

    sc_trace(my_trace_file, clk, "clk");
    sc_trace(my_trace_file, start, "start");
    sc_trace(my_trace_file, x, "x");
    sc_trace(my_trace_file, y, "y");
    sc_trace(my_trace_file, done, "done");
    sc_trace(my_trace_file, pgcdOut, "pgcdOut");

    PGCD PGCD("PGCD");//creation du module et branchement des files
    PGCD.clk(clk);
    PGCD.x(x);
    PGCD.y(y);
    PGCD.pgcdOut(pgcdOut);
    PGCD.start(start);
    PGCD.done(done);

    sc_trace(my_trace_file, PGCD.pgcdReady, "pgcReady");

    //on initialise les variables
    x = 0;
    y = 0;
    pgcdOut = 0;
    start = 0;
    done = 0;
    next_cycle(clk);

    //on va mettre quelque chose d'interessant a l'entrée
    /*//tests basiques
     x.write(230);
     y.write(90);
     next_cycle(clk);
     start.write(1);
     next_cycle(clk);//cycle lecture calcul
     start.write(0);
     next_cycle(clk);//cycle calcul et debut affichage
     //affichage de debugage
     cout << " voci le pgcd: " << pgcdOut.read() << endl;
     next_cycle(clk);//cycle fin affichage


     next_cycle(clk);
     for (int i = 0; i < 40; i++)
     next_cycle(clk);

     x.write(34);
     y.write(22);
     next_cycle(clk);
     start.write(1);
     next_cycle(clk);//cycle lecture calcul
     start.write(0);
     next_cycle(clk);//cycle calcul et debut affichage
     //affichage de debugage
     cout << " voci le pgcd: " << pgcdOut.read() << endl;
     next_cycle(clk);//cycle fin affichage


     next_cycle(clk);
     */

    //test exhaustifs
    for (int i = 0; i < CHAR_MAX; i++)//on fait tous les pgcd
	{
	for (int j = 0; j < CHAR_MAX; j++)
	    {
	    next_cycle(clk);
	    x.write(i);
	    y.write(j);
	    next_cycle(clk);
	    start.write(1);
	    next_cycle(clk);//cycle lecture calcul
	    start.write(0);
	    int resultatBon = PGCD.pgcd(i, j);
	    int resultatPerso = pgcdOut.read();
	    next_cycle(clk);//cycle calcul et debut affichage
	    //affichage en cas de difference avec la method ed reference

	    if (resultatPerso != resultatBon)
		{
		cout << "Probleme dans le calcul du pgcd, on trouve: "
			<< resultatPerso << " au lieu de : " << resultatBon
			<< endl;
		}
	    else
		cout << " calcul réussi " << endl;

	    for (int toto = 0; toto < 6; toto++)
		next_cycle(clk);//cycle fin affichage
	    }
	}

    return EXIT_SUCCESS;

    }
void next_cycle(sc_signal<bool> &signal_clk)
    {
    signal_clk = false;
    sc_start(1);
    signal_clk = true;
    sc_start(1);
    }
