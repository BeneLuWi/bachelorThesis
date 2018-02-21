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

    std::ofstream result;
    result.open("results/analysisOne_Crown_Trott.csv");

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
    fb.open("graphenbsp/c-fat500-5.clq", std::ios::in);
    std::istream is(&fb);

    read_dimacs_graph0(is, gdimacs, v_list, n_label, e_label, 0);


    string graphLocation = "graphenbsp/g17.gw", location;
    if (gleda.read(graphLocation) != 0) {
        std::cout << "Konnte " << graphLocation << " nicht lesen\n";
        return 1;
    } else {
        std::cout << graphLocation << " eingelesen! \n";
    }

    /*for (int p = 0; p < 20; p++) {
        int i = 1000;
            for (int j = i; j < 10000; j += (i / 5)) {

                char *iP, *jP, jS[32], iS[32];


                location = "graphenbsp/tests/tests1000_";

                sprintf(iS, "%d", p);
                sprintf(jS, "%d", j);
                iP = iS;
                jP = jS;
                location += string(iP) + "-" + string(jP) + ".gw";

                random_simple_undirected_graph(gleda, i, j);

                gleda.write(location);
            }

    }
*/
    //int i=100,j=200;


    //random_simple_undirected_graph(gleda,i,j);
    //random_planar_graph(gledaDirect, i);


    //g.write("graphenbsp/g15.gw");

    // Start Programm

    int k =1000;
    for (int p = 0; p < 20; p++) {
        int i = 1000;
        for (int j = i; j < 10000; j += (i / 5)) {

            char *iP, *jP, jS[32], iS[32];


            location = "graphenbsp/tests/tests1000_";

            sprintf(iS, "%d", p);
            sprintf(jS, "%d", j);
            iP = iS;
            jP = jS;
            location += string(iP) + "-" + string(jP) + ".gw";

            gleda.read(location);


            list<list<node>> allVCs;


            //clock_t begin = clock();
            vertex_cover(gleda, k, allVCs, result);
            //clock_t end = clock();
            //result << ';'<< ((double)(end-begin))/ CLOCKS_PER_SEC << "\n";
        }

        /* i =210;
         for (int j = i; j < (i * (i-1))/10; j += (i/4)){

             char *iP, *jP,jS[32], iS[32];

             location="graphenbsp/tests/test";

             sprintf(iS,"%d",i);
             sprintf(jS,"%d",j);
             iP = iS; jP = jS;
             location += string(iP) + "-" + string(jP) + ".gw";

             gleda.read(location);

             int k =1000;
             list<list<node>> allVCs;
             vertex_cover(gleda, k, allVCs, result);
         }*/
        //int k =1000; list<list<node>> allVCs; vertex_cover(gleda, k, allVCs, result);

    }


    fb.close();
    result.close();

    return 0;
}