#ifndef BACHELOR_FUNCTIONS_H
#define BACHELOR_FUNCTIONS_H

#include <LEDA/graph/graph_iterator.h>
#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include <LEDA/core/tuple.h>
#include <iostream>
#include "functions.h"

using namespace leda;

static void incCoverCheck(ugraph& g, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static bool adjacent(ugraph& g, node& n1, node& n2);

static bool isRegular(ugraph& g);

static void rec_vertex_cover(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered);

static void degree_two_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void degree_three_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void vertex_cover(ugraph& g, int& k, list<list<node>>& allVCs);


static void rec_vertex_cover(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered) {
// Rekursive Funktion, init und preprocessing durch vertex_cover
// coverCheck zählt, wieviele der Edges abgedeckt sind.

    if (vc.length() < k && coverCheck < g.all_edges().length()) {

        //MAIN LOOP

        node node1, node2, nAdj;

        //Hier standen die Branch Hilfsvariablen. Diese werden NUR beim Branch gebraucht

        forall_nodes(node1, g) {
                if (nodeDegree[node1] != -1) {
                    std::cout << "Checking " << node1->id() + 1 <<"\n";
                    // CASE 1:  Knoten node1 hat Grad = 1: nimm den Nachbarn von node1
                    if (nodeDegree[node1] == 1) {

                        // Füge N(node1) dem Vertex Cover hinzu und Tagge node1 und N(node1).

                        nAdj = g.adj_nodes(node1)[g.adj_nodes(node1).first()];
                        vc.append(nAdj);
                        nodeDegree[nAdj] = -1;
                        incCoverCheck(g, coverCheck, edgeCovered, nAdj);

                        nodeDegree[node1] = -1;

                        // Suche nach Vertex Cover im Graphen und Ignoriere node1
                        std::cout << "Aktuelle VCLänge: "<<vc.length() << ", Knoten abgedeckt: "<<coverCheck << ", Aktueller Knoten: " <<node1->id() + 1 << ", RekAufruf\n";
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
                        vc.append(node1);
                        nodeDegree[node1] = -1;

                        incCoverCheck(g, coverCheck, edgeCovered, node1);


                        std::cout << "Aktuelle VCLänge: "<<vc.length() << ", Knoten abgedeckt: "<<coverCheck << ", Aktueller Knoten: " <<node1->id() + 1<< ", RekAufruf\n";
                        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

                        // Branch für nAdj -> alle Nachbarn aufnehmen, dann node1 und die Nachbarn disablen
                        forall_adj_nodes(nAdj, node1) {
                                vcBranch.append(nAdj);
                                nodeDegreeBranch[nAdj] = -1;

                                incCoverCheck(g, coverCheckBranch, edgeCoveredBranch, nAdj);
                            }

                        nodeDegreeBranch[node1] = -1;

                        return rec_vertex_cover(g, vcBranch, k, nodeDegreeBranch, allVCs, coverCheckBranch, edgeCoveredBranch);

                    }

                    // CASE 3: Knoten hat Grad == 2: verwende degree_two_vertex
                    else if(degree(node1) == 2) {
                        return degree_two_vertex(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered, node1);
                    }

                    // CASE 4: Knoten hat Grad == 3: verwende degree_three_vertex

                    else if(degree(node1) == 3){
                        //return degree_three_vertex(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered, node1);
                        return;
                    }

                }
            }
    }
    std::cout << "VC-Länge: " <<vc.length() << "--RekEnde\n";
    // Fehlerquelle checken----funktioniert, Eintrag bleibt erhalten
    if (coverCheck == g.all_edges().length()) {
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

        vc.append(nAdj1);
        vc.append(nAdj2);
        nodeDegree[nAdj1] = -1;
        nodeDegree[nAdj2] = -1;
        nodeDegree[node1] = -1;

        incCoverCheck(g, coverCheck, edgeCovered, nAdj1);
        incCoverCheck(g, coverCheck, edgeCovered, nAdj2);

        std::cout << "two degree vertex CASE 1 \n";

        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

    }

    // CASE 2 : N(nAdj1) == N(nAdj2) == n (!= node1), füge node1 und n hinzu
    forall_adj_nodes(n, nAdj1) {
            if (adjacent(g, n, nAdj2) && n != node1) {
                vc.append(node1);
                vc.append(n);

                vc.append(nAdj1);
                vc.append(nAdj2);
                nodeDegree[nAdj1] = -1;
                nodeDegree[nAdj2] = -1;
                nodeDegree[node1] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, node1);
                incCoverCheck(g, coverCheck, edgeCovered, n);

                std::cout << "two degree vertex CASE 2 \n";

                return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);
            }

        }


    // CASE 3 (default):  Branch mit N(node1) und N(A) U N(B)

    // Branch für N(node1)

    vc.append(nAdj1);
    vc.append(nAdj2);
    nodeDegree[nAdj1] = -1;
    nodeDegree[nAdj2] = -1;
    nodeDegree[node1] = -1;

    incCoverCheck(g, coverCheck, edgeCovered, nAdj1);
    incCoverCheck(g, coverCheck, edgeCovered, nAdj2);

    std::cout << "two degree vertex CASE 3 branch 1 \n";

    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


    // Branch für N(A) U N(B)

    forall_adj_nodes(n, nAdj1) {
            if (nodeDegreeBranch[n] != -1) {
                vcBranch.append(n);
                nodeDegreeBranch[n] = -1;

                incCoverCheck(g, coverCheckBranch, edgeCoveredBranch, n);
            }
    }

    forall_adj_nodes(n, nAdj2){
            if(nodeDegreeBranch[n] != -1){
                vcBranch.append(n);
                nodeDegreeBranch[n] = -1;

                incCoverCheck(g, coverCheckBranch, edgeCoveredBranch, n);
            }
    }

    // da N(A) != b

    nodeDegreeBranch[nAdj1] = -1;
    nodeDegreeBranch[nAdj2] = -1;

    std::cout << "two degree vertex CASE 3 branch 2 \n";

    return rec_vertex_cover(g, vcBranch, k, nodeDegreeBranch, allVCs, coverCheckBranch, edgeCoveredBranch);

}

