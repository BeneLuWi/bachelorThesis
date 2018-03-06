#ifndef BACHELOR_FUNCTIONS_H
#define BACHELOR_FUNCTIONS_H

#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include <LEDA/core/tuple.h>
#include <iostream>
#include <fstream>
#include <string>
#include <LEDA/graph/mcb_matching.h>
#include <LEDA/core/queue.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace leda;

using std::cout;

static void incCoverCheck(ugraph& g, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static bool adjacent(ugraph& g, node& n1, node& n2);

static bool isRegular(ugraph& g);

static void rec_vertex_cover(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered);

static void degree_two_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void degree_three_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void vertex_cover(ugraph& g, int& k, list<list<node>>& allVCs, std::ofstream &result);

static void addSelf(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static void addAdj(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1);

static int nemTrott (ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static void degreeZero(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static void buss(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, int k);

static void degreeOne(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static void degreeTwo(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static void printStatistics(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static void printReductionResults(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);

static bool colorAdj(node& n, node_array<int>& colors, graph& g);

static bool isBipartid(graph& g);

static bool isBipartid(ugraph& g);

static bool colorAdj(node& n, node_array<int>& colors);

static bool checkVertexCover(ugraph& g, list<list<node>>& allVCs);

static void crownrule(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered);







static void vertex_cover(ugraph& g, int& k, list<list<node>>& allVCs, std::ofstream &result) {
// Funktion zum preprocessen und Initialisierung der Rekursion
// nodeDegree = sortierte Liste aller Knoten und deren Grad
// edgeCovered = info, ob die Kante im Vertexcover enthalten ist

    node_array<int> nodeDegree(g, 0);
    edge_array<bool> edgeCovered(g);
    node n;
    edge e;
    int coverCheck = 0;
    list<node> vc;

    //
    // Initialisierung
    //
    forall_nodes(n, g){
            nodeDegree[n] = g.degree(n);
        }

    //g.sort_nodes(nodeDegree);

    forall_edges(e, g){
            edgeCovered[e] = false;
        }

    //
    // Statistiken
    //

    //printStatistics(g, vc, nodeDegree, coverCheck, edgeCovered);

    //iterations==anwendungen
    int prev = -1, prev2 = -1, iterations1 = 0, iterations2 = 0, iterations3 = 0, iterations4 = 0;
    int redTrott = 0, redTrottPrev = 0;
    while(prev2 != vc.length()){
        prev2 = vc.length();
        prev = -1;
        while(prev != vc.length()) {
            prev = vc.length();

            //degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
            //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
            //crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
            //redTrott = nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);

            if(redTrott!= redTrottPrev || prev!= vc.length()){
                iterations1++;
            }

            redTrottPrev = redTrott;

            //degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);

            //Falls etwas passiert ist, erhöhe Anwendungen


        }
        prev = -1;
        while(prev != vc.length()) {
            prev = vc.length();

            degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
            //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
            //crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
            //redTrott = nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);



            degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);

            //if(redTrott!= redTrottPrev || prev!= vc.length()) {
                iterations2++;
            //}

            redTrottPrev = redTrott;
        }
        prev = -1;
        while(prev != vc.length()) {
            prev = vc.length();

            //degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
            //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
            //crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
            //redTrott = nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);


            //degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);

            if(redTrott!= redTrottPrev || prev!= vc.length()){
                iterations3++;
            }

            redTrottPrev = redTrott;


        }
    }

    /*
    while(prev != vc.length()) {
        prev = vc.length();
        iterations1++;

        degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
        //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
        //crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
        //nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);

        degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);

    }
    prev = -1;
    while(prev != vc.length()) {
        prev = vc.length();
        iterations2++;

        //degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
        //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
        crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
        //nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);


        degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);


    }
    prev = -1;
    while(prev != vc.length()) {
        prev = vc.length();
        iterations3++;

        degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
        //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
        //crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
        //nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);


        degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);


    }

    prev = -1;
    while(prev != vc.length()) {
        prev = vc.length();
        iterations4++;

        //degreeOne(g, vc, nodeDegree, coverCheck, edgeCovered);
        //buss(g, vc, nodeDegree, coverCheck, edgeCovered, k);
        crownrule(g, vc, nodeDegree, coverCheck, edgeCovered);
        //nemTrott(g, vc, nodeDegree, coverCheck, edgeCovered);


        degreeZero(g, vc, nodeDegree, coverCheck, edgeCovered);


    }
*/
    //printReductionResults(g, vc, nodeDegree, coverCheck, edgeCovered);

    char delim = ';';

    int deaktiviert = 0;
    forall_nodes(n, g){
            if(nodeDegree[n] == -1){
                deaktiviert++;
            }
        }

    result << g.all_edges().length() << delim << deaktiviert << delim << iterations1<< delim << iterations2 << delim << iterations3 << delim << iterations4;

    allVCs.append(vc);

    //cout << checkVertexCover(g, allVCs)<< "-----------\n";

    //starte Rekursuion für Knotenüberdeckung
    /*rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

    if(checkVertexCover(g, allVCs)){
        std::cout << "Alle Knotenüberdeckungen korrekt! \n";
    }else{
        std::cout << "Nicht alle Knotenüberdeckungen korrekt!\n";
    }
    std::cout << "-------------------------------------------\n";

    //Ergebnis
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
    */
    //printStatistics(g, vc, nodeDegree, coverCheck, edgeCovered);
}

//
// Berechnung Vertex Cover
//

static void rec_vertex_cover(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered) {
// Rekursive Funktion, init und preprocessing durch vertex_cover
// coverCheck zählt, wieviele der Edges abgedeckt sind.

    if (vc.length() < k && coverCheck < g.all_edges().length()) {

        //MAIN LOOP

        node node1;

        //Hier standen die Branch Hilfsvariablen. Diese werden NUR beim Branch gebraucht

        forall_nodes(node1, g) {
                if (nodeDegree[node1] != -1) {

                    // CASE 1:  Knoten node1 hat Grad = 1: nimm den Nachbarn von node1
                    if (nodeDegree[node1] == 1) {
                        std::cout << "Checking " << node1->id() + 1 <<"\n \n";

                        // Füge N(node1) dem Vertex Cover hinzu
                        addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, node1);

                        // Suche nach Vertex Cover im Graphen und Ignoriere node1
                        std::cout << "standard CASE 1\n";
                        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

                    }

                    // CASE 2: Knoten hat Grad >= 5   ODER   Knoten hat Grad 2 bis 4 und Graph ist regulär: Branch mit node1 und N(node1)
                    else if (nodeDegree[node1] >= 5 || ((nodeDegree[node1]) >= 2 && nodeDegree[node1] <= 4 && isRegular(g))){
                        std::cout << "Checking " << node1->id() + 1 <<"\n \n";

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
                        std::cout << "Checking " << node1->id() + 1 <<"\n \n";

                        return degree_two_vertex(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered, node1);

                    }

                    // CASE 4: Knoten hat Grad == 3: verwende degree_three_vertex
                    else if(degree(node1) == 3){
                        std::cout << "Checking " << node1->id() + 1 <<"\n \n";

                        return degree_three_vertex(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered, node1);

                    }
                    // Knoten hat Grad 0
                    else{
                        std::cout << "Checking " << node1->id() + 1 <<"\n \n Knoten hat Grad 0 \n";
                        nodeDegree[node1] = -1;
                    }

                }
            }
    }
    std::cout << "VC-Länge: " <<vc. length() << "; Kanten abgedeckt: "<<coverCheck << "--RekEnde\n";
    if (coverCheck == g.all_edges().length() && vc.length() <= k && vc.length() > 0) {
        try{
            allVCs.append(vc);
            std::cout << "worked\n";
        }catch(const std::exception& e){
            std::cout << "didnt work\n";
        }
        std::cout << "VC added \n";
    }
    /*edge e;
    forall_edges(e , g){

            if(!edgeCovered[e]){
                std::cout << "Kanten nicht covered: "<< g.source(e)->id() +1 << "-" <<g.target(e)->id() +1 << "\n";
            }
        }
    vc.clear();*/

}

static void degree_two_vertex(ugraph& g, list<node>& vc, int& k, node_array<int>& nodeDegree,list<list<node>>& allVCs, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){
// node1 hat Grad==2. N(node1) = {nAdj1, nAdj2}, n = N(Adj1) = N(Adj2) != node1

    node n;

    // Hilfsvariablen für Branch. Müssen zurerst init werden, ansonsten "ID- Fehler"
    node_array<int> nodeDegreeBranch = nodeDegree;
    edge_array<bool> edgeCoveredBranch = edgeCovered;
    int coverCheckBranch = coverCheck;
    list<node> vcBranch = vc;

    //TODO Quick and dirty check
    //node &nAdj1 = node1;
    //node &nAdj2 = node1;
    //try {
        node &nAdj1 = g.adj_nodes(node1)[g.adj_nodes(node1)[0]];
        node &nAdj2 = g.adj_nodes(node1)[g.adj_nodes(node1)[1]];
    //}catch(const std::exception&){
      //  std::cout<< "No Neighbours to assign\n";
        //abort();
    //}

    // CASE 1: N(nAdj1) == nAdj2, füge nAdj1 und nAdj2 hinzu
    if (adjacent(g, nAdj1, nAdj2)){

        nodeDegree[node1] = -1;
        addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, nAdj1);
        addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, nAdj2);

        std::cout << "two degree vertex CASE 1\n";

        return rec_vertex_cover(g, vc, k, nodeDegree, allVCs, coverCheck, edgeCovered);

    }

    // CASE 2 : N(nAdj1) == N(nAdj2) == n (!= node1), füge node1 und n hinzu
    forall_adj_nodes(n, nAdj1) {
            if (adjacent(g, n, nAdj2) && n != node1) {

                // TODO testen, ob das hier nötig ist.
                nodeDegree[nAdj1] = -1;
                nodeDegree[nAdj2] = -1;

                addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, node1);
                addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, n);

                std::cout << "two degree vertex CASE 2  " << node1->id() +1 << " " << g.degree(node1)<<" \n";

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

    //TODO Quick and dirty check
    //node &nAdj1 = node1;
    //node &nAdj2 = node1;
    //node &nAdj3 = node1;
    //try {
        node &nAdj1 = g.adj_nodes(node1)[g.adj_nodes(node1)[0]];
        node &nAdj2 = g.adj_nodes(node1)[g.adj_nodes(node1)[1]];
        node &nAdj3 = g.adj_nodes(node1)[g.adj_nodes(node1)[2]];
    //}catch(const std::exception&){
      //  std::cout<< "No Neighbours to assign\n";
       // abort();
    //}
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

//
// Statistiken und Informationen über der Eingabegraphen
//

static void printReductionResults(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){
    node n, m;
    edge e;

    cout << "-----------\nReduktion insgesamt:\n"
         << "Knoten in VC: " << std::to_string(vc.size()) << "\n";



    cout << "\nKnoten deaktiviert: ";

    int deaktiviert = 0;
    forall_nodes(n, g){
            if(nodeDegree[n] == -1){
                //cout << n->id() + 1 << "; ";
                deaktiviert++;
            }
        }
    cout << "\n" << deaktiviert << "/" << g.all_nodes().size()<<"\n";
/*
    forall_nodes(n, g){
            if(nodeDegree[n] != -1){
                cout << "Knoten " << n->id() + 1<< " Tatsächlicher Grad: " <<g.degree(n) << " Nach Reduktion: " << nodeDegree[n]<<"\n--------\n";
                forall_adj_nodes(m, n){
                        if(nodeDegree[m] != -1) {
                            cout << "     Nachbarknoten " << m->id() + 1 << " Tatsächlicher Grad" << g.degree(m)
                                 << " Nach Reduktion:" << nodeDegree[m] << "\n";
                        }
                    }
            }
        }
*/

}

static void printStatistics(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){
    node n;
    edge e;
    std::vector<int> degrees;

    std::cout << "Info über Graphen: \n";

    // Grad 0 Knoten
    degrees.push_back(0);

    forall_nodes(n, g){
            if(nodeDegree[n] != -1) {
                while (int(degrees.size()) <= nodeDegree[n]) {

                    degrees.push_back(0);

                }
                degrees[nodeDegree[n]]++;
            }
        }
    std::cout << "Gradverteilung der Knoten: \n"
            "|Grad| Anzahl\n";

    for (int i = 0; i < int(degrees.size()); i++){
        if(i < 10)std::cout << "|   " << i << "| " << degrees[i] << "\n";
        else if(i > 9 && i < 100)std::cout << "|  " << i << "| " << degrees[i] << "\n";
        else if(i > 99)std::cout << "| " << i << "| " << degrees[i] << "\n";
    }
    std::cout << "Der Graph ist: \n";
    isBipartid(g)?std::cout << "Bipartid \n": std::cout<<"nicht Bipartid \n";
    isRegular(g)?std::cout << "Regulär \n": std::cout<<"nicht Regulär \n";


}

//
// Reduktionsregeln
//

static void degreeZero(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){
    node n;
    bool giveInfo = false;
    if(giveInfo) cout << "-----------\nKnoten mit Grad = 0\n";
    int reduction = 0;
    forall_nodes(n ,g){
            if(nodeDegree[n] == 0){
                nodeDegree[n] = -1;
                reduction++;
            }
        }

    if(giveInfo) std::cout << "reduziert: " << reduction << "\n";
}

static void buss(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, int k){
    node n;
    int reduction = 0;
    forall_nodes(n ,g){
            if(nodeDegree[n] >= k){
                addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, n);
                reduction++;
            }
        }

    std::cout << "-----------\nKnoten mit Grad >= k reduziert: " << reduction << "\n";
}

static void degreeOne(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){
    node n;
    bool giveInfo = false;
    if(giveInfo)cout << "-----------\nKnoten mit Grad = 1\n";
    int reduction = 0;
    forall_nodes(n ,g){
            if(nodeDegree[n] == 1){
                addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, n);
                reduction++;
            }
        }

    if(giveInfo)cout << "reduziert: " << reduction << "\n";

}
static void degreeTwo(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){
    node n;
    bool giveInfo = false;
    if(giveInfo)cout << "-----------\nKnoten mit Grad = 1\n";
    int reduction = 0;
    forall_nodes(n ,g){
            if(nodeDegree[n] == 2){
                addAdj(g, vc, nodeDegree, coverCheck, edgeCovered, n);
                reduction++;
            }
        }

    if(giveInfo)cout << "reduziert: " << reduction << "\n";

}
static int nemTrott (ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){

    // Bipartiden Graphen erstellen
    node_array<node> bNodesLeft(g);
    node_array<node> bNodesRight(g);
    node_array<bool> C0(g, false);
    node_array<bool> V0(g, false);
    list<node> bNodesLeftList, bNodesRightList;
    bool giveInfo = false;

    node n, m;
    edge e;

    graph b;

    if(giveInfo) cout << "-----------\nNemhauser-Trotter:\n";

    // Graphen füllen
    forall_nodes(n ,g){
            if(nodeDegree[n] > 0) {
                bNodesLeft[n] = b.new_node();
                //if(giveInfo) cout << n->id()+1 <<"= " << bNodesLeft[n]->id()+1 <<"\n";
                bNodesRight[n] = b.new_node();
                //if(giveInfo) cout << n->id()+1 <<"= " << bNodesRight[n]->id()+1 <<"\n";
            }
        }

    forall_nodes(n, g){
            if(nodeDegree[n] > 0) {
                forall_adj_nodes(m, n) {
                        if(nodeDegree[m] > 0) {
                            b.new_edge(bNodesLeft[n], bNodesRight[m]);
                            b.new_edge(bNodesRight[m], bNodesLeft[n]);
                            //if(giveInfo) cout << bNodesLeft[n]->id()+1<<" + " << bNodesRight[m]->id()+1 <<"\n";
                        }
                    }
            }
        }

    // evtl überflüssig
    node_array<node> nodeLeftLookup(b, NULL);
    node_array<node> nodeRightLookup(b, NULL);
    forall_nodes(n, g){
            if(nodeDegree[n] > 0) {
                nodeLeftLookup[bNodesLeft[n]] = n;
                nodeRightLookup[bNodesRight[n]] = n;
            }
        }


    node_array<bool> NC(b);

    // Bipartition überprüfen
    if(isBipartid(b)){
        list<edge> M = MAX_CARD_BIPARTITE_MATCHING(b, NC);
        if(!CHECK_MCB(b, M,NC)) {
             if(giveInfo) cout << "something went wrong: Matching not correct\n";
            abort();
        }
    }else{
         if(giveInfo) cout << "something went wrong: Graph not bipartid \n";
        abort();
    }
    /*
    forall_nodes(n, b){
            if(NC[n]){
                if(nodeLeftLookup[n]!=NULL) if(giveInfo) cout << "Im VC(b) "<< nodeLeftLookup[n]->id() +1 << "\n";
                else  if(giveInfo) cout << "Im VC(b) "<< nodeRightLookup[n]->id() +1 << "\n";
            }
        }
    */
    std::string kernelString, deaktiviert;
    int kernel = 0, c = 0, triv = 0;
    // C0 und V0 erstellen -> VC(V0) U C0 = VC(g)
    forall_nodes(n, g){
            if(nodeDegree[n] > 0) {
                // alle C0 in vc aufnehmen
                if (NC[bNodesLeft[n]] && NC[bNodesRight[n]]) {
                    addSelf(g, vc, nodeDegree, coverCheck, edgeCovered, n);
                    C0[n] = true;
                    if(giveInfo) cout << n->id() + 1 << " in C0 \n";
                    c++;
                }
                    // V0 nicht markieren -> werden von VC betrachtet
                else if (NC[bNodesLeft[n]] ^ NC[bNodesRight[n]]) {
                    V0[n] = true;
                    kernelString += std::to_string(n->id() +1 ) + "  ";
                    kernel++;
                }
                    // weder in V0, noch in C0 -> nicht mehr betrachten Und entfernen
                else {
                    deaktiviert += std::to_string(n->id() + 1)  + "  " + std::to_string(nodeDegree[n]) + " - ";
                    nodeDegree[n] = -1;
                    // Alle NachbarKnoten des Knotens, um einen Grad kleiner machen
                    forall_adj_nodes(m, n){

                            if(nodeDegree[m] > -1){
                                nodeDegree[m]--;
                                if(giveInfo) cout << "Verringert"<< m->id() +1 << "  "<< nodeDegree[m] << "\n";
                            }
                        }
                    // Kanten enfernen
                    forall_adj_edges(e , n){
                            if(!edgeCovered[e]){
                                edgeCovered[e] = true;
                                coverCheck++;
                            }
                        }
                    triv++;
                }
            }
        }

        if(giveInfo) cout << "Deaktiviert: " << deaktiviert << "\nProblemkern: "
                    << kernelString  << "\n"
                    <<"Problemkern (=V0): " << kernel << "\nIn die Knotenüberdeckung aufgenommen (=C0): "<< c << "\nDeaktiviert: "<<triv<< "\n";

        return triv;

}
static void crownrule(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered){

    node n, m;
    edge e, adjE;
    graph b;

    bool giveInfo = false, highDegreeFirst = true;


    if(giveInfo) cout << "-----------\nKronenregel:\n";

    // matching1: 0 = nicht betrachtet, 1 = in matching1, 2 = deaktiviert
    edge_array<int> matching1(g, 0);

    // covered: 0 = nicht von matching1 abgedeckt, 1 = von matching1 abgedeckt, 2 = Knoten ist in H (= N(I)) , 3 = Knoten ist in I'
    // O = alle Knoten n mit covered[n] == 0
    node_array<int> covered(g, 0);
    node_array<bool> addedToB(g, false);


    //
    // Maximal Matching matching1 in g finden
    //

    // zunächst nur Knoten mit Grad > 2
    if(giveInfo)  cout << "In M1: \n";

    if(highDegreeFirst) {

        int mostDegree = 0, sumNodes= 0, sumDegrees = 0;

        std::vector<int> degrees;

        // Grad 0 Knoten
        degrees.push_back(0);

        forall_nodes(n, g){
                if(nodeDegree[n]!= -1) {
                    while (int(degrees.size()) <= nodeDegree[n]) {

                        degrees.push_back(0);

                    }
                    degrees[nodeDegree[n]]++;
                }
            }

        for (int i = 0; i < int(degrees.size()); i++){
            if(degrees[i]>mostDegree) mostDegree = i;
            sumDegrees  += degrees[i] * i;
            sumNodes += degrees[i];
        }
        int limit = 0;
        if(sumNodes != 0) {
            limit = sumDegrees / sumNodes;
            //cout << "Durchschnittsgrad: "<< limit << "\n";
        }


        forall_edges(e, g) {
                if (matching1[e] == 0 && !edgeCovered[e]) {
                    if ((nodeDegree[g.source(e)] > limit) && (nodeDegree[g.target(e)] > limit)) {

                        forall_adj_edges(adjE, g.source(e)) {
                                if (!edgeCovered[adjE]) {
                                    matching1[adjE] = 2;
                                }
                            }
                        forall_adj_edges(adjE, g.target(e)) {
                                if (!edgeCovered[adjE]) {
                                    matching1[adjE] = 2;
                                }
                            }
                        matching1[e] = 1;
                        if (giveInfo)  cout << g.source(e)->id() + 1 << " - " << g.target(e)->id() + 1 << "\n";
                        covered[g.source(e)] = 1;
                        covered[g.target(e)] = 1;
                    }
                }
            }
    }

    forall_edges(e, g){
            if(matching1[e] == 0 && !edgeCovered[e]){

                forall_adj_edges(adjE, g.source(e)) {
                        if (!edgeCovered[adjE]) {
                            matching1[adjE] = 2;
                        }
                    }
                forall_adj_edges(adjE, g.target(e)) {
                        if (!edgeCovered[adjE]) {
                            matching1[adjE] = 2;
                        }
                    }
                matching1[e] = 1;
                if(giveInfo)  cout << g.source(e)->id() + 1 << " - " << g.target(e)->id() + 1 << "\n";
                covered[g.source(e)] = 1;
                covered[g.target(e)] = 1;
            }

        }

    if(giveInfo)  cout << "Nicht In M1: \n";
    forall_nodes(n, g){
            if(covered[n] == 0 && nodeDegree[n]>0){
                if(giveInfo)  cout << n->id() + 1 << "\n";
            }
        }

    // Bipartiden Graphen erstellen
    node_array<node> unmatchM1(g);
    node_array<node> adjUnmatchM1(g);

    //list<node> unmatchM1List, adjUnmatch1List;

    // Graphen füllen
    forall_nodes(n ,g){
            if(covered[n] == 0 && nodeDegree[n] > 0) {
                unmatchM1[n] = b.new_node();
                addedToB[n] = true;
                if(giveInfo)  cout << n->id() + 1 << " nicht in M1. Nachbarn: " << "\n";
                forall_adj_nodes(m, n){
                        if(!addedToB[m]) {
                            adjUnmatchM1[m] = b.new_node();
                            addedToB[m] = true;
                        }
                    }
            }
        }

    node_array<node> unmatchM1Lookup(b);
    node_array<node> adjUnmatchM1LookUp(b);
    node_array<int> unmatchM2(b, 0);

    forall_nodes(n, g){
            if(covered[n] == 0 && nodeDegree[n] > 0) {
                forall_adj_nodes(m, n) {

                            b.new_edge(unmatchM1[n], adjUnmatchM1[m]);

                            unmatchM1Lookup[adjUnmatchM1[m]] = m;

                            // evtl überflüssig?
                            adjUnmatchM1LookUp[adjUnmatchM1[m]] = m;


                    }
                unmatchM1Lookup[unmatchM1[n]] = n;
            }
        }

    if(!isBipartid(b)){
         cout << "Graph not Bipartid"<<"\n";
        abort();
    }

    edge_array<int> matching2(b, 0);

    // Maximum Matching G[O U N(O)]
    // herausfinden, welche knoten und Kanten nicht getroffen werden => unmatchM2[node] == 0
    list<edge> m2 = MAX_CARD_BIPARTITE_MATCHING(b);
    for(auto& edge1: m2){
        matching2[edge1] = 1;

        unmatchM2[b.source(edge1)] = 1;
        unmatchM2[b.target(edge1)] = 1;

        if(giveInfo)  cout << "In M2: "<< unmatchM1Lookup[b.source(edge1)]->id() + 1<<  " - "<< unmatchM1Lookup[b.target(edge1)]->id() + 1  << "\n";

    }

    int reduktion = 0;
    int prevVcSize = 0;
    // H(I) finden
    forall_nodes(n, b){
            if(giveInfo)  cout <<unmatchM2[n] << " " << covered[unmatchM1Lookup[n]] << "\n";
            // Wenn Knoten nicht in m2 gematcht wird und in O (!!!nicht in N(O)) ist, dann ist er in I
            if (unmatchM2[n] == 0 && covered[unmatchM1Lookup[n]] == 0){

                if(giveInfo)  cout<< "In I: "<< unmatchM1Lookup[n]->id() + 1 << "\n";
                // Finde H(I)
                forall_adj_nodes(m, unmatchM1Lookup[n]){
                        if(covered[m] != 0){
                            covered[m] = 2;
                            if(giveInfo)  cout << "In H(I): "<< m->id() + 1 << "\n";
                        }

                    }
                // Finde I...packe I in I', Deaktiviere I
                covered[unmatchM1Lookup[n]] = 3;
                if(nodeDegree[unmatchM1Lookup[n]] >= 0){
                    reduktion++;
                }
                nodeDegree[unmatchM1Lookup[n]] = -1;
                if(giveInfo)  cout<< "In I: "<< unmatchM1Lookup[n]->id() + 1 << "\n";
            }
        }


    // Finde alle n aus O, die eine Kante in M2 haben und
    for(auto& edge1: m2){

        // Modell: node1 -> node2 (b ist gerichtet)
        //  cout<< "Testing:  "<< unmatchM1Lookup[b.source(edge1)]->id() + 1 << covered[unmatchM1Lookup[b.source(edge1)]] <<" - " << unmatchM1Lookup[b.target(edge1)]->id() + 1<< covered[unmatchM1Lookup[b.target(edge1)]] << "\n";
        // Wenn Kante in M2 UND node1 in O UND node2 in H
        if(covered[unmatchM1Lookup[b.source(edge1)]] == 0  &&
           covered[unmatchM1Lookup[b.target(edge1)]] == 2 ){

            // Füge node1 in I'
            covered[unmatchM1Lookup[b.source(edge1)]] = 3;
            prevVcSize = vc.size();
            addAdj(g, vc, nodeDegree, coverCheck,edgeCovered, unmatchM1Lookup[b.source(edge1)]);
            reduktion += vc.size() - prevVcSize;
            if(giveInfo)  cout<< "In I': "<< unmatchM1Lookup[b.source(edge1)]->id() + 1 << "\n";
        }

        // Wenn Kante in M2 UND node2 in O UND node1 in H
        if(covered[unmatchM1Lookup[b.target(edge1)]] == 0  &&
           covered[unmatchM1Lookup[b.source(edge1)]] == 2 ){

            // Füge node2 in I'
            covered[unmatchM1Lookup[b.target(edge1)]] = 3;
            prevVcSize = vc.size();
            addAdj(g, vc, nodeDegree, coverCheck,edgeCovered, unmatchM1Lookup[b.target(edge1)]);
            reduktion += vc.size() - prevVcSize;
            if(giveInfo)  cout<< "In I': "<< unmatchM1Lookup[b.target(edge1)]->id() + 1 << "\n";
        }
    }


    if(giveInfo)  cout <<"Reduktion reduziert: "<<reduktion <<"\n";

}

static bool checkVertexCover(ugraph& g, list<list<node>>& allVCs){
    edge e;
    bool result;
    int fails = 0;
    if(allVCs.length() == 0){
        cout << "Keine Überdeckung zum überprüfen!\n";
        return false;
    }

    // überprüfe alle gefundenen VCs
    for(auto& vc : allVCs){
        // überprüfe alle Kanten
        forall_edges(e, g){
                result = false;
                // für jede Kante gucke das VC durch, ob Ziel oder Quelle im VC vorkommen
                for(auto& node1 : vc) {
                    if (g.target(e) == node1 || g.source(e) == node1) {
                        result = true;
                    }
                }
                //if(!result) return false;
                if(!result) fails++;
            }
    }
    cout << "Nicht abgedeckt: " << fails << "\n";
    return true;
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

        forall_out_edges(adjEdge, m){
                if(colors[g.target(adjEdge)] == 2){
                    colors[g.target(adjEdge)] = (colors[m]+1)%2;
                    q.push(g.target(adjEdge));
                }
                else if(colors[g.target(adjEdge)] == colors [m]){
                    return false;
                }
            }

        forall_in_edges(adjEdge, m){
                if(colors[g.source(adjEdge)] == 2){
                    colors[g.source(adjEdge)] = (colors[m]+1)%2;
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
        //std::cout << q.length()<< " in queue \n"<< m->id()+1 << " selected " << colors[m]<< "\n";

        forall_adj_nodes(adj, m){
                if(colors[adj] == 2){
                    colors[adj] = (colors[m]+1)%2;
                    //std::cout << adj->id()+1 << " assigned " << colors[adj] << "\n";
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

    node n;
    if(nodeDegree[node1] != -1) {

        vc.append(node1);
        //cout << node1->id() + 1 << " in VC\n";
        nodeDegree[node1] = -1;

        forall_adj_nodes(n, node1){
                if(nodeDegree[n] > -1){
                    nodeDegree[n]--;
                }
            }

        incCoverCheck(g, coverCheck, edgeCovered, node1);
    }
}

static void addAdj(ugraph& g, list<node>& vc, node_array<int>& nodeDegree, int& coverCheck, edge_array<bool>& edgeCovered, node& node1){
// Fügt alle Nachbarn, die noch nicht im VC sind hinzu und
// markiert die Kanten und
// markiert den aktuellen Knoten

    node n, m;

    nodeDegree[node1] = -1;
    forall_adj_nodes(n, node1) {
            if(nodeDegree[n] != -1) {
                vc.append(n);
                //cout << n->id() + 1 << " in VC\n";
                nodeDegree[n] = -1;

                // Alle NachbarKnoten des Knoten, der in die Überdeckung aufgenommen wird um einen Grad kleiner machen
                forall_adj_nodes(m, n){
                        if(nodeDegree[m] > -1){
                            nodeDegree[m]--;
                            //cout << "Verringert"<< m->id() +1 << "  "<< nodeDegree[m] << "\n";
                        }
                    }
                incCoverCheck(g, coverCheck, edgeCovered, n);
            }
        }

}







#endif // BACHELOR_FUNCTIONS_H