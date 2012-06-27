// PGCD.cpp
#include "PGCD.h"


void PGCD::process(){
   done = false; // valeur par defaut
   
   //mise a jour des registres d'entree (sequentiel):
   if (start) {
      reg_x = x.read();
      reg_y = y.read();
   } else {
      reg_x = var_diff;
      reg_y = var_min;
   }

   if (reg_x==0 || reg_y==0) {
      pgcd = 0;
      done = true;
   } else {
      // calcul des var_max/var_minimums (combinatoire):
      var_max =  (reg_x > reg_y)? reg_x : reg_y;
      var_min = !(reg_x > reg_y)? reg_x : reg_y; //permet d'eviter d'instancier 2 comparateurs var_differents ;-)

      // soutraction (combinatoire):
      var_diff = var_max - var_min;
            
      // calcul des sorties (combinatoire):
      if (var_diff == 0) {
         pgcd = reg_y; // egal a la valeur precedente de var_diff c-a-d le pgcd !
         done = true;
      } else if (var_diff == 1) {
         pgcd = 1;
         done = true;
      } else {
         pgcd = reg_y; // on le fait sortir meme si on n'est pas pret pour eviter de creer un registre
         done = false;
      }
   }
}
/////////////////////////////////////////////////
/*
void PGCD::process(){
   switch (state) {
      case 0 :
         // wait
         break;
         
      case 1 :
         // compute
         break;
         
      case 2 :
         // done
         break;
   }
}
*/


