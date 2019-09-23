#ifndef ArbolB_h
#define ArbolB_h

#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std; 

template <class T>
struct Nodo {
    
    int llave = NULL;
    int espaciosUsados = 0;
    int padre = NULL;
    bool leaf = false;
    T *info;
    int *hijos;
    
    
    
    Nodo(int);
    Nodo(int,int,fstream &);
    virtual ~Nodo();
    
    bool checkFull(int);
    
    
    void printInfo();
    void print(int);
    
};

template <class T>
void Nodo<T>::printInfo(){
    for(int i = 0; i < espaciosUsados;i++){
        cout << info[i] << " ";
    }
}

template <class T>
class ArbolB {
private:
    
    int currentID;
    int orden;
    fstream data;
    void setData();
    
public:
    
    ArbolB(int orden);
    ~ArbolB();
    void Insertar(T dato);
    void Borrar(T dato);
    
    void printNodos();
    void print(Nodo<T> & nodo);
    void printAsc();
    void printDesc();
    void asc(Nodo<T> & nodo);
    void desc(Nodo<T> & nodo);
    
    void updateTotal(int cantidad);
    int getRoot();
    void setRoot(int rootID);
    
    void borrarDato(Nodo<T> & nodo,T dato);
    void borrarLeaf(Nodo<T> & nodo,int);
    void borrarNoLeaf(Nodo<T> & padre,int);
    int getAnterior(Nodo<T> & padre,int);
    int getSiguiente(Nodo<T> & padre,int);
    void fill(Nodo<T> & padre,int);
    void prestadoAnterior(Nodo<T> & padre,int);
    void prestadoSiguiente(Nodo<T> & padre,int);
    void unir(Nodo<T> & padre,int);
    int encontrarInfo(Nodo<T> & nodo,T);
    
    void insertarDato(Nodo<T> & nodo,T dato);
    void divideNodo(Nodo<T> & nodoPadre,int i,Nodo<T> & nodo);
    void save(Nodo<T> & nodo);
    Nodo<T> carga(int llaveDeCarga);
    void Buscar(T dato);
    void buscarDato(Nodo<T> & nodo,T dato);
    void cargaNodo(Nodo<T> *,int);
    int cantidadNodos(); // Checa cantidad de nodos
};

template <class T>
ArbolB<T>::ArbolB(int orden){
    this->orden = orden;
    currentID = 0;
    setData();
    Nodo<T> nodo(orden);
    nodo.llave = currentID;
    nodo.leaf = true;
    save(nodo);
    currentID++;
}

template <class T>
int ArbolB<T>::encontrarInfo(Nodo<T> & nodo,T dato){
    int i=0;
    while (i<nodo.espaciosUsados && nodo.info[i] < dato)
        i++;
    return i;
}

template <class T>
void ArbolB<T>::Borrar(T dato){
    Nodo<T> root = carga(getRoot());
    borrarDato(root, dato);
    if(root.espaciosUsados==0){
        if(!root.leaf)
            setRoot(root.hijos[0]);
    }
}

template <class T>
void ArbolB<T>::borrarDato(Nodo<T> & nodo,T dato){
    int i = encontrarInfo(nodo, dato);
    if(i < nodo.espaciosUsados && nodo.info[i] == dato){
        if(nodo.leaf){
            borrarLeaf(nodo,i);
            save(nodo);
        }
        else{
            borrarNoLeaf(nodo,i);
            save(nodo);
        }
    }
    else{
        if(nodo.leaf){
            cout << "El dato " << dato << " no existe en el arbol" << endl;
        }
        else{
            bool flag = ( (i==nodo.espaciosUsados)? true : false );
            //bool flag = i == nodo.espaciosUsados;
            Nodo<T> hijo = carga(nodo.hijos[i]);
            T chancla = hijo.info[1];
            if(hijo.espaciosUsados < orden)
                fill(nodo,i);
            if(flag && i > nodo.espaciosUsados){
                hijo = carga(nodo.hijos[i-1]);
                borrarDato(hijo, dato);
            }
            else{
                hijo = carga(nodo.hijos[i]);
                chancla = hijo.info[2];
                borrarDato(hijo,dato);
            }
        }
    }
}

template <class T>
void ArbolB<T>::borrarLeaf(Nodo<T> & nodo,int i){
    for (int j = i+1; j < nodo.espaciosUsados; j++)
        nodo.info[j-1] = nodo.info[j];
    nodo.espaciosUsados--;
}

