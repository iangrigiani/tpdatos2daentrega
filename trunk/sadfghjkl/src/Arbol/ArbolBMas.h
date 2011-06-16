
#ifndef _ARBOLBMAS_H_
#define _ARBOLBMAS_H_

#include "../EstructurasArbol/Elementos.h"
#include "NodoInterior.h"
#include "../Persistencia/PersistorArbol.h"
#include "../EstructurasArbol/Solucion.h"
#include <fstream>
#include <vector>
#include <list>

using namespace std;


class ArbolBMas {

	friend class Nodo;
	friend class NodoInterior;
	friend class NodoHoja;

private:
	Nodo* raiz;
	int primeraHoja;
	int cantidadNodos;
	string pathId;
	int tipoDeArbol; // 1 es arbol primario, 2 es secundario
	vector<int> nodosLibres;
	PersistorArbol* persistor;

	Clave ultimaClave;
	enum enumReturn {RESULTADO_OK = 0, NO_ENCONTRADO = 1, ACTUALIZAR_ULTIMA_CLAVE = 2, FUSION = 4} flags;

public:

	ArbolBMas(string ruta_archivo,string ruta_Contador, int tipoDeArbol);

	~ArbolBMas();
	int insertar(Elementos* registro, bool incrementarID);

	bool modificar(Elementos* registro);

	bool incrementarID(Elementos* elemento, int& frecuencia);

	bool decrementarID(Elementos* elemento);
	//	IteradorArbolBMas* begin();

	/*
	 * Primitiva que va a buscar una clave o cadena de caracteres en la estructura o archivo
	 * Pre: Recibo la clave del registro a buscar.
	 * Pos: Si lo encontro, devuelve el registro, sino, devuelve NULL.
	 */
//	pair<Elementos*, IteradorArbolBMas*> buscar(Clave clave);

	bool borrar(Elementos* elemento);

	void mostrar();

	Nodo* leerNodo(int numeroDeNodo);

	int getCantidadBloques();

	void buscar(list<Elementos*>* listaElementos, Clave* clave);

private:

	void llenarListadeBusqueda(list<Elementos*>* listaElementos, NodoHoja* nodo, int posicion, Clave* clave);

	bool claveMenor(Clave clave1, Clave clave2);

	bool claveMenorIgual(Clave clave1, Clave clave2);

	bool claveIgual(Clave clave1, Clave clave2);

	NodoHoja* crearNodoHoja();

	NodoInterior* crearNodoInterior(int nivel);

	void liberarMemoriaNodo(Nodo *unNodo);

	int obtenerPosicion(Nodo *unNodo, Clave clave);

	bool insertarRecursivo(Nodo* nodoCorriente, Clave clave, Persistencia dato, Persistencia id,  Clave* clavePromocion, Nodo** nuevoNodo, Persistencia* idInsertado, bool incrementarID);

	void dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja);

	void dividirNodoInterior(NodoInterior* unNodoInterior, Clave* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion);

	int borrarRecursivo(Elementos* elem, Clave clave, Nodo *nodoCorriente, Nodo *nodoIzquierda, Nodo *nodoDerecha,
			NodoInterior *nodoPadreIzquierda, NodoInterior *nodoPadreDerecha, NodoInterior *nodoPadre, int posicionPadre);

	int fusionarHojas(NodoHoja* hojaIzquierda, NodoHoja* hojaDerecha);

	int fusionarNodosInteriores(NodoInterior* nodoIzquierda, NodoInterior* nodoDerecha, NodoInterior* nodoPadre, int posicionPadre);

	int pasarElementosHojaIzquierda(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void pasarElementosNodoInteriorIzquierdo(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void pasarElementosHojaDerecha(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void pasarElementosNodoInteriorDerecho(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre);

	void persistirNodo(Nodo* unNodo);

	Nodo* hidratarNodo(int numeroDeNodo);

	int obtenerNumeroDeNodo();

	void persistirDatosConfiguracion();

	void hidratarDatosConfiguracion();

	void toString(Nodo* nodoAmostrar, int tab, ofstream& fo);

	void refactorizarNodoFrontCoding(NodoHoja** nodoHojaCorriente);

	void refactorizarNodoNoHojaFrontCoding(Nodo** nodo);

	void sacarFrontCodingNodo (Nodo ** nodo);

	void sacarFrontCodingNodoHoja (NodoHoja ** nodo);

	Solucion buscarSecuencialClave(int nodo, Elementos* elemento, int posicion);

	Persistencia obtenerNuevoId(string path);

};

#endif // _ARBOLBMAS_H_
