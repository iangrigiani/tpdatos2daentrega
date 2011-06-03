/*
 * Aparicion.h
 *
 *  Created on: 01/06/2011
 *      Author: catu
 */

#ifndef APARICION_H_
#define APARICION_H_

#include <list>
#include <string>
using namespace std;

class Aparicion{


private:

	string palabra;
	list<int> documentos;

public:

	Aparicion(){

	}

	Aparicion(string palabra, list<int> documentos){
		this->palabra = palabra;
		this->documentos = documentos;
	}

	virtual ~Aparicion(){
	}

	string getPalabra () const {
		return this->palabra;
	}

	void setPalabra(string palabra)
	{
		this->palabra = palabra;

	}

	list<int> getDocumentos()
	{
		return this->documentos;

	}

	void setDocumentos(list<int> documentos){
		this->documentos = documentos;
	}

};

#endif /* APARICION_H_ */
