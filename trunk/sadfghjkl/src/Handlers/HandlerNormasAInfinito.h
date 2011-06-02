/*
 * HandlerNormasAInfinito.h
 *
 *  Created on: 25/05/2011
 *      Author: andrea
 */

#ifndef HANDLERNORMASAINFINITO_H_
#define HANDLERNORMASAINFINITO_H_

#include <fstream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include "../Comunes/Constantes.h"

using namespace std;

class HandlerNormasAInfinito{
public:
	/* -------- Constructor y Destructor ---------*/
	HandlerNormasAInfinito();
	virtual ~HandlerNormasAInfinito();

	/* Actualiza el archivo de normas incrementando en 1 el valor del peso que estaba
	 * guardado en el archivo para cada IDTermino de la lista.
	 * PRE: Recibe la lista de IDs.
	 * POS: Archivo de normas actualizado.
	 */
	void actualizarPesosTerminos (list<int>& IDsTerminos);


	/* Actualiza el archivo de normas incrementando en 1 el valor del peso que estaba
	 * guardado en el archivo para el IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Archivo de normas actualizado.
	 */
	void incrementarPesoTermino (int IDTermino);

	/* Actualiza el archivo de normas decrementando en 1 el valor del peso que estaba
	 * guardado en el archivo para el IDTermino pasado.
	 * Se usa al eliminar un libro.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Archivo de normas actualizado.
	 */
	void decrementarPesoTermino (int IDTermino);

	/* Busca en el archivo de normas el valor del peso que esta
	 * guardado en el archivo correspondiente al IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Devuelve un entero con el peso.
	 */
	int  buscarPesoTermino(int IDTermino);

private:
	/* Busca en el archivo de normas el valor del peso que esta
	 * guardado en el archivo correspondiente al IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Retorna el offset de Término en el archivo de Normas y
	 *      devuelve por parámetro el pesoTermino
	 */
	int buscarTermino(int IDTermino, int& pesoTermino);

	string crearStringAInsertar(int IDTermino, int pesoTermino);


};


#endif /* HANDLERNORMASAINFINITO_H_ */