template <class T>
void ArbolB<T>::borrarNoLeaf(Nodo<T> & padre,int i){
    T dato = padre.info[i];
    Nodo<T> hijo = carga(padre.hijos[i]);
    Nodo<T> hijoHermano = carga(padre.hijos[i+1]);
    if(hijo.espaciosUsados >= orden){
        T antes = getAnterior(padre,i);
        padre.info[i] = antes;
        borrarDato(hijo, antes);
    }
    else if(hijoHermano.espaciosUsados >= orden){
        T siguiente = getSiguiente(padre,i);
        padre.info[i] = siguiente;
        borrarDato(hijoHermano, siguiente);
    }
    else{
        unir(padre,i);
        hijo = carga(hijo.llave);
        borrarDato(hijo,dato);
        //borrarDato(hijoHermano, dato);
    }
}


template <class T>
int ArbolB<T>::getAnterior(Nodo<T> & padre,int i){
    Nodo<T> hijo = carga(padre.hijos[i]);
    while(!hijo.leaf)
        hijo = carga(hijo.hijos[hijo.espaciosUsados]);
    return hijo.info[hijo.espaciosUsados-1];
}


template <class T>
int ArbolB<T>::getSiguiente(Nodo<T> & padre, int i){
    Nodo<T> hijo = carga(padre.hijos[i+1]);
    while(!hijo.leaf)
        hijo = carga(hijo.hijos[0]);
    return hijo.info[0];
}

template <class T>
void ArbolB<T>::fill(Nodo<T> & nodo,int i){
    Nodo<T> hijo = carga(nodo.hijos[i-1]);
    Nodo<T> hijoHermano = carga(nodo.hijos[i+1]);
    if(i != 0 && hijo.espaciosUsados >= orden)
        prestadoAnterior(nodo,i);
    else if(i != nodo.espaciosUsados && hijoHermano.espaciosUsados >= orden)
        prestadoSiguiente(nodo,i);
    else{
        if(i != nodo.espaciosUsados)
            unir(nodo,i);
        else
            unir(nodo,i-1);
    }
    
}

template <class T>
void ArbolB<T>::prestadoAnterior(Nodo<T> & padre,int i){
    Nodo<T> hijo = carga(padre.hijos[i]);
    Nodo<T> hijoHermano = carga(padre.hijos[i-1]);
    
    for(int j = hijo.espaciosUsados; j>= 0;j--)
        hijo.info[j+1] = hijo.info[j];
    if(!hijo.leaf){
        for(int j = hijo.espaciosUsados; j>=0; j--)
            hijo.hijos[j+1] = hijo.hijos[j];
    }
    hijo.info[0] = padre.info[i-1];
    //hijo
    if(!padre.leaf)
        hijo.hijos[0] = hijoHermano.hijos[hijoHermano.espaciosUsados];
    
    padre.info[i-1] = hijoHermano.info[hijoHermano.espaciosUsados-1];
    
    hijo.espaciosUsados++;
    hijoHermano.espaciosUsados--;
    
    save(padre);
    save(hijo);
    save(hijoHermano);
    
    
    
}

template <class T>
void ArbolB<T>::prestadoSiguiente(Nodo<T> & padre,int i){
    Nodo<T> hijo = carga(padre.hijos[i]);
    Nodo<T> hijoHermano = carga(padre.hijos[i+1]);
    
    hijo.info[hijo.espaciosUsados] = padre.info[i];
    
    if(!hijo.leaf)
        hijo.hijos[hijo.espaciosUsados+1] = hijoHermano.hijos[0];
    
    
    padre.info[i] = hijoHermano.info[0];
    
    for(int j = 1 ; j < hijoHermano.espaciosUsados;j++)
        hijoHermano.info[j-1] = hijoHermano.info[j];
    
    if(!hijoHermano.leaf){
        for(int j = 1; j <= hijoHermano.espaciosUsados; j++)
            hijoHermano.hijos[j-1] = hijoHermano.hijos[j];
    }
    
    
    hijo.espaciosUsados++;
    hijoHermano.espaciosUsados--;
    
    save(padre);
    save(hijo);
    save(hijoHermano);
    
}

