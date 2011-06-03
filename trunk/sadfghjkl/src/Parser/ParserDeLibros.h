#ifndef PARSERDELIBROS_H_
#define PARSERDELIBROS_H_
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "../Comunes/Constantes.h"
#include "../Comunes/RegistroLibro.h"
#include "Parser.h"
#include <vector>
using namespace std;

class ParserDeLibros : public virtual Parser {

private:

	char * libroActual;
	/*
	 * Arma la cadena de match para el autor
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerAutor();
	/*
	 * Arma la cadena de match para el titulo
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerTitulo();
	/*
	 * Arma la cadena de match para la editorial
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerEditorial();
	/*
	 * Arma la cadena de match para las palabras
	 * pre: -
	 * post: genera la cadena y se fija el match
	 */
	char * obtenerPalabras();
	/*
	 * Encuentra el primer match que cumple según las
	 * características de la expresión regular pasada como patrón
	 * pre: pasar patrón de match
	 * post: genera la cadena obtenida
	 */
	char * obtenerPrimerMatch(char * string, char * patronDeFiltro, int size);

	void downCase(string& str);

public:

	ParserDeLibros();
	virtual ~ParserDeLibros();
	/*
	 * Metodo que se le pasa el buffer con el libro y devuelve el parseo
	 * en un registro.
	 * pre: pasar el registro
	 * post: parsea y contruye el registro a devolver.
	 */
	void obtenerRegistroDeLibro(char * libro, RegistroLibro& reg);

//	void mostrarLista(){
//		vector<string>::iterator it = this->listaStopWords.begin();
//		while ( it != this->listaStopWords.end()){
//			cout << (*it) << endl;
//			++it;
//		}
//	}

	list<string> obtenerPalabrasDeLibro(char* libro);
	list < string > obtenerDatos(char* cadena, bool filtrar);

};

#endif /* PARSERDELIBROS_H_ */
