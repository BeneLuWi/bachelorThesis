#ifndef BACHELOR_REDUCTION_H
#define BACHELOR_REDUCTION_H

#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include <LEDA/core/tuple.h>
#include <LEDA/graph/mcb_matching.h>
#include <iostream>

using namespace leda;

static void nemTrott (ugraph& g, node_array< bool>& NC);

static bool colorAdj(node& n, node_array<int>& colors);

static bool isBipartid(ugraph& g);




static void nemTrott (ugraph& g, node_array< bool>& NC){

    if(isBipartid(g)){
        // NC ist Referenz
        //MAX_CARD_BIPARTITE_MATCHING(g, NC);
    }

    else{

        // Bipartiden Graphen erstellen
        node_array<node> bNodesLeft(g);
        node_array<node> bNodesRight(g);
        edge e;
        node n, m;

        ugraph b;

        forall_nodes(n ,g){
                bNodesLeft[n] = b.new_node();
                std::cout << n->id()+1 <<"= " << bNodesLeft[n]->id()+1 <<"\n";
                bNodesRight[n] = b.new_node();
                std::cout << n->id()+1 <<"= " << bNodesRight[n]->id()+1 <<"\n";
            }


        forall_nodes(n, g){
                forall_adj_nodes(m, n){
                    b.new_edge(bNodesLeft[n], bNodesRight[m]);
                        std::cout << bNodesRight[m]->id()+1<<" + " << bNodesLeft[n]->id()+1 <<"\n";
                }
            }
        isBipartid(b)? std::cout<< "jeeese \n" : std::cout << "shit \n";
    }

}


static bool isBipartid(ugraph& g){
    //2 is default value
    node_array<int> colors(g, 2);
    node_array<bool> visited(g, false);
    node n = g.first_node();

    int recCount = 1, recMax = g.all_nodes().length();

    forall_nodes(n, g){
            if (!colorAdj(n,colors, visited)) return false;
        }

    return true;

}

static bool colorAdj(node& n, node_array<int>& colors, node_array<bool>& visited){
    node m;

   /* if(colors[n] == 2){
        forall_adj_nodes(m, n){
                switch (colors[m]){
                    case 1:
                        if(colors[n] == 2){
                            colors[n] = 0;
                            break;

                        }else if(colors[n] == 0){
                            break;
                        }
                    std::cout<< m->id() +1 <<": "<< colors[m] << n->id() + 1  << ": "<< colors[n]<<"fail\n";
                        return false;

                    case 0:
                        if (colors[n] == 2){
                            colors[n] = 1;
                            break
                                    ;
                        }else if(colors[n] == 1){
                            break;
                        }
                        std::cout<< m->id() +1 <<": "<< colors[m] << n->id() + 1  << ": "<< colors[n]<<"fail\n";
                        return false;

                    default:
                        colors[n] = 1;
                        break;
                }

            }
    }*/

    std::cout << "\n\n--" << n->id()+1 <<": "<< colors[n] << "\n\n";
    forall_adj_nodes(m, n){
            if(colors[n]==1){
                switch (colors[m]) {
                    case 2:
                        colors[m] = 0;
                        std::cout << m->id()+1 <<": "<< colors[m] << ", ";
                        return

                    case 1:
                        std::cout << m->id()+1 <<": "<< colors[m] << ": "<< "FAIL\n";
                        return false;

                    case 0:
                        std::cout << m->id()+1 <<": "<< colors[m] << ", ";
                        break;
                }

            }else if(colors[n]==0){
                switch (colors[m]){
                    case 2:
                        colors[m] = 1;
                        std::cout << m->id()+1 <<": "<< colors[m] << ", ";
                        break;

                    case 1:
                        std::cout << m->id()+1 <<": "<< colors[m] << ", ";
                        break;

                    case 0:
                        std::cout << m->id()+1 <<": "<< colors[m] << "FAIL\n";
                        return false;
                }

            }

        }
    return true;
}



#endif //BACHELOR_REDUCTION_H
