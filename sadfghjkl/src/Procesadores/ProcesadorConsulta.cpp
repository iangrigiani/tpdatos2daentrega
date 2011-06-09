/*
 * ProcesadorConsulta.cpp
 *
 *  Created on: 01/06/2011
 *      Author: catu
 */

#include "ProcesadorConsulta.h"

ProcesadorConsulta::ProcesadorConsulta() {

}

ProcesadorConsulta::~ProcesadorConsulta() {

}


void ProcesadorConsulta::crearAparicion(Aparicion aparicion1, Aparicion aparicion2, Aparicion & nuevaAparicion)
{
	//Agrego el id correspondiente al documento
	nuevaAparicion.setIdDocumento(aparicion1.getIdDocumento());

	list<Posicion> posiciones1 = aparicion1.getPosiciones();
	list<Posicion> posiciones2 = aparicion2.getPosiciones();

	list<Posicion> :: iterator itPosiciones1 = posiciones1.begin();
	list<Posicion> :: iterator itPosiciones2 = posiciones2.begin();

	while(itPosiciones1 != posiciones1.end())
	{
		nuevaAparicion.agregarPosiciones((*itPosiciones1).getPosiciones(), (*itPosiciones1).getPalabra());
		++itPosiciones1;
	}

	while(itPosiciones2 != posiciones2.end())
	{
		nuevaAparicion.agregarPosiciones((*itPosiciones2).getPosiciones(),(*itPosiciones2).getPalabra());
		++itPosiciones2;
	}
}


Palabra ProcesadorConsulta::compararApariciones(Palabra palabra1, Palabra palabra2)
{
	Palabra palabraCoincidente;

	list<Aparicion> apariciones1 = palabra1.getApariciones();
	list<Aparicion> apariciones2 = palabra2.getApariciones();

	list<Aparicion> :: iterator itApariciones1 = apariciones1.begin();
	list<Aparicion> :: iterator itApariciones2;

	bool encontrado = false;

	palabraCoincidente.setPalabra(palabra1.getPalabra() +" "+ palabra2.getPalabra());

	while (itApariciones1 != apariciones1.end())
	 {
		Aparicion aparicionActual1 = *itApariciones1;

		itApariciones2 = apariciones2.begin();

		while(itApariciones2 != apariciones2.end() && !encontrado)
		{
			Aparicion aparicionActual2 = *itApariciones2;

			//Coincidencia de documentos, se supone que aparecen una vez en la lista
			//nada mas por lo que una vez que lo encuentra sale del while
			if(aparicionActual1.getIdDocumento() == aparicionActual2.getIdDocumento())
			{
				Aparicion nuevaAparicion;

				//Creo una nueva aparicion a partir de las dos coincidentes en el documento
				//Se guardan ambas listas de posiciones referentes a cada palabra
				this->crearAparicion(aparicionActual1,aparicionActual2,nuevaAparicion);

				palabraCoincidente.agregarAparicion(nuevaAparicion);

				encontrado = true;
			}

			itApariciones2++;
		}

		encontrado = false;
		itApariciones1++;
	}

	return palabraCoincidente;


}



Palabra ProcesadorConsulta::procesarApariciones(list<Palabra> palabras)
{
	Palabra palabraFiltrada;

	list<Palabra> :: iterator itPalabras = palabras.begin();


	Palabra palabraActual = *itPalabras;
	++itPalabras;
	Palabra palabraSiguiente;

	while(itPalabras != palabras.end())
	{
		palabraSiguiente = *itPalabras;

		if(palabraFiltrada.obtenerDocumentos().size() == 0)
		{
			palabraFiltrada = compararApariciones(palabraActual,palabraSiguiente);
		}
		else
		{
			palabraFiltrada = compararApariciones(palabraFiltrada,palabraSiguiente);
		}

		++itPalabras;

		palabraActual = palabraSiguiente;
	}

	return palabraFiltrada;
}



list<int> ProcesadorConsulta::consultarPalabras(list<string> palabras)
{
	list<Palabra> palabrasConsulta;
	list<int> documentosCoincidentes;

	Palabra palabraFiltrada;

	list<string> :: iterator itPalabras  = palabras.begin();

	if ( palabras.size() == 1 )
		return this->consultaPuntualPalabra(*itPalabras);


	//TODO cambiar hash termino por arbol para manejar los terminos
	//HashTermino hashTermino(TAM_CUBO,PATH_BLOQUES_TERMINO,PATH_ESP_LIBRE_TERMINO,PATH_TABLA_TERMINO,PATH_TMP_TERMINO,PATH_ID);

	HashPalabra hashPalabra;
	hashPalabra.crear_condiciones_iniciales();

	HandlerArchivoOcurrencias handlerArchivoOcurrencias;

	while( itPalabras!= palabras.end() )
	{
		Palabra palabra;

		//TODO Cambiar por arbol
		//int idTermino = hashTermino.consultar(*itPalabras);

		//TODO agregar un consultar en HashPalabras que devuelva la lista de offsets de cada termino
		list<int> offsetsArchivoOcurrencias;

		//Esto devuelve la lista de offsets al archivo de ocurrencias correspondiente a ese termino
		//offsetsArchivoOcurrencias = hashPalabra.consultar(idTermino);

		palabra = handlerArchivoOcurrencias.obtenerPalabra(offsetsArchivoOcurrencias);

		palabrasConsulta.push_back(palabra);
	}

	palabraFiltrada = this->procesarApariciones(palabrasConsulta);

	//Si obtengo mas de un documento es porque primero debo filtrar por proximidad
	if (palabraFiltrada.obtenerDocumentos().size() > 1)
	{
		documentosCoincidentes = filtrarProximidad(palabraFiltrada);
	}
	else
		documentosCoincidentes = palabraFiltrada.obtenerDocumentos();

	//Si los documentos coincidentes, una vez filtrado por proximidad siguen siendo
	//mas de 1 entonces hay que hacer la consulta ranqueada
	if(documentosCoincidentes.size() > 1)
	{
		filtrarRanqueada(palabraFiltrada);
	}

	return documentosCoincidentes;
}