template <class T>
void ArbolB<T>::unir(Nodo<T> & padre, int i){
    Nodo<T> hijo = carga(padre.hijos[i]);
    Nodo<T> hijoHermano = carga(padre.hijos[i+1]);
    hijo.info[orden-1] = padre.info[i];
    
    for (int j=0; j<hijoHermano.espaciosUsados; j++)
        hijo.info[j+orden] = hijoHermano.info[j];
    
    
    if (!hijo.leaf){
        for(int j=0; j<=hijoHermano.espaciosUsados; j++)
            hijo.hijos[j+orden] = hijoHermano.hijos[j];
    }
    
    
    for (int j=i+1; j<padre.espaciosUsados; j++)
        padre.info[j-1] = padre.info[j];
    
    
    for (int j=i+2; j<=padre.espaciosUsados; j++)
        padre.hijos[j-1] = padre.hijos[j];
    
    hijo.espaciosUsados += hijoHermano.espaciosUsados+1;
    padre.espaciosUsados--;
    
    save(padre);
    save(hijo);
    save(hijoHermano);
    
}

template <class T>
void ArbolB<T>::Buscar(T dato){
    Nodo<T> root = carga(getRoot());
    buscarDato(root, dato);
}

template <class T>
void ArbolB<T>::buscarDato(Nodo<T> & nodo, T dato){
    int i = 0;
    while(i < nodo.espaciosUsados && dato > nodo.info[i])
        i++;
    if (dato == nodo.info[i]){
        cout << "Se encontro dato " << dato << " en el nodo " << nodo.llave << " en la posicion " << i << endl;
    }
    else if (nodo.leaf){
        cout << "No se encontro dato " << dato << " en el arbol." << endl;
    }
    else{
        Nodo<T> hijo = carga(nodo.hijos[i]);
        buscarDato(hijo, dato);
    }
}




template <class T>
void ArbolB<T>::Insertar(T dato){
    Nodo<T> root = carga(getRoot());
    if(root.checkFull(orden)){
        Nodo<T> nodoPadre(orden);
        nodoPadre.llave = currentID;
        setRoot(currentID);
        nodoPadre.leaf = false;
        nodoPadre.espaciosUsados = 0;
        nodoPadre.hijos[0] = root.llave;
        nodoPadre.padre = nodoPadre.llave;
        currentID++;
        divideNodo(nodoPadre, 0, root);
        insertarDato(nodoPadre, dato);
    }
    else{
        insertarDato(root, dato);
        
    }
}

template <class T>
void ArbolB<T>::insertarDato(Nodo<T> & nodo,T dato){
    int i = nodo.espaciosUsados-1;
    if(nodo.leaf){
        while (i >= 0 && dato < nodo.info[i]){
            nodo.info[i+1] = nodo.info[i];
            i--;
        }
        nodo.info[i+1] = dato;
        nodo.espaciosUsados++;
        save(nodo);
        
    }
    else{
        while (i >= 0 && dato < nodo.info[i]){
            i--;
        }
        i ++;
        Nodo<T> nodoHijo = carga(nodo.hijos[i]);
        if(nodoHijo.checkFull(orden)){
            divideNodo(nodo, i, nodoHijo);
            if(dato > nodo.info[i]){
                i++;
                nodoHijo = carga(nodo.hijos[i]);
            }
        }
        insertarDato(nodoHijo, dato);
    }
}

template <class T>
void ArbolB<T>::divideNodo(Nodo<T> & nodoPadre,int i,Nodo<T> & nodo){
    nodo.padre = nodoPadre.llave;
    Nodo<T> nodoHermano(orden);
    nodoHermano.llave = currentID;
    nodoHermano.padre = nodoPadre.llave;
    currentID++;
    nodoHermano.leaf = nodo.leaf;
    int div = orden-1;
    nodoHermano.espaciosUsados = div;
    
    for(int j = 0; j < div; j++){
        nodoHermano.info[j] = nodo.info[j+orden];
    }
    if (!nodo.leaf){
        for(int j = 0; j < div+1; j++){
            nodoHermano.hijos[j] = nodo.hijos[j+orden];
        }
    }
    nodo.espaciosUsados = div;
    
    for (int j = nodoPadre.espaciosUsados+1; j >= i+1;j--){
        nodoPadre.hijos[j+1] = nodoPadre.hijos[j];
    }
    
    nodoPadre.hijos[i+1] = nodoHermano.llave;
    
    for (int j = nodoPadre.espaciosUsados; j >= i; j--){
        nodoPadre.info[j] = nodoPadre.info[j-1];
    }
    
    nodoPadre.info[i] = nodo.info[orden-1];
    nodoPadre.espaciosUsados++;
    
    
    save(nodo);
    save(nodoPadre);
    save(nodoHermano);
    
    
    
}

