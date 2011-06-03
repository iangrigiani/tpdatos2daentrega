/*
 * Parser.h
 *
 *  Created on: 01/06/2011
 *      Author: catu
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "../Comunes/Constantes.h"

using namespace std;

class Parser {

protected:

	vector<string> listaStopWords;

	/*
	 * Obtiene desde archivo la lista de stopWords
	 * pre: -
	 * post: lista obtenida
	 */
	void obtenerListaStopWords();


public:

	Parser();
	virtual ~Parser();

	/*
	 * Se fija en la lista de stopWords si la palabra correspondiente
	 * es o no un stopWord
	 * pre: pasar una palabra. Debe existir la lista de stopWords
	 * post: Retorna true, si la palabra se encuentra en la lista.
	 */
	bool esStopWords(char* pch);
};

#endif /* PARSER_H_ */
