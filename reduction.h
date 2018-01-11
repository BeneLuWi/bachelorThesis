#ifndef BACHELOR_REDUCTION_H
#define BACHELOR_REDUCTION_H

#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include <LEDA/core/tuple.h>
#include <LEDA/graph/mcb_matching.h>
#include <iostream>
#include <LEDA/core/queue.h>

using namespace leda;

static void nemTrott (ugraph& g);

static bool colorAdj(node& n, node_array<int>& colors);

static bool isBipartid(graph& g);




static void nemTrott (ugraph& g){

        // Bipartiden Graphen erstellen
        node_array<node> bNodesLeft(g);
        node_array<node> bNodesRight(g);
        node n, m;

        graph b;


        forall_nodes(n ,g){
                bNodesLeft[n] = b.new_node();
                std::cout << n->id()+1 <<"= " << bNodesLeft[n]->id()+1 <<"\n";
                bNodesRight[n] = b.new_node();
                std::cout << n->id()+1 <<"= " << bNodesRight[n]->id()+1 <<"\n";
            }

        forall_nodes(n, g){
                forall_adj_nodes(m, n){
                    b.new_edge(bNodesLeft[n], bNodesRight[m]);
                    b.new_edge(bNodesRight[n], bNodesLeft[m]);
                        std::cout << bNodesRight[m]->id()+1<<" + " << bNodesLeft[n]->id()+1 <<"\n";
                }
            }

        node_array<node> nodeLookup(b);
        forall_nodes(n, g){
            nodeLookup[bNodesLeft[n]] = n;
            nodeLookup[bNodesRight[n]] = n;
        }

    node_array<bool> NC(b);


        if(isBipartid(b)){
            std::cout << "Bipartid graph created"" \n";
            list<edge> M = MAX_CARD_BIPARTITE_MATCHING(b, NC);
            std::cout << "MCB korrekt? "<< CHECK_MCB(b, M,NC) << "\n";
        }else{
            std::cout << "something went wrong: graph not bipartid \n";
            abort();
        }


}

static bool isBipartid(graph& g){
    //2 is default value for color
    node_array<int> colors(g, 2);
    node_array<bool> visited(g, false);
    node n;

    forall_nodes(n, g){
        if(colors[n] == 2){
            if(!colorAdj(n,colors)){
                return false;
            }
       }
    }
    return true;


}

static bool colorAdj(node& n, node_array<int>& colors){
    colors[n] = 1;
    leda_queue<node> q;
    node adj;
    q.push(n);
    while(!q.empty()){
        node m = q.pop();
        //std::cout << m->id()+1 << " selected " << colors[m] << "\n";

        forall_adj_nodes(adj, m){
                if(colors[adj] == 2){
                    colors[adj] = (colors[m]+1)%2;
                    std::cout << adj->id()+1 << " assigned " << colors[adj] << "\n";
                    q.push(adj);
                }
                else if(colors[adj] == colors [m]){
                    return false;
                }
            }
    return true;
    }

}

/*    node m;
    int tmpColor = 2;
    visited[n] = true;
    visitCount ++;
    std::cout<<visitCount << " " << colors.size() << "\n";
    forall_adj_nodes(m, n){
        // No Adj node has color yet, do nothing and assign assign color 1 to n
        std::cout << "comparing" <<n->id() +1 <<" " << colors[n] <<" with " <<m->id() +1 << " " << colors[m]<<"\n";

        if(tmpColor != 2 && tmpColor == colors[m] && colors[m] != 2){
            std::cout << "should end\n\n";
            return false;
        }

        else if(colors[m] == 0){
            std::cout << "tmp becomes " << 1 <<"\n";
            tmpColor = 1;
        }
        else if(colors[m] == 1){
            std::cout << "tmp becomes " << 0 <<"\n";
            tmpColor = 0;

        }
    }
    // color n
    if(tmpColor == 2){
        colors[n] = 1;
        std::cout << "assign " <<n->id()+1 <<" " << colors[n]<< "\n";
    }else{
        colors[n] = tmpColor;
        std::cout << "assign " <<n->id()+1 <<" " << colors[n]<< "\n";
    }

    // look for not visited nodes
    forall_adj_nodes(m, n) {
            if (!visited[m]) {
                std::cout << "look at " << m->id() + 1 << "\n";
                if (!colorAdj(m, colors, visited, visitCount, g)) {
                    return false;
                }
            }
    }
    forall_nodes(m, g) {
            if (!visited[m]) {
                std::cout << "look at " << m->id() + 1 << "\n";
                if (!colorAdj(m, colors, visited, visitCount, g)) {
                    return false;
                }
            }
        }
    if(visitCount == colors.size()){
        std::cout << visitCount << "Works \n";
        return true;
    }*/

#endif //BACHELOR_REDUCTION_H
