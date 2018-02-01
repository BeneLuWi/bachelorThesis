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

    // DIMACS Graphen einlesen

    list<node> v_list; 
    node_array<int> n_label;
    edge_array<int> e_label;

    std::filebuf fb;
    fb.open ("graphenbsp/frb59-26-5.mis",std::ios::in);
    std::istream is(&fb);

    read_dimacs_graph0(is, gdimacs, v_list, n_label, e_label, 0);


    string graphLocation = "graphenbsp/g15.gw";
    if (gleda.read(graphLocation) != 0 ){
        std::cout<< "Konnte " << graphLocation <<" nicht lesen\n";
        return 1;
    } else{
        std::cout<< graphLocation <<" eingelesen! \n";
    }

    int i=10000,j=30000;

    //random_simple_undirected_graph(g,i,j);
    //g.write("graphenbsp/g15.gw");
    // Start Programm
    int k =220;
    list<list<node>> allVCs;
    vertex_cover(gdimacs, k, allVCs);


    fb.close();

    return 0;
}