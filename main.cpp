// Header file for chdir call...Für Testen von graphen
#ifdef __linux__
# include <unistd.h>
#endif
#ifdef _WIN32
#endif

#include <LEDA/core/string.h>
#include <LEDA/graph/ugraph.h>
#include "functions.h"
#include <LEDA/graph/dimacs.h>
#include <LEDA/graph/dimacs_graph.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace leda;

int main() {

    #ifdef __linux__
            chdir(PROJECT_DIRECTORY);
    #endif
    #ifdef _WIN32
            _chdir(PROJECT_DIRECTORY);
    #endif
    //Beispiel um Funktionalitäten zu testen.
    //VC(g0,4) = {{n1,n2,n6,n7}, {n1,n4,n5,n6}, {n2,n3,n4,n7}}

    //
    //Graphen einlesen
    //

    ugraph gdimacs, gleda;

    graph gledaDirect;
    // DIMACS Graphen einlesen

    list<node> v_list;
    node_array<int> n_label;
    edge_array<int> e_label;

    std::filebuf fb;
    fb.open ("graphenbsp/c-fat500-5.clq",std::ios::in);
    std::istream is(&fb);

    read_dimacs_graph0(is, gdimacs, v_list, n_label, e_label, 0);


    string graphLocation = "graphenbsp/g17.gw", location;
    if (gleda.read(graphLocation) != 0 ){
        std::cout<< "Konnte " << graphLocation <<" nicht lesen\n";
        return 1;
    } else{
        std::cout<< graphLocation <<" eingelesen! \n";
    }

    /*
    for (int i = 10; i < 10000; i += 1000){
        for (int j = i; j < (i * (i-1))/2; j += (i/4)){

            char *iP, *jP,jS[32], iS[32];

            location="graphenbsp/tests/test";

            sprintf(iS,"%d",i);
            sprintf(jS,"%d",j);
            iP = iS; jP = jS;
            location += string(iP) + "-" + string(jP) + ".gw";

            gleda.write(location);
        }
    }*/
    int i=100,j=1000;


    //random_simple_undirected_graph(gleda,i,j);
    //random_planar_graph(gledaDirect, i);


    //g.write("graphenbsp/g15.gw");

    // Start Programm
    /*for (int i = 10; i < 10000; i += 1000){
        for (int j = i; j < (i * (i-1))/2; j += (i/4)){

            char *iP, *jP,jS[32], iS[32];

            location="graphenbsp/tests/test";

            sprintf(iS,"%d",i);
            sprintf(jS,"%d",j);
            iP = iS; jP = jS;
            location += string(iP) + "-" + string(jP) + ".gw";

            gleda.read(location);


        }

    }*/
    int k =1000;
    list<list<node>> allVCs;
    vertex_cover(gleda, k, allVCs);


    fb.close();

    return 0;
}