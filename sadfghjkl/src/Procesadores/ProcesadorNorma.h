#ifndef PROCESADORNORMA_H_
#define PROCESADORNORMA_H_
class ArbolBMas;
class HashTitulo;
#include <fstream>
#include <list>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include "../NormasAInfinito/CalculadorDePesoGlobal.h"
#include "../Arbol/ArbolBMas.h"
#include "../Hash/HashTitulo.h"

using namespace std;

class ProcesadorNorma{
public:
	/* -------- Constructor y Destructor ---------*/
	ProcesadorNorma();
	virtual ~ProcesadorNorma();

	/* Actualiza el archivo de normas incrementando en 1 el valor del peso que estaba
	 * guardado en el archivo para cada IDTermino del vector idTerminos.
	 * PRE: -
	 * POS: Archivo de normas actualizado.
	 */
	void actualizarPesosYNormas(int idDocumento, int* lista, int tamanioLista);


	/* Actualiza el archivo de normas incrementando en 1 el valor del peso que estaba
	 * guardado en el archivo para el IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Archivo de normas actualizado.
	 */
	int incrementarPesoTermino (int IDTermino);

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

	/*
	 * Se usa para borrar la norma de un Documento cuando este documento (libro) se elimina
	 * PRE: Recibe por parámetro el id del documento
	 * POS:
	 */
	void eliminarNormaGuardada(int idDocumento);
	/*
	 * Se usa para consultar la norma de un Documento
	 * PRE: Recibe por parámetro el id del documento
	 * POS:
	 */
	float consultarNorma(int idDocumento);

private:
//	ArbolBMas* arbolPesos;
	CalculadorDePesoGlobal* calc;
//	vector<int> idTerminos;
	string intToString(int integer);
	void persistirNorma(int idDocumento, float norma);
//	string lineaArchivoNorma(int idDocument, float norma);
};
#endif /* PROCESADORNORMA_H_ */
