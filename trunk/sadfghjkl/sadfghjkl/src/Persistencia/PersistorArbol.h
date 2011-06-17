
#ifndef PERSISTORARBOL_H_
#define PERSISTORARBOL_H_
#include "Persistencia.h"
#include "../Handlers/HandlerBloques.h"
#include <string.h>
#include <fstream>

class PersistorArbol {
private:
//	fstream archivo;
	HandlerBloques * handlerBloque;
	string rutaOut;
	string ruta;
	int tamanioBloque;

public:
	/*
	 * Constructor
	 */
	PersistorArbol(string ruta, int tamanioBloque);

	/*
	 * Metodo que sirve para guardar un bloque en el archivo
	 * Pre:
	 * Pos:
	 */
	bool guardarBloque (int nroBloque, Persistencia cadena);

	/*
	 * Metodo que sirve para leer un bloque del archivo
	 * Pre: El numero de bloque debe ser valido
	 * Pos: Devuelve una el bloque leido en una "CadenaBytes".
	 * 		Si el numero de bloque es invalido o no se puede realizar la lectura
	 * 		se retorna un objeto "CadenaBytes" vacio
	 */
	Persistencia leerBloque (int nroBloque);

	int getTamanioArchivo();

	int getCantidadBloques();

	string getRuta();

	/*
	 * Destructor
	 */
	virtual ~PersistorArbol();
};

#endif /* PERSISTORARBOL_H_ */
