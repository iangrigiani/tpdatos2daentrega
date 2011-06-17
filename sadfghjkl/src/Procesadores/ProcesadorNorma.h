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

	/*
	 * Se usa para consultar la norma de un Documento
	 * PRE: Recibe por parámetro el id del documento
	 * POS: idTermino del término más frecuente en documento idDocumento guardado
	 */
	void guardarIDTerminoFrecuente(int idDocumento, int idTermino);

	/*
	 * Se usa para consultar la norma de un Documento
	 * PRE: Recibe por parámetro el id del documento
	 * POS: Devuelve el valor de la norma
	 */
	int consultarNorma(int idDocumento);

	/*
	 * Se usa para borrar el id de un Documento cuando este documento (libro) se elimina
	 * PRE: Recibe por parámetro el id del documento
	 * POS:
	 */
	void eliminarIDTerminoFrecuente(int idDocumento);


	/* Actualiza el arbol de frecuencias incrementando en 1 el valor del peso que estaba
	 * guardado para cada IDTermino del vector idTerminos.
	 * PRE: -
	 * POS: Archivo de frecuencias actualizado.
	 */
	void actualizarPesos(int idDocumento, int* lista, int tamanioLista);

	/* Actualiza el arbol de frecuencias incrementando en 1 el valor del peso que estaba
	 * guardado para el IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Archivo de frecuencias actualizado.
	 */
	int  incrementarPesoTermino(int IDTermino);


	/* Busca en el arbol de frecuencias el valor del peso que esta
	 * guardado correspondiente al IDTermino pasado.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Devuelve OK o error según haya tenido éxito o no la operación
	 */
	int  buscarPesoTermino(int IDTermino);

	/* Actualiza el arbol de frecuencias decrementando en 1 el valor del peso que estaba
	 * guardado para el IDTermino pasado.
	 * Se usa al eliminar un libro.
	 * PRE: Recibe un int con el IDTermino.
	 * POS: Archivo de frecuencias actualizado.
	 */
	int  decrementarPesoTermino (int IDTermino);

private:

	CalculadorDePesoGlobal* calc;
	string intToString(int integer);

};
#endif /* PROCESADORNORMA_H_ */
