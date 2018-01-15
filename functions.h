#ifndef BACHELOR_FUNCTIONS_H
#define BACHELOR_FUNCTIONS_H

#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include <LEDA/core/tuple.h>
#include "reduction.h"
#include <iostream>

using namespace leda;

static void incCoverCheck(ugraph& g, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static bool adjacent(ugraph& g, node& n1, node& n2);

static bool isRegular(ugraph& g);

static void rec_vertex_cover(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered);

static void degree_two_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void degree_three_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void vertex_cover(ugraph& g, int& k, list<list<node>>& allVCs);

static void addSelf(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void addAdj(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void nemTrott (ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static bool colorAdj(node& n, node_array<int>& colors, graph& g);

static bool isBipartid(graph& g);

static bool isBipartid(ugraph& g);

static bool colorAdj(node& n, node_array<int>& colors);

static bool checkVertexCover(ugraph& g, list<list<node>>& allVCs);





static void nemTrott (ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){

    // Bipartiden Graphen erstellen
    node_array<node> bNodesLeft(g);
    node_array<node> bNodesRight(g);
    node_array<bool> C0(g, false);
    node_array<bool> V0(g, false);
    list<node> bNodesLeftList, bNodesRightList;

    node n, m;

    graph b;

    // Graphen füllen
    forall_nodes(n ,g){
            bNodesLeft[n] = b.new_node();
            //bNodesLeftList.push(bNodesLeft[n]);
            std::cout << n->id()+1 <<"= " << bNodesLeft[n]->id()+1 <<"\n";
            bNodesRight[n] = b.new_node();
            //bNodesRightList.push(bNodesRight[n]);
            std::cout << n->id()+1 <<"= " << bNodesRight[n]->id()+1 <<"\n";
        }

    forall_nodes(n, g){
            forall_adj_nodes(m, n){
                    b.new_edge(bNodesLeft[n], bNodesRight[m]);
                    std::cout << bNodesLeft[n]->id()+1<<" + " << bNodesRight[m]->id()+1 <<"\n";
                    //b.new_edge(bNodesLeft[m], bNodesRight[n]);
                    //b.new_edge(bNodesRight[n], bNodesLeft[m]);
                    //std::cout << bNodesLeft[m]->id()+1<<" + " << bNodesRight[n]->id()+1 <<"\n";
                }
        }

    // evtl überflüssig
    node_array<node> nodeLeftLookup(b, NULL);
    node_array<node> nodeRightLookup(b, NULL);
    forall_nodes(n, g){
            nodeLeftLookup[bNodesLeft[n]] = n;
            nodeRightLookup[bNodesRight[n]] = n;
        }


    node_array<bool> NC(b);

    // Bipartition überprüfen
    if(isBipartid(b)){
        std::cout << "Bipartid graph created"" \n";
        list<edge> M = MAX_CARD_BIPARTITE_MATCHING(b, NC);
        std::cout << "MCB korrekt? "<< CHECK_MCB(b, M,NC) << "\n";
    }else{
        std::cout << "something went wrong: graph not bipartid \n";
        abort();
    }

    forall_nodes(n, b){
            if(NC[n]){
                if(nodeLeftLookup[n]!=NULL)std::cout << "Im VC(b) "<< nodeLeftLookup[n]->id() +1 << "\n";
                else std::cout << "Im VC(b) "<< nodeRightLookup[n]->id() +1 << "\n";
            }
        }

    // C0 und V0 erstellen -> VC(V0) U C0 = VC(g)
    forall_nodes(n, g){
            // alle C0 in vc aufnehmen
            if(NC[bNodesLeft[n]] && NC[bNodesRight[n]]){
                addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, n);
                C0[n] = true;
                std::cout << n->id()+ 1 << " in C0 \n";
            }
            // V0 nicht markieren -> werden von VC betrachtet
            else if(NC[bNodesLeft[n]] ^ NC[bNodesRight[n]]){
                V0[n] = true;
                std::cout << n->id()+ 1 << " in V0 \n";
            }
            // weder in V0, noch in C0 -> nicht mehr betrachten
            else{
                nodeDegree[n] = -1;
            }
        }

}

static bool checkVertexCover(ugraph& g, list<list<node>>& allVCs){
    edge e;
    node n,m;

    forall_edges(e, g){
            for(auto& nodelist : allVCs){

            }
        }
}

// directed Graph
static bool isBipartid(graph& g){
    //2 is default value for color
    node_array<int> colors(g, 2);
    node_array<bool> visited(g, false);
    node n;

    forall_nodes(n, g){
            if(colors[n] == 2){
                if(!colorAdj(n,colors, g)){
                    return false;
                }
            }
        }
    return true;
}

// directed Graph
static bool colorAdj(node& n, node_array<int>& colors, graph& g){
    colors[n] = 1;
    leda_queue<node> q;

    edge adjEdge;
    q.push(n);
    while(!q.empty()){
        node m = q.pop();
        std::cout << q.length()<< " in queue \n"<< m->id()+1 << " selected " << colors[m]<<" degree "<< degree(m) << "\n";

        forall_out_edges(adjEdge, m){
                if(colors[g.target(adjEdge)] == 2){
                    colors[g.target(adjEdge)] = (colors[m]+1)%2;
                    std::cout << g.target(adjEdge)->id()+1 << " assigned " << colors[g.target(adjEdge)] << "\n";
                    //q.append(adj);
                    q.push(g.target(adjEdge));
                }
                else if(colors[g.target(adjEdge)] == colors [m]){
                    return false;
                }
            }

        forall_in_edges(adjEdge, m){
                if(colors[g.source(adjEdge)] == 2){
                    colors[g.source(adjEdge)] = (colors[m]+1)%2;
                    std::cout << g.source(adjEdge)->id()+1 << " assigned " << colors[g.source(adjEdge)] << "\n";
                    //q.append(adj);
                    q.push(g.source(adjEdge));
                }
                else if(colors[g.source(adjEdge)] == colors [m]){
                    return false;
                }
            }
    }
    return true;

}

// undirected Graph
static bool isBipartid(ugraph& g){
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

// undirected Graph
static bool colorAdj(node& n, node_array<int>& colors){
    colors[n] = 1;
    leda_queue<node> q;
    node adj;

    q.push(n);
    while(!q.empty()){
        node m = q.pop();
        std::cout << q.length()<< " in queue \n"<< m->id()+1 << " selected " << colors[m]<<" degree "<< degree(m) << "\n";

        forall_adj_nodes(adj, m){
                if(colors[adj] == 2){
                    colors[adj] = (colors[m]+1)%2;
                    std::cout << adj->id()+1 << " assigned " << colors[adj] << "\n";
                    //q.append(adj);
                    q.push(adj);
                }
                else if(colors[adj] == colors [m]){
                    return false;
                }
            }
    }
    return true;

}

void vertex_cover(ugraph &g, int &k, list<list<node>> &allVCs) {
// Funktion zum preprocessen und Initialisierung der Rekursion
// nodeDegree = sortierte Liste aller Knoten und deren Grad
// edgeCovered = info, ob die Kante im Vertexcover enthalten ist

    node_array<int> nodeDegree(g);
    edge_array<bool> edgeCovered(g);
    node n;
    edge e;
    int coverCheck = 0;
    list<node> vc;

    //init
    forall_nodes(n, g){
            nodeDegree[n] = degree(n);
        }

    g.sort_nodes(nodeDegree);

    forall_edges(e, g){
            edgeCovered[e] = false;
        }

    isBipartid(g)? std::cout << "Bipartid\n": std::cout << "Nicht Bipartid \n";

    nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);

    //starte Rekursuion
    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

}


static void rec_vertex_cover(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered) {
// Rekursive Funktion, init und preprocessing durch vertex_cover
// coverCheck zählt, wieviele der Edges abgedeckt sind.

    if (vc.length() < k && coverCheck < g.all_edges().length()) {

        //MAIN LOOP

        node node1;

        //Hier standen die Branch Hilfsvariablen. Diese werden NUR beim Branch gebraucht

        forall_nodes(node1, g) {
                if (nodeDegree[node1] != -1) {
                    std::cout << "Checking " << node1->id() + 1 <<"\n \n";
                    // CASE 1:  Knoten node1 hat Grad = 1: nimm den Nachbarn von node1
                    if (nodeDegree[node1] == 1) {

                        // Füge N(node1) dem Vertex Cover hinzu
                        addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

                        // Suche nach Vertex Cover im Graphen und Ignoriere node1
                        std::cout << "standard CASE 1\n";
                        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

                    }

                    // CASE 2: Knoten hat Grad >= 5   ODER   Knoten hat Grad 2 bis 4 und Graph ist regulär: Branch mit node1 und N(node1)
                    else if (nodeDegree[node1] >= 5 || ((nodeDegree[node1]) >= 2 && nodeDegree[node1] <= 4 && isRegular(g))){

                        //Hilfsvariablen für den Branch
                        node_array<int> nodeDegreeBranch = nodeDegree;
                        edge_array<bool> edgeCoveredBranch = edgeCovered;
                        int coverCheckBranch = coverCheck;
                        list<node> vcBranch = vc;

                        //Branch für node1
                        addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

                        std::cout << "standard CASE 2 Branch 1\n";
                        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

                        // Branch für N(node1)
                        addAdj(g, vcBranch,nodeDegreeBranch, coverCheckBranch, edgeCoveredBranch, node1);

                        std::cout << "standard CASE 2 Branch 2 \n";
                        return rec_vertex_cover(g, vcBranch, k, nodeDegreeBranch, allVCs, coverCheckBranch, edgeCoveredBranch);

                    }

                    // CASE 3: Knoten hat Grad == 2: verwende degree_two_vertex
                    else if(degree(node1) == 2) {

                        return degree_two_vertex(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered, node1);

                    }

                    // CASE 4: Knoten hat Grad == 3: verwende degree_three_vertex
                    else if(degree(node1) == 3){

                        return degree_three_vertex(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered, node1);

                    }
                }
            }
    }
    std::cout << "VC-Länge: " <<vc.length()  << "--RekEnde\n";
    if (coverCheck == g.all_edges().length() && vc.length() <= k && vc.length() > 0) {
        allVCs.append(vc);
        std::cout << "VC added \n";
    }
    vc.clear();

}



static void degree_two_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){
// node1 hat Grad==2. N(node1) = {nAdj1, nAdj2}, n = N(Adj1) = N(Adj2) != node1

    node n;

    // Hilfsvariablen für Branch. Müssen zurerst init werden, ansonsten "ID- Fehler"
    node_array<int> nodeDegreeBranch = nodeDegree;
    edge_array<bool> edgeCoveredBranch = edgeCovered;
    int coverCheckBranch = coverCheck;
    list<node> vcBranch = vc;

    node& nAdj1 = g.adj_nodes(node1)[g.adj_nodes(node1)[0]];
    node& nAdj2 = g.adj_nodes(node1)[g.adj_nodes(node1)[1]];


    // CASE 1: N(nAdj1) == nAdj2, füge nAdj1 und nAdj2 hinzu
    if (adjacent(g, nAdj1, nAdj2)){

        nodeDegree[node1] = -1;
        addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, nAdj1);
        addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, nAdj2);

        std::cout << "two degree vertex CASE 1 \n";

        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

    }

    // CASE 2 : N(nAdj1) == N(nAdj2) == n (!= node1), füge node1 und n hinzu
    forall_adj_nodes(n, nAdj1) {
            if (adjacent(g, n, nAdj2) && n != node1) {

                // TODO testen, ob das hier nötig ist.
                // nodeDegree[nAdj1] = -1;
                // nodeDegree[nAdj2] = -1;

                addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, node1);
                addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, n);

                std::cout << "two degree vertex CASE 2 \n";

                return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);
            }

        }


    // CASE 3 (default):  Branch mit N(node1) und N(A) U N(B)

    // Branch für N(node1)

    addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

    std::cout << "two degree vertex CASE 3 branch 1 \n";

    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


    // Branch für N(A) U N(B)

    addAdj(g, vcBranch, nodeDegreeBranch, coverCheckBranch, edgeCoveredBranch, nAdj1);
    addAdj(g, vcBranch, nodeDegreeBranch, coverCheckBranch, edgeCoveredBranch, nAdj2);

    std::cout << "two degree vertex CASE 3 branch 2 \n";

    return rec_vertex_cover(g, vcBranch, k, nodeDegreeBranch, allVCs, coverCheckBranch, edgeCoveredBranch);

}

