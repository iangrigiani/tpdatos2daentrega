/*
 * Posicion.h
 *
 *  Created on: 08/06/2011
 *      Author: catu
 */

#ifndef POSICION_H_
#define POSICION_H_

#include <list>
#include <string>
using namespace std;

class Posicion {

private:
		string palabra;
		list<int> posiciones;

public:

		Posicion(){}

		Posicion(string palabra, list<int> posiciones)
		{
			this->palabra = palabra;
			this->posiciones = posiciones;

		}

		virtual ~Posicion(){}

		void setPalabra(string palabra)
		{
			this->palabra = palabra;

		}

		string getPalabra()
		{
			return this->palabra;

		}

		list<int> getPosiciones()
		{
			return this->posiciones;

		}

		void agregarPosiciones(list<int> & posiciones)
		{
			list < int > ::iterator it;
			for (it = posiciones.begin(); it != posiciones.end(); ++ it)
				this->posiciones.push_back(*it);
		}

};

#endif /* POSICION_H_ */
