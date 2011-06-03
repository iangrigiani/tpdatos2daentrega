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
		list<int> procesarApariciones(list<Aparicion> apariciones);
		list<int> compararApariciones(list<int> documentos1,list<int> documentos2);
public:

		ProcesadorConsulta();
		virtual ~ProcesadorConsulta();
		list<int> consultarPalabras(list<string> palabras);
};

#endif /* PROCESADORCONSULTA_H_ */
