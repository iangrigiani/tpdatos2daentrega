/*
 * Ocurrencia.cpp
 *
 *  Created on: 22/05/2011
 *      Author: catu
 */

#include "Ocurrencia.h"


Ocurrencia::Ocurrencia()
{
	this->codigoGammaDocumento = "";
	this->idPalabra = 0;
	this->palabra = "";
	this->idDocumento = 0;
}

int Ocurrencia::getIdPalabra()
{
	return this->idPalabra;
}

void Ocurrencia::setIdPalabra(int idPalabra)
{
	this->idPalabra = idPalabra;
}

string Ocurrencia::getPalabra()
{
	return this->palabra;

}

void Ocurrencia::setPalabra(string palabra)
{
	this->palabra = palabra;
}


string Ocurrencia::getCodigoGammaDocumento()
{
	return this->codigoGammaDocumento;
}

void Ocurrencia::setCodigoGammaDocumento(string idDocumento)
{
	this->codigoGammaDocumento = idDocumento;
}


int Ocurrencia::getIdDocumento()
{
	return this->idDocumento;
}

void Ocurrencia::setIdDocumento(int idDocumento)
{
	this->idDocumento = idDocumento;
}


list<int>  Ocurrencia::getPosiciones()
{
	return this->posiciones;
}



void Ocurrencia::setPosiciones(list<int> posiciones)
{
	this->posiciones = posiciones;

}

void Ocurrencia::agregarPosicion(int  posicion)
{
	this->posiciones.push_back(posicion);
}


void Ocurrencia::agregarPosiciones(list < int > & posiciones) {
	list < int > ::iterator it;
	for (it = posiciones.begin(); it != posiciones.end(); ++ it)
		this->posiciones.push_back(*it);
}


