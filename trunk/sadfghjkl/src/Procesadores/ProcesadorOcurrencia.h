#ifndef PROCESADOROCURRENCIA_H_
#define PROCESADOROCURRENCIA_H_

#include "../Parser/Parser.h"
#include "../Comunes/Ocurrencia.h"
#include "../Comunes/Termino.h"
#include "../Procesadores/ProcesadorNorma.h"


class ProcesadorOcurrencia {

private:
		int cantidadTerminos;
		int* idTerminos;
		void getOcurrencias(list<string> palabras, vector<Ocurrencia> & ocurrencias, int idDocumento);
		void insertarBinarioOcurrencia(string palabraActual, int iteracion, int idTermino, vector<Ocurrencia> & ocurrencias);
		Termino agregarTermino(string palabraActual);
		void insertarIdTermino(int idTermino);
public:
		ProcesadorOcurrencia();
		vector<Ocurrencia> obtenerOcurrencias (list<string> palabras, int idDocumento);
		virtual ~ProcesadorOcurrencia();
};

#endif /* PROCESADOROCURRENCIA_H_ */
