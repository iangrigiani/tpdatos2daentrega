#ifndef APARICION_H_
#define APARICION_H_

#include <list>
#include <string>
#include "Posicion.h"
using namespace std;

class Aparicion{


private:

		int idDocumento;
		list<Posicion> posiciones;


public:

	Aparicion(){

	}

	Aparicion(int idDocumento, list<Posicion> posiciones){
		this->idDocumento = idDocumento;
		this->posiciones = posiciones;
	}

	virtual ~Aparicion(){

	}


	int getIdDocumento () const {
		return this->idDocumento;
	}

	void setIdDocumento(int idDocumento)
	{
		this->idDocumento = idDocumento;

	}

	list<Posicion> getPosiciones()
	{
		return this->posiciones;

	}


	void agregarPosicion(Posicion & posicion)
	{
		this->posiciones.push_back(posicion);

	}

	void agregarPosiciones(list<int> posiciones, string palabra, int idPalabra)
	{
		Posicion posicion;
		posicion.setPalabra(palabra);
		posicion.agregarPosiciones(posiciones);
		posicion.setIdPalabra(idPalabra);
		this->posiciones.push_back(posicion);


	}

};

#endif /* APARICION_H_ */