static void degree_three_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){

    node n, n1;


    // Hilfsvariablen für Branches. Müssen zurerst init werden, ansonsten "ID- Fehler"
    node_array<int> nodeDegreeBranch1 = nodeDegree, nodeDegreeBranch2 = nodeDegree;
    edge_array<bool> edgeCoveredBranch1 = edgeCovered, edgeCoveredBranch2 = edgeCovered;
    int coverCheckBranch1 = coverCheck, coverCheckBranch2 = coverCheck;
    list<node> vcBranch1 = vc, vcBranch2 = vc;

    node& nAdj1 = g.adj_nodes(node1)[g.adj_nodes(node1)[0]];
    node& nAdj2 = g.adj_nodes(node1)[g.adj_nodes(node1)[1]];
    node& nAdj3 = g.adj_nodes(node1)[g.adj_nodes(node1)[2]];

    // CASE 1: Dreieck mit node1 und 2 der Nachbarn {a, b} : Branch mit N(node1) und N(c) _____(N(node1) = {a, b, c})

    if(adjacent(g, nAdj1, nAdj2)){
        // Branch für N(node1)
        addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

        std::cout << "three degree vertex CASE 1 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(nAdj3)
        addAdj(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, nAdj3);

        std::cout << "three degree vertex CASE 1 branch 2 \n";
        return rec_vertex_cover(g, vcBranch1, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);


    } else if(adjacent(g, nAdj1, nAdj3)){

        // Branch für N(node1)
        addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

        std::cout << "three degree vertex CASE 1 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(nAdj2)
        addAdj(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, nAdj2);

        std::cout << "three degree vertex CASE 1 branch 2 \n";
        return rec_vertex_cover(g, vcBranch1, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);

    } else if(adjacent(g,nAdj2, nAdj3)){

        // Branch für N(node1)
        addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

        std::cout << "three degree vertex CASE 1 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(nAdj1)
        addAdj(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, nAdj1);

        std::cout << "three degree vertex CASE 1 branch 2 \n";
        return rec_vertex_cover(g, vcBranch1, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);

    }
    // CASE 2: Kreis mit {node1, a, b, n1} (n1 ist bel Element von g) : Branch mit N(node1) und {node1, n1}

    //finde Nachbar-Knoten d, der nicht node1 oder in N(node1) ist
    if(degree(nAdj1)> 1 && degree(nAdj2) > 1){
        forall_adj_nodes(n, nAdj1){
                if(adjacent(g, n, nAdj2) && n != nAdj3 && n != node1){

                    // Branch für N(node1)
                    addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

                    std::cout << "three degree vertex CASE 2 branch 1 \n";
                    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


                    //Branch für {node1 ,n1}
                    addSelf(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, node1);
                    addSelf(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, n1);

                    std::cout << "three degree vertex CASE 2 branch 2 \n";
                    return rec_vertex_cover(g, vcBranch1, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);
                }
            }
    }

    if(degree(nAdj1)> 1 && degree(nAdj3) > 1){
        forall_adj_nodes(n, nAdj3){
                if(adjacent(g, n, nAdj3) && n != nAdj2 && n != node1){

                    // Branch für N(node1)
                    addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

                    std::cout << "three degree vertex CASE 2 branch 1 \n";
                    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


                    //Branch für {node1 ,n1}
                    addSelf(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, node1);
                    addSelf(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, n1);

                    std::cout << "three degree vertex CASE 2 branch 2 \n";
                    return rec_vertex_cover(g, vcBranch1, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);
                }
            }
    }

    if(degree(nAdj2)> 1 && degree(nAdj3) > 1){
        forall_adj_nodes(n, nAdj3){
                if(adjacent(g, n, nAdj3) && n != nAdj1 && n != node1){

                    // Branch für N(node1)
                    addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

                    std::cout << "three degree vertex CASE 2 branch 1 \n";
                    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


                    //Branch für {node1 ,n1}
                    addSelf(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, node1);
                    addSelf(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, n1);

                    std::cout << "three degree vertex CASE 2 branch 2 \n";
                    return rec_vertex_cover(g, vcBranch1, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);
                }
            }
    }

    // CASE 3: {a, b, c} sind keine Nachbarn und Grad(a) == 4: Branch mit N(node1) und N(a) und a U N(b) U N(c)

    int degreeCase;
    node& nAdj = n;

    if(!adjacent(g, nAdj1, nAdj2) && !adjacent(g, nAdj1, nAdj3) && !adjacent(g, nAdj2, nAdj3)){
        if(degree(nAdj1) == 4){node& nAdj = nAdj1; degreeCase = 1;}
        else if(degree(nAdj2) == 4) {node& nAdj = nAdj2; degreeCase = 2;}
        else if(degree(nAdj3) == 4) {node& nAdj = nAdj3; degreeCase = 3;}
        else return;

        // Branch für N(node1)
        addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

        std::cout << "three degree vertex CASE 3 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(a) (a = nAdj)
        addAdj(g, vcBranch1, nodeDegreeBranch1, coverCheckBranch1, edgeCoveredBranch1, nAdj);

        std::cout << "three degree vertex CASE 3 branch 2 \n";
        rec_vertex_cover(g, vc, k, nodeDegreeBranch1, allVCs, coverCheckBranch1, edgeCoveredBranch1);

        // Branch für a U N(b) U N(c)
        switch (degreeCase){
            case 1 :
                addAdj(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj2);
                addAdj(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj3);
                addSelf(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj);

                std::cout << "three degree vertex CASE 3 branch 3 \n";

                return rec_vertex_cover(g, vcBranch2, k, nodeDegreeBranch2, allVCs, coverCheckBranch2, edgeCoveredBranch2);

            case 2 :
                addAdj(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj1);
                addAdj(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj3);
                addSelf(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj);

                std::cout << "three degree vertex CASE 3 branch 3 \n";

                return rec_vertex_cover(g, vcBranch2, k, nodeDegreeBranch2, allVCs, coverCheckBranch2, edgeCoveredBranch2);

            case 3 :
                addAdj(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj1);
                addAdj(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj2);
                addSelf(g, vcBranch2, nodeDegreeBranch2, coverCheckBranch2, edgeCoveredBranch2, nAdj);

                std::cout << "three degree vertex CASE 3 branch 3 \n";

                return rec_vertex_cover(g, vcBranch2, k, nodeDegreeBranch2, allVCs, coverCheckBranch2, edgeCoveredBranch2);
            }
    }

}


