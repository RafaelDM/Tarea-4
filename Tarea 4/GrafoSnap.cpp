#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <queue>
#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
#include "time.h"
#include "Snap.h"

using namespace std::chrono;
using namespace std;
typedef PNGraph Graph;

void graphML(Graph g);
void GEXF(Graph g);
void GDF(Graph g);
void graphSon(Graph g);

int main() {
    high_resolution_clock::time_point t1;
   	high_resolution_clock::time_point t2;
   	duration<double> tiempo;
    
    Graph graph = TSnap::LoadEdgeList<Graph>("Nutella.txt",0,1);
  
    t1 = high_resolution_clock::now();
    graphML(graph);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<duration<double>>(t2-t1);
    tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;

    cout << "GEFX" << endl;
    t1 = high_resolution_clock::now();
    GEXF(graph); 
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<duration<double>>(t2-t1);
    tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;

    cout << "GDF" << endl;
    t1 = high_resolution_clock::now();
    GDF(graph);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<duration<double>>(t2-t1);
    tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
    
    cout << "graphSon" << endl;
    t1 = high_resolution_clock::now();
    graphSon(graph);
    t2 = high_resolution_clock::now();
    tiempo = duration_cast<duration<double>>(t2-t1);
    tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
    return 0;
}


void GDF(Graph g) {
    std::ofstream file;
    file.open("graph.gdf");
    if (file.is_open()) {
        file << "nodedef>id VARCHAR\n";
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            file << NI.GetId() << "\n";
        
        file << "edgedef>source VARCHAR, destination VARCHAR\n";
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++)
            file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";
        
        file.close();
    }
}

void graphML(Graph g) {
    std::ofstream file;
    file.open("graph.graphml");
    if (file.is_open()) {
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        file << "<graph id=\"G\" edgedefault=\"undirected\">\n";
        
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            file << "<node id=\"" << NI.GetId() << "\"/>\n";
        
        int i = 1;
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
            file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";
        
        file << "</graph>\n";
        file << "</graphml>\n";
        file.close();
    }
}

void GEXF(Graph g) {
    std::ofstream file;
    file.open("graph.gexf");
    if (file.is_open()) {
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        file << "<graph mode=\"static\" defaultedgetype=\"undirected\">\n";
        
        file << "<nodes>\n";
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
            file << "<node id=\"" << NI.GetId() << "\" />\n";
        file << "</nodes>\n";
        
        file << "<edges>\n";
        int i = 1;
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
            file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
        file << "</edges>\n";
        
        file << "</graph>\n";
        file << "</gexf>\n";
        file.close();
    }
}



void graphSon(Graph g) {
    std::ofstream file;
    file.open("graph.json");
    if (file.is_open()) {
        file << "{ \"graph\": {\n";
        file << "\"nodes\": [\n";
        for (Graph::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); ) {
            file << "{ \"id\": \"" << NI.GetId() << "\" }";
            if (NI++ == g->EndNI())
                file << " ],\n";
            else
                file << ",\n";
        }
        
        file << "\"edges\": [\n";
        for (Graph::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); ) {
            file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
            if (EI++ == g->EndEI())
                file << " ]\n";
            else
                file << ",\n";
        }
        file << "} }";
        
        file.close();
    }
}
