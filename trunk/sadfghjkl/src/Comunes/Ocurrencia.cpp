
#include "Ocurrencia.h"


Ocurrencia::Ocurrencia()
{
	this->idDocumento = 0;
	this->idPalabra = 0;
	this->palabra = "";
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
