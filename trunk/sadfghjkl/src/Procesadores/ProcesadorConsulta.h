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
#include "../Handlers/HandlerArchivoOcurrencias.h"
#include "../Hash/HashPalabra.h"


using namespace std;

class ProcesadorConsulta {

private:

		Palabra compararApariciones(Palabra palabra1,Palabra palabra2);

		/*
		 * Crea una aparicion a partir de dos apariciones existentes.
		 */
		void crearAparicion(Aparicion aparicion1, Aparicion aparicion2, Aparicion & nuevaAparicion, string palabra1, string palabra2);




		/*
		 * Procesar consulta puntual de Palabra
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultaPuntualPalabra(string palabra);

		void filtrarProximidad(Palabra & palabra);

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
		 * pre:obtener las ocurrencias asociadas a las palabras
		 * pos : devuelve la lista de offset al archivo RLV.
		 */
		list<int> consultarPalabras(list<string> palabras);

		Palabra procesarApariciones(list<Palabra> palabras);


};

#endif /* PROCESADORCONSULTA_H_ */
