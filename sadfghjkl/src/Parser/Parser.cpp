/*
 * Parser.cpp
 *
 *  Created on: 01/06/2011
 *      Author: catu
 */

#include "Parser.h"

Parser::Parser() {
	this->obtenerListaStopWords();

}

Parser::~Parser() {

}



bool Parser::esStopWords(char* palabra){

	// @Nacho: IMPLEMENTACION CON BUSQUEDA BINARIA

	int totalElem = this->listaStopWords.size();
	int medio, pivotDer, pivotIzq;
	pivotIzq=0;
	pivotDer=totalElem-1;

	stringstream ss;
	ss << palabra;

	string palabraStr = ss.str();

	while ( pivotIzq <= pivotDer) { // el elemento que esta ala izquierda debe de ser menor que el de la derecha
		medio = ( pivotIzq + pivotDer )/2; // calculo el elemento central
		if ( palabraStr > this->listaStopWords[medio] ) // si el elemento buscado es mayor que el centro entonces busco en la segunda mitad del vector
			pivotIzq = medio + 1; // el primer valor del vector pasa hacer la mitad mas 1
		else if ( palabraStr < this->listaStopWords[medio] ) // si el elemento buscado buscado es menor que la mitad entonces buscamos en la primera mitad del vector
			pivotDer = medio - 1;
		else return true; // si encontro la palabra, devuelvo true
	}

	return false;

}

void Parser::obtenerListaStopWords(){
	ifstream fd;
	fd.open(PATH_STOPWORDS, ios_base::in);
	if (!fd.is_open()){
		fd.open(PATH_STOPWORDS, ios_base::out);
		fd.close();
		fd.open(PATH_STOPWORDS, ios_base::in);
	}
	fd.seekg(0, ios_base::end);
	int tamanio = fd.tellg();
	fd.seekg(0, ios_base::beg);
	char* lista = (char*)calloc(tamanio, sizeof(char));
	fd.read(lista, tamanio);
	char * pch;
	pch = strtok (lista,"\n");

	stringstream ss;
	ss << pch;

	this->listaStopWords.push_back(ss.str());
	while (pch != NULL)
	{
		pch = strtok (NULL, "\n");
		if (pch) this->listaStopWords.push_back(pch);
	}
	fd.close();
}

