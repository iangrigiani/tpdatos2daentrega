/*
 * ProcesadorConsulta.h
 *
 *  Created on: 01/06/2011
 *      Author: catu
 */

#ifndef PROCESADORCONSULTA_H_
#define PROCESADORCONSULTA_H_

#include <string.h>
#include "../Comunes/Palabra.h"
#include "../Comunes/Aparicion.h"
#include "../Comunes/Posicion.h"
#include "../Comunes/Distancia.h"
#include "../Handlers/HandlerArchivoOcurrencias.h"
#include "../Hash/HashPalabra.h"
#include <math.h>


using namespace std;

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


		/*
		 * Procesa todas las posiciones recibidas por parametros y devuelve un entero}
		 * que representa la distancia minima de las mismas
		 */
		int procesarPosiciones(list<Posicion> posiciones);

		/*
		 * Compara los elementos de una lista de enteros que representan las posiciones
		 * de las palabras en el libro y devuelve la distancia minima entre ellas.
		 */
		int compararPosiciones(list<int> posiciones);

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
		 * pre: recibe una lista de distancias.
		 * post: devuelve una lista de documentos, aquellos que tienen la menor distancia.
		 */
		list<int> filtrarDistancias(list<Distancia> distancias);

		list<int> filtrarProximidad(Palabra & palabra);

		void filtrarRanqueada(Palabra & palabra);
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
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultaTitulo(string titulo);


		/*
		 * Procesar consulta de Palabras
		 * pre: obtener las ocurrencias asociadas a las palabras
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultarPalabras(list<string> palabras);

};

#endif /* PROCESADORCONSULTA_H_ */
