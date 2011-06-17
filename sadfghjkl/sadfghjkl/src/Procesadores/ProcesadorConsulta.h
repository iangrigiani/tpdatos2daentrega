#ifndef PROCESADORCONSULTA_H_
#define PROCESADORCONSULTA_H_

#include <string.h>
#include "../Comunes/Palabra.h"
#include "../Comunes/Aparicion.h"
#include "../Comunes/Posicion.h"
#include "../Comunes/Distancia.h"
#include "../Arbol/ArbolBMas.h"
#include "../Handlers/HandlerArchivoOcurrencias.h"
#include "../Hash/HashPalabra.h"
#include "../Hash/HashTitulo.h"
#include "../Procesadores/ProcesadorNorma.h"
#include <math.h>
//using namespace std;

class ProcesadorConsulta {

private:

		/*
		 * Compara dos palabras y crea una nueva con las coincidencias.
		 */
		Palabra compararApariciones(Palabra palabra1,Palabra palabra2);

		/*
		 * Crea una aparicion a partir de dos apariciones existentes.
		 */
		void crearAparicion(Aparicion aparicion1, Aparicion aparicion2, Aparicion & nuevaAparicion);


		/*
		 * Procesa todas las palabras recibidas por parametro y devuelve una sola con
		 * las coincidencias.
		 */
		Palabra procesarApariciones(list<Palabra> palabras);


		void actualizarApariciones(int idDocumento,list<Posicion> posiciones, list<Aparicion> & aparicionesActualizadas);


		/*
		 * Procesa todas las posiciones recibidas por parametros y devuelve un entero}
		 * que representa la distancia minima de las mismas
		 */
		int procesarPosiciones(list<Posicion> & posiciones);

		/*
		 * Crea a partir de dos palabras con su correspondiente posicion una nueva posicion y la agrega a la lista
		 * de posiciones recibida por parametro.
		 */
		void crearPosicionesNuevas(string palabra1,int posicion1, string palabra2,int posicion2, list<Posicion> & posicionesMinimas);


		/*
		 * Compara los elementos de una lista de enteros que representan las posiciones
		 * de las palabras en el libro y devuelve la distancia minima entre ellas.
		 */
		int compararPosiciones(list<int> posiciones);

		/*
		 * Compara dos posiciones y agrega las minimas distancias a la lista de posiciones recibida por parametro
		 * y devuelve una nueva posicion con la minima correspondiente a la segunda palabra.
		 */
		Posicion compararPosiciones(Posicion posicionActual, Posicion posicionSiguiente, list<Posicion> & posicionesMinimas);

		/*
		 * Agrega todas las posiciones que se encuentran en posicion a la lista de posiciones
		 * que recibe por parametro.
		 */
		void filtrarPosiciones(list<int> & posiciones,Posicion posicion);

		/*
		 * Procesar consulta puntual de Palabra
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultaPuntualPalabra(string palabra);


		/*
		 * Compara dos distancias y crea una nueva con la minima.
		 */
		Distancia compararDistancias(Distancia distancia1,Distancia distancia2);

		/*
		 * Filtra las distancias
		 */
		Palabra filtrarDistancias(list<Distancia> distancias, Palabra palabra, list<int> & documentosCoincidentes);

		Palabra filtrarDocumentos(Distancia distancia, Palabra  palabra);

		Palabra filtrarProximidad(Palabra palabra,list<int> & documentos);

		list<int> filtrarRanqueada(Palabra palabra);
public:

		ProcesadorConsulta();
		virtual ~ProcesadorConsulta();

		/*
		 * Procesar consulta puntual de Autor
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultaAutor(string autor);

		/*
		 * Procesar consulta puntual de Editorial
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultaEditorial(string editorial);

		/*
		 * Procesar consulta puntual de Editorial
		 * pre: hacer la funcion de hashing
		 * pos: devuelve el offset al archivo RLV.
		 */
		int consultaTitulo(string titulo);


		/*
		 * Procesar consulta de Palabras
		 * pre: obtener las ocurrencias asociadas a las palabras
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultaPalabras(list<string> palabras);


};

#endif /* PROCESADORCONSULTA_H_ */