template <class T>
void ArbolB<T>::printNodos(){
    Nodo<T> root = carga(getRoot());
    print(root);
    cout << endl;
}

template <class T>
void ArbolB<T>::printAsc(){
    Nodo<T> root = carga(getRoot());
    asc(root);
    cout << endl;
}

template <class T>
void ArbolB<T>::printDesc(){
    Nodo<T> root = carga(getRoot());
    desc(root);
    cout << endl;
}

template <class T>
void ArbolB<T>::print(Nodo<T> & nodo){
    Nodo<T> hijo(orden);
    if(nodo.leaf)
        nodo.print(orden);
    else{
        nodo.print(orden);
        for(int i = 0; i<= nodo.espaciosUsados; i++){
            hijo = carga(nodo.hijos[i]);
            print(hijo);
        }
    }
}

template <class T>
void ArbolB<T>::asc(Nodo<T> & nodo){
    Nodo<T> hijo(orden);
    int i;
    for(i = 0; i < nodo.espaciosUsados; i++){
        if(!nodo.leaf){
            hijo = carga(nodo.hijos[i]);
            asc(hijo);
        }
        cout << " " << nodo.info[i];
    }
    if(nodo.leaf == false){
        hijo = carga(nodo.hijos[i]);
        asc(hijo);
    }
}

template <class T>
void ArbolB<T>::desc(Nodo<T> & nodo){
    Nodo<T> hijo(orden);
    int i;
    for(i = nodo.espaciosUsados; i > 0; i--){
        if(!nodo.leaf){
            hijo = carga(nodo.hijos[i]);
            desc(hijo);
        }
        cout << " " << nodo.info[i-1];
    }
    if(nodo.leaf == false){
        hijo = carga(nodo.hijos[i]);
        desc(hijo);
    }
}

template <class T>
void ArbolB<T>::setData(){
    //    int totalNodos = 0;
    int root = 0;
    data.open("data.dat");
    data.seekp(0);
    //    data.write(reinterpret_cast<char*>(&totalNodos), sizeof(int));
    data.write(reinterpret_cast<char*>(&root), sizeof(int));
}

template <class T>
int ArbolB<T>::getRoot(){
    int root;
    data.seekg(0);
    data.read(reinterpret_cast<char*>(&root), sizeof(int));
    return root;
}

template <class T>
void ArbolB<T>::setRoot(int rootID){
    data.seekp(0);
    data.write(reinterpret_cast<char*>(&rootID), sizeof(int));
}

template <class T>
int ArbolB<T>::cantidadNodos(){
    int totalNodos;
    data.seekg(0);
    data.read(reinterpret_cast<char*>(&totalNodos), sizeof(int));
    return totalNodos;
}


template <class T>
void ArbolB<T>::updateTotal(int cantidad){
    int total;
    data.seekg(0);
    data.read(reinterpret_cast<char*>(&total), sizeof(int));
    total += cantidad;
    data.seekp(0);
    data.write(reinterpret_cast<char*>(&total), sizeof(int));
}


template <class T>
void ArbolB<T>::save(Nodo<T> & nodo){
    data.seekp(sizeof(int)+nodo.llave*sizeof(Nodo<T>));
    data.write(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
}

template <class T>
Nodo<T>  ArbolB<T>::carga(int llaveDeCarga){
    Nodo<T> nodo(orden);
    data.seekg(sizeof(int)+llaveDeCarga*sizeof(Nodo<T>));
    data.read(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
    return nodo;
    
}


template <class T>
ArbolB<T>::~ArbolB(){
    data.close();
}
main(){
	int t1,t2,tiempo;//para la función de tiempo 


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
			t1=clock();
			if (Busqueda(tree, num) == NILPTR){
				printf("%d no encontrado\n", num);
			}
			else
				printf("%d Encontrado\n", num);
			t2=clock();
			 tiempo=getMilisegundos(t2-t1);
 				printf(" Tiempo = [ %d ] ", tiempo);
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

#endif /* ArbolB_h */