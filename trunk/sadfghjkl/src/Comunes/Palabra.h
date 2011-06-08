/*
 * Palabra.h
 *
 *  Created on: 08/06/2011
 *      Author: catu
 */

#ifndef PALABRA_H_
#define PALABRA_H_

#include <list>
#include <string>
#include "Aparicion.h"
using namespace std;

class Palabra{


private:

	string palabra;
	list<Aparicion> apariciones;

public:

	Palabra(){

	}

	Palabra(string palabra, list<Aparicion> apariciones){
		this->palabra = palabra;
		this->apariciones = apariciones;
	}

	virtual ~Palabra(){
	}

	string getPalabra () const {
		return this->palabra;
	}

	void setPalabra(string palabra)
	{
		this->palabra = palabra;

	}

	list<Aparicion> getApariciones()
	{
		return this->apariciones;

	}

	void setApariciones(list<Aparicion> apariciones){
		this->apariciones = apariciones;
	}

	void agregarApariciones(list<Aparicion> & apariciones)
	{
		list < Aparicion > ::iterator it;
		for (it = apariciones.begin(); it != apariciones.end(); ++ it)
			this->apariciones.push_back(*it);
	}

	void agregarAparicion(Aparicion & aparicion)
	{
		this->apariciones.push_back(aparicion);
	}

	list<int> obtenerDocumentos()
	{
		list<int> documentos;

		list<Aparicion> :: iterator itApariciones = this->apariciones.begin();

		while(itApariciones != this->apariciones.end())
		{
			Aparicion aparicionActual = *itApariciones;
			documentos.push_back(aparicionActual.getIdDocumento());
			++itApariciones;
		}

		return documentos;
	}

};

#endif /* PALABRA_H_ */
