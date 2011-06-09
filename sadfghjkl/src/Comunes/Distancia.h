/*
 * Distancia.h
 *
 *  Created on: 08/06/2011
 *      Author: catu
 */

#ifndef DISTANCIA_H_
#define DISTANCIA_H_

#include <list>

class Distancia{

private:
		list<int> documentos;
		int distancia;

public:
		Distancia(){}

		Distancia(list<int> idDocumento,int distancia)
		{
			this->documentos = idDocumento;
			this->distancia = distancia;
		}

		virtual ~Distancia(){}

		int getDistancia() const
		{
		    return distancia;
		}

		list<int> getDocumentos()
		{
		    return documentos;
		}

		void setDistancia(int distancia)
		{
		    this->distancia = distancia;
		}

		void setDocumentos(list<int> idDocumento)
		{
		    this->documentos = idDocumento;
		}

		void agregarDocumentos(list<int> & documentos)
		{
			list<int> :: iterator itDocumentos = documentos.begin();

			while(itDocumentos != documentos.end())
			{
				this->documentos.push_back(*itDocumentos);
				++itDocumentos;
			}
		}

		int obtenerDocumento()
		{
			list<int> :: iterator itIdDocumento = this->documentos.begin();
			return *itIdDocumento;

		}
};





#endif /* DISTANCIA_H_ */
