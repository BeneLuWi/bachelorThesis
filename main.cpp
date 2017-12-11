// Header file for chdir call...Für Testen von graphen
#ifdef __linux__
# include <unistd.h>
#endif
#ifdef _WIN32
# include <direct.h>
#endif

#include <LEDA/core/string.h>
#include <LEDA/graph/ugraph.h>
#include "functions.h"

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


    //Graphen einlesen
    ugraph g;
    if (g.read("graphenbsp/g6.gw") != 0 ){
        std::cout<< "Konnte Graph nicht lesen\n";
    }
    // Start Programm
    int k = 4;
    list<list<node>> allVCs;
    vertex_cover(g, k, allVCs);
    std::cout << "-------------------------------------------\n";

    //Ergebnis
    node n;
    list<node> it;

    if(allVCs.length()==0){
        std::cout<<"Keine Knotenüberdeckung gefunden mit |VC|<= "<< k <<"\n";
    } else{
        std::cout << allVCs.length()<<" Knotenüberdeckungen gefunden mit |VC|<= "<< k <<": \n";
        forall(it, allVCs){
                std::cout << " Länge " << it.length() << ", Knoten: ";
                forall(n, it){
                        std::cout << n->id() + 1 << " ";
                    }
            }
    }



    return 0;
}