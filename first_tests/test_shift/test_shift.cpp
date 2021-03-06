
//#include "systemc.h"
#include "shift.h"

void next_cycle (sc_signal<bool> &signal_clk);


/*
main et sc_main
    La fonction main() est déjà définie par la bibliothèque SystemC.
    Elle appelle la fonction sc_main, fournie par l'utilisateur, qui est le point d'entrée du code utilisateur.
    sc_main a le même prototype que main : int sc_main(int argc, char *argv[]);
    Cette fonction a pour rôle d'instancier tous les modules et signaux nécessaires, et de lancer la simulation.
*/
int sc_main(int argc, char *argv[])
{
    int i;
    
    /*
Déclaration des signaux
    Le registre à décalage possède trois ports, trois signaux sont donc nécessaires à son test.
    On instancie donc trois signaux, de type bool (1 bit, en logique 2 valuée).
    L'horloge a aussi un type sc_signal<bool>. C'est nous qui nous chargerons de la faire bouger.
    Il existe en SystemC une façon plus propre de générer des horloges, en passant par le type sc_clock.
    C'est le moteur SystemC qui se charge alors de générer les transitions des objets sc_clock.
    */
    sc_signal<bool> clk;
    sc_signal<bool> in;
    sc_signal<bool> out;

/*
Trace des signaux
    SystemC dispose de fonction de traçage de signaux au format  VCD (Value Change Dump, visible par gtkwave, ... ).
    SystemC permet de tracer les variables scalaires, les vecteurs de bits, les signaux et certains ports.
    Pour les objets ne disposant pas de fonctions de traçage (structures, objets, ...) il est toujours possible de définir ses
      propres fonctions de traçage, qui consistent généralement à tracer les membres de l'objets. Seuls les objets existant pendant
      toute la simulation peuvent être tracés. En d'autres termes, les variables locales ne sont pas traçables.
    Avant de tracer un objet, il faut ouvrir un fichier de traces. C'est le but de la fonction sc_create_vcd_trace_file().
    Puis on enregistre tous les objets à tracer à l'aide la fonction sc_trace, prenant en argument une référence ou un pointeur
      vers l'objet à tracer et un nom associé qui sera utilisé dans la génération des chronogrammes.
    Il est impératif, sous peine de crash, de fermer le fichier de trace avant de retourner de sc_main().
    Plusieurs fichiers de traces peuvent être générés en même temps, et un même signal peut être tracé dans plusieurs fichiers à la fois.
*/
    sc_trace_file *my_trace_file;
    my_trace_file = sc_create_vcd_trace_file ("shift_trace");
    sc_trace(my_trace_file, clk, "clk");
    sc_trace(my_trace_file, in, "in");
    sc_trace(my_trace_file, out, "out");
                                                                              // sc_trace(my_trace_file, shifter->regs, "regs"); // ???????????????????

/*
Instanciation et connexion du module à tester
    L'instanciation d'un module se fait comme l'instanciation de n'importe quel objet C++.
    On peut le créer de façon statique comme ici (il prend comme argument celui attendu par son constructeur, c-à-d un nom), ou de façon dynamique à 
      l'aide de new (new est l'équivalent de malloc en C++, il permet d'allouer dynamiquement un objet en passant des arguments à son constructeur).
    La connexion est faite ici de façon explicite : chaque port et relié explicitement à un signal : shifter.din(in);
    Il est aussi possible, comme en Verilog ou VHDL, d'utiliser une connexion par position (implicite).
*/
    shifter shifter("reg_decalage");
    shifter.clk(clk);
    shifter.din(in);
    shifter.dout(out);
                                                                              //    connexion par position : shifter(clk, in, out); ???????????????????

/*
Lancement de la simulation
    Une simulation se lance généralement par sc_start, et s'arrête par sc_stop. Comme aucun signal n'est géré automatiquement dans ce système-ci
      (pas de sc_clock), il faut gérer la simulation manuellement.
    La simulation peut être initialisée par l'appel de la fonction sc_start(SC_ZERO_TIME), qui se charge alors de faire toutes les initialisations 
      du scheduler SystemC, et d'exécuter une fois tous les processus qui ne sont pas marqués dont_initialize().
    Mais cet appel n'est pas obligatoire : il est fait automatiquement pas le scheduler lors du lancement de la simulation s'il n'a pas déjà été fait.
    Remarque : le fonction sc_initialize() est obsolète, et remplacée par sc_start(SC_ZERO_TIME).
    Les signaux sont alors positionnés à la main, par une simple affectation (in = 0).
    Puis le temps est avancé manuellement par la fonction qu'on a appelée next_cycle(), dont le code se trouve en bas du listing :
      cette fonction positionne manuellement la ligne d'horloge, et fait à chaque fois avancer la simulation d'une unité de temps (1ns)
      grâce à la fonction sc_start().
*/
    in = 0;
    next_cycle(clk);
    in = 1;
    next_cycle(clk); next_cycle(clk);
    in = 0;
    next_cycle(clk);
    in = 1;
    next_cycle(clk); next_cycle(clk);
    in=0;

    for(i=0; i<17; i++)
        next_cycle(clk);

    sc_close_vcd_trace_file (my_trace_file);

    return EXIT_SUCCESS;

}
/////////////////////////////////////////////////
void next_cycle (sc_signal<bool> &signal_clk)
{
    signal_clk = false;
    sc_start (1, SC_NS); // (1, SC_NS) => 1 nano seconde
    signal_clk = true;
    sc_start (1, SC_NS);
}



