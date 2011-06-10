#ifndef HANDLERARBOL_H_
#define HANDLERARBOL_H_

#include "../Hash/HashPalabra.h"
#include "../Hash/HashTermino.h"
#include "../Arbol/ArbolBMas.h"
#include "HandlerArchivoRLV.h"
#include "HandlerArchivoLog.h"
#include "HandlerArchivoOcurrencias.h"
#include "../Procesadores/ProcesadorOcurrencia.h"
#include "../Parser/ParserDeLibros.h"

#include <list>

class HandlerComandos {

private:
	ParserDeLibros* parser;
	HandlerArchivoRLV* handler;
	HandlerArchivoOcurrencias * handlerOcurrencias;
	HandlerArchivoLog* log;
	ArbolBMas* arbol;
	/*
	 * Crea un arbol del tipo autor o editorial e inserta el elemento
	 * que obtiene del handler de reg de LV correspondiente.
	 */
	void insertarEnArbol (int tipoArbol, int offset);
	bool eliminarEnArbol(int tipoArbol, int offset);

	//int funcion_hash_titulo(const string& str);

	void insertar_en_hash_titulo(int offset);

	void eliminar_de_hash_titulo(int offset);

	list < int > eliminar_repeticion(list < int > & palabras);

	int funcion_hash_palabra(const string& str);

	void insertar_en_hash_palabra(int offset);

	void eliminar_de_hash_palabra(int offset);

public:

	HandlerComandos();

	/*
	 * Toma un path donde se encuentra el libro original guardado, procesa el libro
	 * y lo agrega al Archivo Maestro de libros.
	 * Además, agrega una línea al Archivo de Log con los Flags de indexado en 0
	 * */
	void guardarLibroEnArchivoMaestro(const string& path_nuevo_libro);

	/*
	 * PRE: int parametro ('a'|'e'|'t'|'p')
	 * POS: Agrega segun parametro en el indice correspondiente todos los libros agregados recientemente al Archivo Maestro
	 *
	 * */
	void indexar(int parametro);

	/*
	 * Muestra el log de todos los archivos ingresados recientemente
	 * */
	void listarLibrosIngresados();

	/*
	 * Busca y muestra un libro por ID
	 */
	void obtenerLibro(int IDArchivo);

	/*
	 * Busca un libro por ID y lo elimina del registro maestro y de los 4 índices
	 */
	void quitarLibro(int IDArchivo);

	/*
	 * PRE: int parametro ('a'|'e'|'t'|'p')
	 * POS: Muestra la estructura del indice correspondiente segun el parametro recibido
	 * como texto plano
	 * */
	void verEstructura(int parametro);


	virtual ~HandlerComandos();
};

#endif /* HANDLERARBOL_H_ */
