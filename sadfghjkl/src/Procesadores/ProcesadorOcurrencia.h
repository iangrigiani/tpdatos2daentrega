#ifndef PROCESADOROCURRENCIA_H_
#define PROCESADOROCURRENCIA_H_

#include "../Parser/Parser.h"
#include "../Comunes/Ocurrencia.h"
#include "../Comunes/Termino.h"
#include "../Handlers/HandlerFrecGlobalTerminos.h"


class ProcesadorOcurrencia {

private:
		int cantidadTerminos;
		int* idTerminos;
		void getOcurrencias(list<string> palabras, list<Ocurrencia> & ocurrencias);
		Termino agregarTermino(string palabraActual);
		void insertarIdTermino(int idTermino);
public:
		ProcesadorOcurrencia();
		list<Ocurrencia> obtenerOcurrencias (list<string> palabras);
		virtual ~ProcesadorOcurrencia();
};

#endif /* PROCESADOROCURRENCIA_H_ */
