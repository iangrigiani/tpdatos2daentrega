#ifndef PARSERDELIBROS_H_
#define PARSERDELIBROS_H_
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <sstream>
#include "../EstructurasEnComun/Constantes.h"
#include <vector>
using namespace std;

class ParserDeLibros {
public:
private:
	vector<string> listaStopWords;
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

	/*
	 * Obtiene desde archivo la lista de stopWords
	 * pre: -
	 * post: lista obtenida
	 */
	void obtenerListaStopWords();

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

	void mostrarLista(){
		vector<string>::iterator it = this->listaStopWords.begin();
		while ( it != this->listaStopWords.end()){
			cout << (*it) << endl;
			++it;
		}
	}

	list<string> obtenerPalabrasDeLibro(char* libro);
	list < string > obtenerDatos(char* cadena, bool filtrar);

	/*
	 * Se fija en la lista de stopWords si la palabra correspondiente
	 * es o no un stopWord
	 * pre: pasar una palabra. Debe existir la lista de stopWords
	 * post: Retorna true, si la palabra se encuentra en la lista.
	 */
	bool esStopWords(char* pch);

};

#endif /* PARSERDELIBROS_H_ */
