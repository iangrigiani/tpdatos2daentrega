#include "ProcesadorConsulta.h"

ProcesadorConsulta::ProcesadorConsulta() {

}

ProcesadorConsulta::~ProcesadorConsulta() {

}

list<int> ProcesadorConsulta::consultaAutor(string autor){

	list<Elementos*> listaRetornoBusqueda;
	list<int> listaRetorno;

	ArbolBMas* arbol = new ArbolBMas(PATH_AUTOR, 2);
	Clave* clave = new Clave(autor);
	arbol->buscar(&listaRetornoBusqueda, clave);

	if ( listaRetornoBusqueda.size() > 0){
		list<Elementos*>::iterator it = listaRetornoBusqueda.begin();
		while ( it != listaRetornoBusqueda.end()){
			listaRetorno.push_back(atoi((*it)->getID()->toString().c_str()));
			++it;
		}
	}
	return listaRetorno;
}

list<int> ProcesadorConsulta::consultaEditorial(string editorial){
	list<Elementos*> listaRetornoBusqueda;
	list<int> listaRetorno;

	ArbolBMas* arbol = new ArbolBMas(PATH_EDITORIAL, 2);
	Clave* clave = new Clave(editorial);
	arbol->buscar(&listaRetornoBusqueda, clave);

	if ( listaRetornoBusqueda.size() > 0){
		list<Elementos*>::iterator it = listaRetornoBusqueda.begin();
		while ( it != listaRetornoBusqueda.end()){
			listaRetorno.push_back(atoi((*it)->getID()->toString().c_str()));
			++it;
		}
	}
	return listaRetorno;
}

int ProcesadorConsulta::consultaTitulo(string titulo){
	HashTermino hash(NOM_BLOQUES_TITULO, NOM_ESP_LIBRE_TITULO, NOM_TABLA_TITULO);
	return (hash.consultar(titulo));
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



list<int> ProcesadorConsulta::consultaPalabras(list<string> palabras)
{
	list<Palabra> palabrasConsulta;
	list<int> documentosCoincidentes;

	Palabra palabraFiltrada;

	list<string> :: iterator itPalabras  = palabras.begin();

	if ( palabras.size() == 1 )
		return this->consultaPuntualPalabra(*itPalabras);

	HashPalabra hashPalabra(NOM_BLOQUES_PALABRA, NOM_ESP_LIBRE_PALABRA, NOM_TABLA_PALABRA);

	ArbolBMas* arbol = new ArbolBMas(PATH_ID_TERMINOS,1);
	HandlerArchivoOcurrencias handlerArchivoOcurrencias;

	while( itPalabras!= palabras.end() )
	{
		Palabra palabra;

		list<int> idTermino;
		list<Elementos*> listaBusqueda;
		Clave* clave = new Clave(*itPalabras);
		arbol->buscar(&listaBusqueda, clave);

		if ( listaBusqueda.size() > 0){
			list<Elementos*>::iterator it = listaBusqueda.begin();
			idTermino.push_back(atoi((*it)->getID()->toString().c_str()));
		}

		list<int>::iterator it2 = idTermino.begin();
		list<int> offsetsArchivoOcurrencias;

		//Esto devuelve la lista de offsets al archivo de ocurrencias correspondiente a ese termino
		offsetsArchivoOcurrencias = hashPalabra.consultar((*it2));

		palabra = handlerArchivoOcurrencias.obtenerPalabra(offsetsArchivoOcurrencias);

		palabra.setPalabra(*itPalabras);

		palabrasConsulta.push_back(palabra);
		++itPalabras;
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
//	if(documentosCoincidentes.size() > 1)
//	{
//		documentosCoincidentes = filtrarRanqueada(palabraFiltrada);
//	}


	return documentosCoincidentes;
}



list<int> ProcesadorConsulta::consultaPuntualPalabra(string palabra){

	HashPalabra hashPalabra(NOM_BLOQUES_PALABRA, NOM_ESP_LIBRE_PALABRA, NOM_TABLA_PALABRA);
	HandlerArchivoOcurrencias handlerArchivoOcurrencias;

	list<int> offsetsArchivoOcurrencias;
	list<int> idTermino;

	ArbolBMas* arbol = new ArbolBMas(PATH_ID_TERMINOS, 1);
	list<Elementos*> listaBusqueda;
	Clave* clave = new Clave(palabra);
	arbol->buscar(&listaBusqueda, clave);

	if ( listaBusqueda.size() > 0){
		list<Elementos*>::iterator it = listaBusqueda.begin();
		idTermino.push_back(atoi((*it)->getID()->toString().c_str()));
	}

	list<int>::iterator it2 = idTermino.begin();

	offsetsArchivoOcurrencias = hashPalabra.consultar((*it2));

	return (handlerArchivoOcurrencias.obtenerListaDocumentos(offsetsArchivoOcurrencias));
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

	return filtrarDistancias(distancias,palabra);
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


list<int> ProcesadorConsulta::filtrarDistancias(list<Distancia> distancias, Palabra & palabra)
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

	filtrarDocumentos(distanciaMinima,palabra);

	return distanciaMinima.getDocumentos();
}

void ProcesadorConsulta::filtrarDocumentos(Distancia distancia, Palabra & palabra)
{
	list<Aparicion> apariciones = palabra.getApariciones();
	list<Aparicion> :: iterator itApariciones;

	list<Aparicion> aparicionesFiltradas;

	list<int> documentosCoincidentes = distancia.getDocumentos();
	list<int> :: iterator itDocumentos = documentosCoincidentes.begin();

	bool encontrado = false;


	while(itDocumentos != documentosCoincidentes.end())
	{
		int docActual = *itDocumentos;

		 itApariciones = apariciones.begin();

		 while(itApariciones != apariciones.end() && !encontrado)
		 {
			 Aparicion aparicionActual = *itApariciones;
			 if(aparicionActual.getIdDocumento() == docActual)
			 {
				 aparicionesFiltradas.push_back(aparicionActual);
				 encontrado = true;

			 }

			 itApariciones++;

		 }

		 encontrado = false;
		 itDocumentos++;
	}

	apariciones.clear();

	list<Aparicion> :: iterator itAparicionFiltrada = aparicionesFiltradas.begin();

	while(itAparicionFiltrada != aparicionesFiltradas.end())
	{
		apariciones.push_back(*itAparicionFiltrada);
		itAparicionFiltrada++;

	}

}



list<int> ProcesadorConsulta::filtrarRanqueada(Palabra & palabra)
{
	list<int> documentos;

	return documentos;

}
