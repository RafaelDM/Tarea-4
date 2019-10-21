/*
Rafael Díaz Medina A01024592
David Benjamin Ruis Salazar A01020825
https://www.boost.org/doc/libs/1_55_0/libs/graph/example/
https://www.boost.org/doc/libs/1_55_0/libs/graph/example/dfs-example.cpp
https://www.boost.org/doc/libs/1_55_0/libs/graph/example/kruskal-example.cpp
https://www.boost.org/doc/libs/1_55_0/libs/graph/example/bfs-example.cpp
https://www.boost.org/doc/libs/1_55_0/libs/graph/example/prim-example.cpp
https://www.boost.org/doc/libs/1_55_0/libs/graph/example/dijkstra-example.cpp

Para poder correr este programa en windows se necesitaron de muchos pasos pero como se 
consiguio finalmente fue así:
1- Descargar dev-c++
2- Descargar Boost
3- Configurar las librerías de boost para que el compilador las pudiera leer automaticamente
4- Ejecutar el programa

Tenemos contadores en cada uno de los algoritmos y también en las operaciones
de inserción y delete

Complejidad de crear Vertice O(1)
Complejidad de borrar Vertice O(m+n)
Complejidad de crear Aristas O(1)
Complejidad de borrar Aristas O(1)
Complejidad de DFS O(m+n)
Complejidad de BFS O(m+n)
Complejidad de Dijkstra O(n log n)
Complejidad de Prim O(n log n)
Complejidad de Kruskal O(n log n)
Complejidad de Floyd Warshall O(n^3)
*/
#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string.h>
#include <bits/stdc++.h>
#include <ctype.h>
#include <stdio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <ctime> 
#include <string>
#include <algorithm>
#include <tuple>
#include <iterator>
using namespace std;
using namespace boost;
using namespace std::chrono;
#include <boost/graph/adjacency_list.hpp> 
#include <boost/graph/graph_traits.hpp> 
#include <boost/graph/graphviz.hpp> 
#include <boost/tuple/tuple.hpp> 
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijsktra_shortest_paths_no_color_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/exterior_property.hpp>


typedef property<vertex_distance_t, int> Vdistance;
typedef property<edge_weight_t, int> EdgeWeight;
typedef adjacency_list <vecS, vecS, bidirectionalS, Vdistance, EdgeWeight> Grafo;
typedef property_map<Grafo, edge_weight_t>::type EdgeWeights;
typedef boost::graph_traits<Grafo>::vertex_descriptor vertex_t;
typedef graph_traits < Grafo >::edge_descriptor Edge;
typedef boost::exterior_vertex_property<Grafo, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;

class dfsVisitor : public boost::default_dfs_visitor{
public:
	
	void discover_vertex(vertex_t v, const Grafo& n) const{
		std::cerr << v << " " ;
		
		return;
	}
};

class bfsVisitor : public boost::default_bfs_visitor{
public:
	void discover_vertex(vertex_t v, const Grafo& n) const{
		std::cerr << v << " ";
		return;
	}
};

	Grafo crearVertices(Grafo p,int vertex){
		vertex_t u;
		u= crear_vertice(p);
		name.push_back(	std::to_string(vertex));
		std::cout << "Se puso el vertice "<< vertex << "\n";
		return p;
	}

	Grafo crearAristas(Grafo p, int sale, int entra, int peso){
		crear_aristas(sale, entra, peso, p);
		std::cout << "Se puso la arista de " << sale << " a " << entra << "\n";
		return p;
	}

	Grafo borrarArista(Grafo p, int sale, int entra){
		borrar_arista(sale, entra, p);
		std::cout << "Se removio la arista de " << sale << " a " << entra << "\n";
		return p;
	}

	Grafo borrarVertice(Grafo p, int u){
		clear_vertex(u,p);
		borrar_vertice(u, p);
		std::cout << "Se ha removido el vertice " << u; 
		return p;
	}

	void DFS(Grafo p){
		dfsVisitor temp;
		std::cout << "DFS: \n";
		depth_first_search(p, visitor(temp));
	}

	void BFS(Grafo p, int inicio){
		bfsVisitor temp;
		std::cout << "BFS: \n";
		breadth_first_search(p,inicio, visitor(temp));
	}

	void dijsktra(Grafo n){
		std::vector<vertex_t> p(num_vertices(n));
		std::vector<int> d(num_vertices(n));
		vertex_t s = vertex(1, n);
		property_map<Grafo, vertex_index_t>::type indexmap = get(vertex_index, n);
		property_map<Grafo, edge_weight_t>::type weightmap = get(edge_weight, n);
		dijsktra_shortest_paths(n, s, &p[0], &d[0], weightmap, indexmap,
		std::less<int>(), closed_plus<int>(),(std::numeric_limits<int>::max)(), 0,default_dijsktra_visitor());
		graph_traits <Grafo>::vertex_iterator vi, vend;
		
		for (tie(vi, vend) = vertices(n); vi != vend; ++vi){
			std::cout << "distancia al vertice " << name[*vi] << " = " << d[*vi] << ", ";
			std::cout << " con padre " << name[p[*vi]] << std::
				endl;
		}
	}

	void prim(Grafo p){
		std::vector<vertex_t> v(num_vertices(p));
		property_map<Grafo, vertex_index_t>::type indexmap = get(vertex_index, p);
		property_map<Grafo, vertex_distance_t>::type distance = get(vertex_distance, p);
		property_map<Grafo, edge_weight_t>::type weightmap = get(edge_weight, p);
		prim_minimum_spanning_tree(p, *vertices(p).first,&v[0],distance,weightmap,indexmap, default_dijsktra_visitor());
		
		for (std::size_t i = 1; i != v.size(); ++i){
			
			if (v[i] != i){
			std::cout << "parent[" << i << "] = " << v[i] << std::endl;
			}
			else{
				std::cout << "parent[" << i << "] = no hay padre" << std::endl;
			}
		}
	}

	void kruskal(Grafo p){
		property_map < Grafo, edge_weight_t >::type weight = get(edge_weight, p);
		std::vector < Edge > spanning_tree;
		kruskal_minimum_spanning_tree(p, std::back_inserter(spanning_tree));
		std::cout << "Kruskal: \n";
		for (std::vector < Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
			std::cout << source(*ei, p) << " <--> " << target(*ei, p)<< " con peso " << weight[*ei] << std::endl;
		}
	}

	void floydWarshall(Grafo p){
		DistanceMatrix distancias(num_vertices(p));
		DistanceMatrixMap dm(distancias, p);
		property_map < Grafo, edge_weight_t >::type weight = get(edge_weight, p);
		floyd_warshall_all_pairs_shortest_paths(p, dm,boost::weight_map(weight));
		std::cout << "\n Floyd-Warshall AP-SP: " << std::endl;
		
		for (std::size_t i = 1; i < num_vertices(p); ++i) {
			
			for (std::size_t j = 1; j < num_vertices(p); ++j) {
				std::cout << "del vertice " << i  << " al " << j  << " : ";
				
				if (distancias[i][j] == std::numeric_limits<int>::max()){
					std::cout << "X" << std::endl;
				}
				else{
					std::cout << distancias[i][j] << std::endl;
				}
			}
			std::cout << std::endl;
		}
	}
};
class GrafoC{
public:
	std::vector<std::string> name = { "1","2","3","4","5","6","7","8","9","10","11","12","13","14" };
public: 

