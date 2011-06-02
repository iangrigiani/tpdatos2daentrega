#ifndef PROCESADOROCURRENCIA_H_
#define PROCESADOROCURRENCIA_H_
#include "../ParserLibros/ParserDeLibros.h"
#include "../EstructurasEnComun/Ocurrencia.h"
#include "../EstructurasEnComun/Termino.h"
class ProcesadorOcurrencia {

private:
	void getOcurrencias(list<string> palabras, list<Ocurrencia> & ocurrencias);
	Termino agregarTermino(string palabraActual);
public:
	ProcesadorOcurrencia();
	list<Ocurrencia> obtenerOcurrencias (list<string> palabras);
	virtual ~ProcesadorOcurrencia();
};

#endif /* PROCESADOROCURRENCIA_H_ */
