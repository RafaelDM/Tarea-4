/*
David Benjamon Ruiz Salazar A01020825
Rafael Díaz Medina A01024592

Para poder correr este programa en Windows se necesitaron de muchos pasos pero como se 
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
Complejidad de DFS O(m+n) Este algoritmo utiliza una tecnica Branch and bound
Complejidad de BFS O(m+n) Este algoritmo utiliza una tecnica Branch and bound
Complejidad de Dijkstra O(n log n) Este algoritmo utiliza una tecnica Avida
Complejidad de Prim O(n log n) Este algoritmo utiliza una tecnica Avida
Complejidad de Kruskal O(n log n) Este algoritmo utiliza una tecnica Avida
Complejidad de Floyd Warshall O(n^3) Este algoritmo utiliza una tecnica de programacion dinamica
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
#include <list>
using namespace std;
using namespace boost;
using namespace std::chrono;
#include "Snap.h"
#define vertice 23 
#define nodos 14

struct pesoArista{
    int ID;
    int peso;
};
void crearVertices(GrafoC test) {
  for(int i = 0; i<nodos; i++){
      test -> crearNodo(i+1);
  }
}
void borrarVertices(int id,GrafoC test){
    test -> borrarNodo(id);
}
void crearAristas(GrafoC test, pesoArista arrV[], int origen, int destino, int peso){
    int id;
    test -> crearArista(origen,destino,-1);
    id = test ->idArista(origen,destino);
    arrV[id].ID = id;
    arrV[id].peso = peso;
}

void borrarAristas(int id, GrafoC test){
    test -> DelEdge(id);
}
void DFS( GrafoC test, int source){
    bool visitado[nodos];
    stack<int> stack;
    int s, counter=0; int dfs[nodos];;

    for(int i=0; i<nodos; i++){
        visitado[0] = false;
    }
    stack.push(source);

    printStack(stack);
    while(!stack.empty()){

        s = stack.top();
        stack.pop();

        if(visitado[s-1] == false){
            visitado[s-1] = true;
            dfs[counter] = s;
            counter++;
        }

        for(int i = 0; i<nodos; i++){
            if((test -> Arista(s, i+1, true) == 1) && visitado[i]== false){
                stack.push(i+1);
            }
        }


    }
}
void BFS(GrafoC test, int source){
    bool visitado [nodos];
    queue <int> que;
    int bfs[nodos];
    int front, counter = 0;

    for(int i = 0; i < M; i++){
        visitado [i] = false;
    }

    visitado[source-1] = true;
    que.push(source);

    while(!que.empty()){
        front = que.front();
        bfs[counter] = front;
        counter++;

        for(int i = 0; i<nodos; i++){
            if((test -> Arista(front, i+1, true) == 1) && visitado[i]== false){
                visitado[i] = true;
                que.push(i+1);
            }
        }

        que.pop();
    }
}

void prim(GrafoC test, pesoArista arrV[]){
    int counter = 0, id, min, destino;
    int nodos [2][nodos];
    int pesos [vertice];
    for(int i =0; i<nodos; i++){
        nodos[0][i] = i+1;
    }

    for(int x = 0; x<nodos; x++){
        destino = x+1;
        counter=0;
        for(int i = 0; i<nodos; i++){
            if(test -> Arista(i+1, destino, true) == 1){
                id = test ->idArista(i+1,destino);
                pesos[counter] = arrV[id].peso;
                counter++;
            }
        }

                min = pesos[0];
                for(int k = 0; k<counter;k++){
                    if(pesos[k]<min){
                        min = pesos[k];
                    }
                }
                nodos[1][x] = min;
    }
    nodos[1][0] = NULL;
}

void kruskal(GrafoC test, pesoArista arrV[]){
    list<int> T;
    subset *subsets = new subset[vertice];
    int x, y, src, drc;

    for (int i = 0; i < vertice; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

        pesoArista VerticeOrd[vertice];
        for(int i =0; i<vertice; i++){
            VerticeOrd[i].ID = arrV[i].ID;
            VerticeOrd[i].peso = arrV[i].peso;
        }

        sort(VerticeOrd, VerticeOrd+vertice, compare);

    for(int i =0; i<vertice; i++){
        src = GetSrc(VerticeOrd[i].ID, test);
        drc = GetDrc(VerticeOrd[i].ID, test);

        x = encontrar(subsets, src);
        y = encontrar(subsets, drc);

        if(x != y){
            T.push_back(VerticeOrd[i].ID);
            unir(subsets, x, y);
        }
        else{

        }
    }
}

void dijkstra(GrafoC test, pesoArista arrV[], int source){
    int u = source-1;
    int distancia[nodos];
    bool visitado[nodos];
    for(int i =0; i<nodos; i++){
        distancia[i] = 10000;
        visitado[i] = false;
    }
    distancia[source-1] = 0;
    for(int i = 0; i<nodos; i++){
        for(int v=0; v<nodos;v++){
        if(test -> Arista(u+1, v+1, true) == 1){
        int id = test ->idArista(u+1,v+1);
        int x = arrV[id].peso;
			if(!visitado[v] && distancia[u]!=10000 && distancia[u]+x<distancia[v]){
			distancia[v]=distancia[u]+x;

		    }
        }
    }
    u = minDijkstra(distancia, visitado);
        visitado[u] = true;
  }
}

void floyd(GrafoC test, pesoArista arrV[]){
    int id, temp;
    int A[nodos][nodos];
    for(int i = 0; i<nodos; i++){
        for(int j = 0; j<nodos; j++){
            if(test -> Arista(i+1, j+1, true) == 1){
                 id = test ->idArista(i+1,j+1);
                 A[i][j] = arrV[id].peso;
            }
            else{
                A[i][j] = 10000;
            }
        }
    }

    for(int i = 0; i<nodos; i++){
        A[i][i] = 0;
    }


    int C[nodos][nodos];
    for(int i = 0; i<nodos; i++){
        for(int j = 0; j<nodos; j++){
            C[i][j] = A[i][j];
        }
    }

    for(int k = 0; k<nodos; k++){
        for(int i = 0; i<nodos; i++){
            for(int j = 0; j<nodos; j++){
                temp = C[i][k] + C[k][j];
                if( C[i][j] > temp){
                    C[i][j] = temp;
                }
            }
        }
    }
}
struct subset{
    int parent;
    int rank;
};

bool compare(pesoArista a, pesoArista b){
    return a.peso < b.peso;
}

int GetSrc(int id, GrafoC test){
    int x;
    for (Graph::TEdgeI EI = test->BegEI(); EI < test->EndEI(); EI++) {
        if( EI.GetId() == id){
            x = EI.GetSrcNId();
        }
    }
    return x;
}

int GetDrc(int id, GrafoC test){
    int x;
    for (Graph::TEdgeI EI = test->BegEI(); EI < test->EndEI(); EI++) {
        if( EI.GetId() == id){
           x = EI.GetDstNId();
        }
    }
    return x;
}

int encontrar(subset subsets[], int i){
    if (subsets[i].parent != i)
        subsets[i].parent = encontrar(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void unir(subset subsets[], int x, int y)
{
    int xroot = encontrar(subsets, x);
    int yroot = encontrar(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
int minDijkstra(int *distancia, bool *visitado){
    int min = 9999;
    int index;

    for(int i = 0; i<nodos; i++){
        if(visitado[i] == false && distancia[i] <= min){
            min = distancia[i];
            index = i;
        }
    }
    return index;

}

void insertarAristas(GrafoC test, pesoArista arrV[]){
    crearAristas(test,arrV,1,4,8);
    crearAristas(test,arrV,1,3,8);
    crearAristas(test,arrV,4,8,2);
    crearAristas(test,arrV,4,7,3);
    crearAristas(test,arrV,7,4,6);
    crearAristas(test,arrV,8,7,3);
    crearAristas(test,arrV,8,9,3);
    crearAristas(test,arrV,9,12,4);
    crearAristas(test,arrV,9,10,2);
    crearAristas(test,arrV,12,9,2);
    crearAristas(test,arrV,12,11,8);
    crearAristas(test,arrV,11,12,6);
    crearAristas(test,arrV,12,14,9);
    crearAristas(test,arrV,14,13,2);
    crearAristas(test,arrV,13,14,6);
    crearAristas(test,arrV,3,10,4);
    crearAristas(test,arrV,10,3,10);
    crearAristas(test,arrV,3,2,7);
    crearAristas(test,arrV,3,5,8);
    crearAristas(test,arrV,2,5,7);
    crearAristas(test,arrV,4,5,1);
    crearAristas(test,arrV,5,6,9);
    crearAristas(test,arrV,6,13,4);
}
int main(){
    high_resolution_clock::time_point t1;
   	high_resolution_clock::time_point t2;
   	duration<double> tiempo;
	
    GrafoC test;
    pesoArista arrV[vertice];
    test = Graph::New();
//------------------------------------------
while (1){
	printf("1.Crear vertice\n2.Borrar vertice\n3.Crear arista\n4.Borrar arista\n5.DFS\n6.BFS\n7.Prim y Kruskal\n8.dijsktra y Floyd-Warshall\n");
	scanf("%d", &s);
	if(s==1){
		printf("Crear Vertices\n");
		t1=high_resolution_clock::now();
		crearVertices(test);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;

	}
	else if(s==2){
		printf("Borraremos el 3\n");
		t1=high_resolution_clock::now();
		borrarVertices(3, test);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==3){
		printf("Insertar Aristas\n");
		t1=high_resolution_clock::now();
		insertarAristas(test, arrV);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==4){
		printf("Borraremos 1");
		t1=high_resolution_clock::now();
		borrarAristas(1, test);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==5){
		printf("Hacemos el corrido de DFS");
		t1=high_resolution_clock::now();
		DFS(test, 1);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==6){
		printf("Hacemos el corrido de BFS");
		t1=high_resolution_clock::now();
		BFS(test, 1);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==7){
		printf("Arbol de recubrimiento Minimo con Prim y Kruskal");
		t1=high_resolution_clock::now();
		prim(test, arrV);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
		//------------------------------------------------------
		t1=high_resolution_clock::now();
		kruskal(test, arrV);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
	}
	else if(s==8){
		printf("Ruta minima con dijsktra y Floyd-Warshall");
		t1=high_resolution_clock::now();
		dijkstra(test, arrV, 1);
		t2=high_resolution_clock::now();
		tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
		//-------------------------------------------------
		t1=high_resolution_clock::now();
		floyd(test, arrV);
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
