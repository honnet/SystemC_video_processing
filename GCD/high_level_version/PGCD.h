/*
 * ramSync.h
 *
 *  Created on: 16 mars 2010
 *      Author: remi
 */

#include "systemc.h"

SC_MODULE(PGCD){

sc_in<bool> clk;
sc_in<unsigned char> x;
sc_in<unsigned char> y;
sc_out<unsigned char> pgcdOut;
sc_in<bool> start;
sc_out<bool> done;


void calcul();//processus quui va effectuer le calcul
void ecriture();//ecriture sur la sortie du resultat
int pgcd(int , int );
public :
 unsigned char pgcdTemp;//variable qui va stocker le pgcdOut
 bool pgcdReady;


SC_CTOR(PGCD)
    {
    pgcdReady=false;
    SC_METHOD(calcul);
    sensitive << clk;

    SC_METHOD(ecriture);
    sensitive << clk;
    }
};

