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



list<int> ProcesadorConsulta::compararApariciones(list<int> documentos1, list<int> documentos2)
{
	list<int> documentosCoincidentes;

	list<int> :: iterator itDocumentos1;
	list<int> :: iterator itDocumentos2;

	bool encontrado = false;

	for(itDocumentos1 = documentos1.begin(); itDocumentos1 != documentos1.end();++itDocumentos1)
	{
		int documento1Actual = *itDocumentos1;

		itDocumentos2 = documentos2.begin();

		while(itDocumentos2 != documentos2.end() && !encontrado)
		{
			int documento2Actual = *itDocumentos2;

			//Coincidencia de documentos, se supone que aparecen una vez en la lista
			//nada mas por lo que una vez que lo encuentra sale del while
			if(documento1Actual == documento2Actual)
			{
				documentosCoincidentes.push_back(documento1Actual);
				encontrado = true;
			}

			itDocumentos2++;
		}

		encontrado = false;
	}

	return documentosCoincidentes;


}



list<int> ProcesadorConsulta::procesarApariciones(list<Aparicion> apariciones)
{
	list<int> documentosCoincidentes;

	list<Aparicion> :: iterator itApariciones = apariciones.begin();


	Aparicion aparicionActual = *itApariciones;
	++itApariciones;
	Aparicion aparicionSiguiente;

	while(itApariciones != apariciones.end())
	{
		aparicionSiguiente = *itApariciones;

		if(documentosCoincidentes.size() == 0)
		{
			documentosCoincidentes = compararApariciones(aparicionActual.getDocumentos(),aparicionSiguiente.getDocumentos());
		}
		else
		{
			documentosCoincidentes = compararApariciones(documentosCoincidentes,aparicionSiguiente.getDocumentos());
		}

		++itApariciones;

		aparicionActual = aparicionSiguiente;
	}

	return documentosCoincidentes;
}



list<int> ProcesadorConsulta::consultarPalabras(list<string> palabras)
{
	list<string> :: iterator itPalabras;


	//TODO cambiar hash termino por arbol para manejar los terminos
	//HashTermino hashTermino(TAM_CUBO,PATH_BLOQUES_TERMINO,PATH_ESP_LIBRE_TERMINO,PATH_TABLA_TERMINO,PATH_TMP_TERMINO,PATH_ID);

	HashPalabra hashPalabra;
	hashPalabra.crear_condiciones_iniciales();

	HandlerArchivoOcurrencias handlerArchivoOcurrencias;

	list<Aparicion> apariciones;

	for(itPalabras = palabras.begin();itPalabras!= palabras.end();++itPalabras)
	{
		Aparicion aparicion;

		//TODO Cambiar por arbol
		//int idTermino = hashTermino.consultar(*itPalabras);

		//TODO agregar un consultar en HashPalabras que devuelva la lista de offsets de cada termino
		list<int> offsetsArchivoOcurrencias;

		//Esto devuelve la lista de offsets al archivo de ocurrencias correspondiente a ese termino
		//offsetsArchivoOcurrencias = hashPalabra.consultar(idTermino);

		aparicion.setDocumentos(handlerArchivoOcurrencias.obtenerListaDocumentos(offsetsArchivoOcurrencias));
		aparicion.setPalabra(*itPalabras);

		apariciones.push_back(aparicion);
	}


	//Metodo que realiza la interseccion de las listas para obtener los documentos en comun.
	return this->procesarApariciones(apariciones);
}
