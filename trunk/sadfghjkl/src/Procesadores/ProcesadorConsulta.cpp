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

	if (palabraFiltrada.obtenerDocumentos().size() != 0){
		filtrarProximidad(palabraFiltrada);
	}

	filtrarRanqueada(palabraFiltrada);

	return palabraFiltrada.obtenerDocumentos();
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

void ProcesadorConsulta::filtrarProximidad(Palabra & palabra){

}

void ProcesadorConsulta::filtrarRanqueada(Palabra & palabra){

}