list<int> ProcesadorConsulta::consultaPuntualPalabra(string palabra){

	HashPalabra hashPalabra;
	hashPalabra.crear_condiciones_iniciales();
	HandlerArchivoOcurrencias handlerArchivoOcurrencias;

	list<int> offsetsArchivoOcurrencias;

	// TODO Obtener ID de termino del arbol de terminos;

	//TODO agregar un consultar en HashPalabras que devuelva la lista de offsets de cada termino
	//offsetsArchivoOcurrencias = hashPalabra.consultar(idTermino);

	return handlerArchivoOcurrencias.obtenerListaDocumentos(offsetsArchivoOcurrencias);
}

int ProcesadorConsulta::compararPosiciones(list<int> posiciones)
{
	int distanciaMinima = 0;
	int distanciaMinimaAnterior = 0;

	list<int> :: iterator itPosiciones1 = posiciones.begin();
	list<int> :: iterator itPosiciones2;

	while(itPosiciones1 != posiciones.end())
	{
		int posicion1Actual = *itPosiciones1;

		itPosiciones2 = posiciones.begin();

		while(itPosiciones2 != posiciones.end())
		{
			int posicion2Actual = *itPosiciones2;

			if(posicion1Actual != posicion2Actual)
			{
				distanciaMinima = abs(posicion2Actual - posicion1Actual);

				//Esto debe hacerse una vez solamente
				if(distanciaMinimaAnterior == 0)
					distanciaMinimaAnterior = distanciaMinima;

				if(distanciaMinima < distanciaMinimaAnterior)
					distanciaMinimaAnterior = distanciaMinima;
			}

			itPosiciones2++;
		}

		itPosiciones1++;
	}


	return distanciaMinimaAnterior;

}

void ProcesadorConsulta::filtrarPosiciones(list<int> & posiciones, Posicion posicion)
{
	list<int> pos = posicion.getPosiciones();
	list<int> :: iterator itPosiciones = pos.begin();

	while(itPosiciones!= pos.end())
	{
		posiciones.push_back(*itPosiciones);
		itPosiciones++;
	}

}



int ProcesadorConsulta::procesarPosiciones(list<Posicion> posiciones)
{
	list<Posicion> :: iterator itPosiciones = posiciones.begin();
	list<int> pos;

	//Una vez que tenemos todas las posiciones en una misma lista las comparamos
	while(itPosiciones != posiciones.end())
	{
		Posicion posicionActual = *itPosiciones;
		this->filtrarPosiciones(pos,posicionActual);
		++itPosiciones;
	}

	return compararPosiciones(pos);

}



list<int> ProcesadorConsulta::filtrarProximidad(Palabra & palabra)
{
	list<Distancia> distancias;

	list<Aparicion> apariciones = palabra.getApariciones();

	list<Aparicion> :: iterator itApariciones = apariciones.begin();

	while(itApariciones != apariciones.end())
	{
		//Obtengo la aparicion actual
		Aparicion aparicionActual = *itApariciones;
		list<int> idDocumento;

		Distancia nuevaDistancia;

		nuevaDistancia.setDistancia(this->procesarPosiciones(aparicionActual.getPosiciones()));
		idDocumento.push_back(aparicionActual.getIdDocumento());
		nuevaDistancia.setDocumentos(idDocumento);

		distancias.push_back(nuevaDistancia);

		itApariciones++;

	}

	return filtrarDistancias(distancias);
}

Distancia ProcesadorConsulta::compararDistancias(Distancia distancia1,Distancia distancia2)
{
	Distancia distanciaMinima;

	if(distancia1.getDistancia() < distancia2.getDistancia())
	{
		distanciaMinima.setDistancia(distancia1.getDistancia());
		distanciaMinima.setDocumentos(distancia1.getDocumentos());

	}
	else
		if(distancia1.getDistancia() > distancia2.getDistancia())
		{
			distanciaMinima.setDistancia(distancia2.getDistancia());
			distanciaMinima.setDocumentos(distancia2.getDocumentos());
		}
		else
		{
			distanciaMinima.setDistancia(distancia1.getDistancia());

			//Se agregan ambos documentos

			list<int> documentos1 = distancia1.getDocumentos();
			list<int> documentos2 = distancia2.getDocumentos();

			distanciaMinima.agregarDocumentos(documentos1);
			distanciaMinima.agregarDocumentos(documentos2);
		}


	return distanciaMinima;
}


list<int> ProcesadorConsulta::filtrarDistancias(list<Distancia> distancias)
{
	Distancia distanciaMinima;


	list<Distancia> :: iterator itDistancias = distancias.begin();

	Distancia distanciaActual = *itDistancias;
	++itDistancias;
	Distancia distanciaSiguiente;


	while(itDistancias != distancias.end())
	{
		distanciaSiguiente = *itDistancias;

		if(distanciaMinima.getDocumentos().size() == 0)
		{
			distanciaMinima = compararDistancias(distanciaActual,distanciaSiguiente);
		}
		else
		{
			distanciaMinima = compararDistancias(distanciaMinima,distanciaSiguiente);

		}

		distanciaActual = distanciaSiguiente;
		itDistancias++;
	}


	return distanciaMinima.getDocumentos();
}


void ProcesadorConsulta::filtrarRanqueada(Palabra & palabra)
{

}
