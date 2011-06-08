/*
 * ProcesadorConsulta.h
 *
 *  Created on: 01/06/2011
 *      Author: catu
 */

#ifndef PROCESADORCONSULTA_H_
#define PROCESADORCONSULTA_H_

#include <string.h>
#include "../Comunes/Aparicion.h"
#include "../Handlers/HandlerArchivoOcurrencias.h"
#include "../Hash/HashPalabra.h"


using namespace std;

class ProcesadorConsulta {

private:
		list<int> compararApariciones(list<int> documentos1,list<int> documentos2);
		list<int> procesarApariciones(list<Aparicion> apariciones);
		/*
		 * Procesar consulta puntual de Palabra
		 * pos: devuelve la lista de offset al archivo RLV.
		 */
		list<int> ConsultaPuntualPalabra(string palabra);

		void filtrarProximidad(list<int>& documentos);

		void filtrarRanqueada(list<int>& documentos);
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


		list<int> consultarPalabras(list<string> palabras);

};

#endif /* PROCESADORCONSULTA_H_ */
