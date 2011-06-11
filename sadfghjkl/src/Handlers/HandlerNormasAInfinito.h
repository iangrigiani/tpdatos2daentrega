#ifndef HANDLERNORMASAINFINITO_H_
#define HANDLERNORMASAINFINITO_H_
class ArbolBMas;
#include <fstream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "../EstructurasArbol/Elementos.h"
#include "../EstructurasArbol/Clave.h"
#include "../Comunes/Constantes.h"
#include "../Arbol/ArbolBMas.h"

using namespace std;

class HandlerNormasAInfinito{
public:
	/* -------- Constructor y Destructor ---------*/
	HandlerNormasAInfinito();
	HandlerNormasAInfinito(vector<int> idTerminos);
	virtual ~HandlerNormasAInfinito();

	/* Actualiza el archivo de normas incrementando en 1 el valor del peso que estaba
	 * guardado en el archivo para cada IDTermino del vector idTerminos.
	 * PRE: -
	 * POS: Archivo de normas actualizado.
	 */
	void actualizarPesosTerminos();


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
	int decrementarPesoTermino (int IDTermino);

	/* Busca en el archivo de normas el valor del peso que esta
	 * guardado en el archivo correspondiente al IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Devuelve OK o error según haya tenido éxito o no la operación
	 */
	int  buscarPesoTermino(int IDTermino);

private:
	ArbolBMas* arbolPesos;
	vector<int> idTerminos;
	string intToString(int integer);
};


#endif /* HANDLERNORMASAINFINITO_H_ */