static void degree_three_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){

    node n;

    // Hilfsvariablen für Branches. Müssen zurerst init werden, ansonsten "ID- Fehler"
    node_array<int> nodeDegreeBranch1 = nodeDegree, nodeDegreeBranch2 = nodeDegree;
    edge_array<bool> edgeCoveredBranch1 = edgeCovered, edgeCoveredBranch2 = edgeCovered;
    int coverCheckBranch1 = coverCheck, coverCheckBranch2 = coverCheck;
    list<node> vcBranch1 = vc, vcBranch2 = vc;

    node& nAdj1 = g.adj_nodes(node1)[g.adj_nodes(node1)[0]];
    node& nAdj2 = g.adj_nodes(node1)[g.adj_nodes(node1)[1]];
    node& nAdj3 = g.adj_nodes(node1)[g.adj_nodes(node1)[2]];

    // CASE 1: Dreieck mit node1 und 2 der Nachbarn {a, b} : Branch mit N(node1) und N(c) (N(node1) = {a, b, c})

    if(adjacent(g, nAdj1, nAdj2)){
        // Branch für N(node1)
        forall_adj_nodes(n, node1) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }

        nodeDegree[node1] = -1;

        std::cout << "three degree vertex CASE 3 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(nAdj3)
        forall_adj_nodes(n, nAdj3) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }

        nodeDegree[nAdj3] = -1;

        std::cout << "three degree vertex CASE 3 branch 2 \n";
        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


    } else if(adjacent(g, nAdj1, nAdj3)){

        // Branch für N(node1)
        forall_adj_nodes(n, node1) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }

        nodeDegree[node1] = -1;

        std::cout << "three degree vertex CASE 3 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(nAdj2)
        forall_adj_nodes(n, nAdj2) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }

        nodeDegree[nAdj2] = -1;

        std::cout << "three degree vertex CASE 3 branch 2 \n";
        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

    } else if(adjacent(g,nAdj2, nAdj3)){

        // Branch für N(node1)
        forall_adj_nodes(n, node1) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }

        nodeDegree[node1] = -1;

        std::cout << "three degree vertex CASE 3 branch 1 \n";
        rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

        // Branch für N(nAdj1)
        forall_adj_nodes(n, nAdj1) {
                vc.append(n);
                nodeDegree[n] = -1;

                incCoverCheck(g, coverCheck, edgeCovered, n);
            }

        nodeDegree[nAdj1] = -1;

        std::cout << "three degree vertex CASE 3 branch 2 \n";
        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);


    }
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

    //starte Rekursuion
    rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

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
    node n;
    forall_adj_nodes(n, n1){
            if(n == n2){
                return true;
            }
        }

    return false;
}

static bool isRegular(ugraph& g){
//Überprüfe, ob Graph regulär
    node n;
    int deg = degree(g.first_node());
    forall_nodes(n, g){
            if(degree(n) != deg){
                return false;
            }
        }
    return true;
}








#endif // BACHELOR_FUNCTIONS_H