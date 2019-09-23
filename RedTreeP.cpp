/*
Rafael Díaz Medina A1024592
*/
//Librerías
#include <iostream>
#include <fstream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h> 
#include "time.h"
#include <chrono>
using namespace std::chrono;

#define RED		1
#define BLACK	2
//estructura de un nodo
struct node {
	int key;
	struct node *left, *right, *p;
	int color;
	int size;
};

typedef struct node *NODERB;
struct node NIL;
NODERB NILPTR = &NIL;
//Ordenar de menor a Mayor------------------------
void menorMayor(NODERB x) {
	if (x != NILPTR) {
		menorMayor(x->left);
		printf("%d ", x->key);
		menorMayor(x->right);
	}
}
//ordenar de mayor a Menor-------------------
void mayorMenor(NODERB x){
	if (x != NILPTR){
		mayorMenor(x-> right);
		printf("%d ", x->key);
		menorMayor(x->left);
	}
}
//Busqueda de un nodo-------------------
NODERB Busqueda(NODERB root, int k) {
	if (root == NILPTR || root->key == k)
		return root;
		
	if (k < root->key)
		return Busqueda(root->left, k);
		
	else
		return Busqueda(root->right, k);
		
}
//Altura de un nodo--------------------
NODERB high(NODERB root, int nodoB , NODERB size){
	
	if (root == NILPTR || root->key == nodoB)
		return size;
		
	else{
		size++;
		if(nodoB < root->key) root=root->left;
		else if
		(root->right, nodoB) root = root->right;
	}
}
//Encontrar el elemento más pequeño, esto me sirve para poder borrar en uno de los casos---------
NODERB minimo(NODERB root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}
//rotación del arbol hacia la Izquierda-----------------
void izquierda(NODERB *treeroot, NODERB x) {
	NODERB y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}
//Rotación del arbol hacia la derecha----------------------
void derecha(NODERB *treeroot, NODERB y) {
	NODERB x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}
//Arreglar el arbol en caso de que se desomponga al momento de insertar un elemento------------------
void rbinsertfixup(NODERB *treeroot, NODERB z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			NODERB y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					izquierda(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				derecha(treeroot,z->p->p);
			}
		}
		else {
			NODERB y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					derecha(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				izquierda(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}
//Insertar un nodo en el arbo---------------
void rbinsert(NODERB *treeroot, int z) {
	NODERB Z = (NODERB) malloc(sizeof(struct node));
	Z->key = z;
	NODERB y = NILPTR;
	NODERB x = *treeroot;
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	rbinsertfixup(treeroot,Z);
}
//para poder cambiar de padres e hijos los nodos al momento de borrar algo en el arbol-------------
void rbtransplant(NODERB *treeroot, NODERB u, NODERB v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}
//Lo mismo que en el insertar pero ahora para borrar---------------------
void rbdeletefixup(NODERB *treeroot, NODERB x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x == x->p->left) {
			NODERB w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				izquierda(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					derecha(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				izquierda(treeroot,x->p);
				x = *treeroot;
			}
		}
		else {
			NODERB w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				derecha(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					izquierda(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				derecha(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}
//Borrar con todos los posibles casos que esto conlleva-----------------
void rbdelete(NODERB *treeroot, int z) {
	NODERB Z = Busqueda(*treeroot, z);
	if (Z == NILPTR) {
		printf("Nodo no encontrado\n");
		return;
	}
	NODERB y = Z;
	int yoc = y->color;
	NODERB x;
	if (Z->left == NILPTR) {
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else {
		y = minimo(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}
//Metodo de Tiempo
int getMilisegundos(clock_t c)
{
    int tiempo=0;
    tiempo = (int)((c/(double)CLOCKS_PER_SEC)*1000) ;
return tiempo;
}
//main de este programa-------
main(){
	//para la función de tiempo 
	high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double> tiempo;

	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	NODERB tree = NILPTR;
	int n;
	int i;
 /* Leer archivos desde un txt
 --------------------------------------------------------------------*/
ifstream fin("elementos.txt");
int num;
for(i=0; i<=100000; i++){
fin>> num;
rbinsert(&tree, num);

}
/*----------------------------------------------------------*/
	while (1) {
		printf("1.Insertar\n2.Buscar\n3.Menor a Mayor\n4.Mayor a Menor\n5.Borrar\n6.Altura de nodo\n7.Salida\n");
		scanf("%d", &n);
		if (n == 1) {
			printf("Ingresa el Numero\n");
			int num;
			scanf("%d", &num);
			rbinsert(&tree, num);
		}
		else if (n == 2) {
			printf("Ingresa el Numero\n");
			int num;
			scanf("%d", &num);
			t1 = high_resolution_clock::now();
			if (Busqueda(tree, num) == NILPTR){
				printf("%d no encontrado\n", num);
			}
			else
				printf("%d Encontrado\n", num);
			t2 = high_resolution_clock::now();
			 tiempo = duration_cast<duration<double>>(t2-t1);
        tiempo=tiempo*1000;
        cout << tiempo.count() << "milisegundos" << endl;
		}
		else if (n == 3) {
			menorMayor(tree);
			printf("\n");
		}
		else if (n == 4){
			mayorMenor(tree);
			printf("\n");
		}
		else if (n == 5) {
			printf("Ingresa el numero\n");
			int num;
			scanf("%d", &num);
			rbdelete(&tree, num);
		}
		else if (n == 6) {

			printf("Ingresa el numero\n");
			int num;
			scanf("%d", &num);
			if (high(tree, num, 0) == NILPTR){
				printf("%d no encontrado\n", num);
			}
			else{
				printf("%d encontrado\n", high(tree, num,0));	
			}
		}
		else 
			break;
	}
	return 0;
}

/*
Insertar listo
Borrar Listo
Imprimir Ordenado Listo
Imprimir Ordenado hacia abajo listo
Obtener la altura de cualquier nodo falta Creo que los tres son lo mismo
Obtener la profundidad falta
Obtener el nivel de cualquier nodo falta
*/