	Grafo crearGrafo(){
		std::vector<int> vertices = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
		Grafo n(vertices.size());
		std::vector<int> pesos = { 8,8,8,7,4,7,9,4,6,2,3,1,2,6,3,3,2,4,10,6,8,6,2,9 };

		crear_aristas(1,3,8,n);
		crear_aristas(1, 4,8,n);
		crear_aristas(3,5,8,n);
		crear_aristas(3,2,7,n);
		crear_aristas(3,10,4,n);
		crear_aristas(2,5,7,n);
		crear_aristas(5,6,9,n);
		crear_aristas(6,13,4,n);
		crear_aristas(13,14,6,n);
		crear_aristas(14,13,2,n);
		crear_aristas(4,7,3,n);
		crear_aristas(4,5,1,n);
		crear_aristas(4,8,2,n);
		crear_aristas(7,4,6,n);
		crear_aristas(8,7,3, n);
		crear_aristas(8,9,3, n);
		crear_aristas(9,10,2, n);
		crear_aristas(9,12,4, n);
		crear_aristas(10,3,10, n);
		crear_aristas(10,6,6, n);
		crear_aristas(12,11,8, n);
		crear_aristas(11,12,6, n);
		crear_aristas(12,9,2, n);
		crear_aristas(12,14,9, n);
		
		return n;
	}

int main(){
	high_resolution_clock::time_point t1;
   	high_resolution_clock::time_point t2;
   	duration<double> tiempo;
	
	GrafoC test;
	Grafo n = test.crearGrafo();
	int s;
	while (1){
	printf("1.Crear vertice\n2.Borrar vertice\n3.Crear arista\n4.Borrar arista\n5.DFS\n6.BFS\n7.Prim y Kruskal\n8.dijsktra y Floyd-Warshall\n");
	scanf("%d", &s);
	if(s==1){
		printf("Ingresa el numero\n");
		int num;
		scanf("%d", &num);
		t1=high_resolution_clock::now();
		test.crearVertices(n, num);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;

	}
	else if(s==2){
		printf("Ingresa el numero\n");
		int num;
		scanf("%d", &num);
		t1=high_resolution_clock::now();
		test.borrarVertice(n, num);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==3){
		printf("Los numeros que vamos a ingresar son 14, 15, 2\n");
		t1=high_resolution_clock::now();
		test.crearAristas(n, 14, 15, 2);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==4){
		printf("Borraremos 10, 3");
		t1=high_resolution_clock::now();
		test.borrarArista(n, 10, 3);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==5){
		printf("Hacemos el corrido de DFS");
		t1=high_resolution_clock::now();
		test.DFS(n);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==6){
		printf("Hacemos el corrido de BFS");
		t1=high_resolution_clock::now();
		test.BFS(n,1);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==7){
		printf("Arbol de recubrimiento Minimo con Prim y Kruskal");
		t1=high_resolution_clock::now();
		test.prim(n);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
		//------------------------------------------------------
		t1=high_resolution_clock::now();
		test.kruskal(n);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==8){
		printf("Ruta minima con dijsktra y Floyd-Warshall");
		t1=high_resolution_clock::now();
		test.dijsktra(n);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
		//-------------------------------------------------
		t1=high_resolution_clock::now();
		test.FloydWarshall(n);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;

	}
	else 
	break;
	}
	return 0;
}