static void incCoverCheck(ugraph& g, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){
//Für alle Kanten an Knoten node1 überprüfe, ob die Kante bereits covered ist, ansonsten covere Sie und ehöhe coverCheck

    edge e;
    forall_adj_edges(e , node1){

            if(!edgeCovered[e]){
                edgeCovered[e] = true;
                coverCheck++;
            }
        }
}

static bool adjacent(ugraph& g, node& n1, node& n2){
// Überprüft, ob zwei Knoten benachbart sind

    node n;
    forall_adj_nodes(n, n1){
            if(n == n2){
                return true;
            }
        }

    return false;
}

static bool isRegular(ugraph& g){
//Überprüft, ob Graph g regulär ist

    node n;
    int deg = degree(g.first_node());
    forall_nodes(n, g){
            if(degree(n) != deg){
                return false;
            }
        }

    std::cout << "Graph is regular \n";
    return true;
}

static void addSelf(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){
// Fügt den aktuellen Knoten dem VC hinzu und
// markiert die Kanden und
// markiert den aktuellen Knoten

    if(nodeDegree[node1] != -1) {

        vc.append(node1);
        nodeDegree[node1] = -1;

        incCoverCheck(g, coverCheck, edgeCovered, node1);
    }
}

static void addAdj(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){
// Fügt alle Nachbarn, die noch nicht im VC sind hinzu und
// markiert die Kanten und
// markiert den aktuellen Knoten

    node n;

    forall_adj_nodes(n, node1) {
            if(nodeDegree[n] != -1) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }
        }

    nodeDegree[node1] = -1;
}





#endif // BACHELOR_FUNCTIONS_H