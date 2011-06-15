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
	HashTitulo hash(NOM_BLOQUES_TITULO, NOM_ESP_LIBRE_TITULO, NOM_TABLA_TITULO);
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

		palabra = handlerArchivoOcurrencias.obtenerPalabra(offsetsArchivoOcurrencias,*itPalabras);

		palabra.setPalabra(*itPalabras);

		palabrasConsulta.push_back(palabra);
		++itPalabras;
	}

	palabraFiltrada = this->procesarApariciones(palabrasConsulta);

	Palabra palabraFiltroProximidad;

	//Si obtengo mas de un documento es porque primero debo filtrar por proximidad
	if (palabraFiltrada.obtenerDocumentos().size() > 1)
	{
		palabraFiltroProximidad = filtrarProximidad(palabraFiltrada,documentosCoincidentes);
	}
	else
		documentosCoincidentes = palabraFiltrada.obtenerDocumentos();


	//Si los documentos coincidentes, una vez filtrado por proximidad siguen siendo
	//mas de 1 entonces hay que hacer la consulta ranqueada

	if(documentosCoincidentes.size() > 1)
	{
		documentosCoincidentes = filtrarRanqueada(palabraFiltroProximidad);
	}

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

	if (idTermino.size() > 0) {
		list<int>::iterator it2 = idTermino.begin();
		offsetsArchivoOcurrencias = hashPalabra.consultar((*it2));
	}

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

			if(posicion1Actual < posicion2Actual)
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

	posiciones.push_back(*itPosiciones);
}



int ProcesadorConsulta::procesarPosiciones(list<Posicion> & posiciones)
{
	list<Posicion> :: iterator itPosiciones = posiciones.begin();
	list<int> pos;
	list<Posicion> posicionesMinimas;

	int distancia = -1;


	Posicion posicionActual = *itPosiciones;
	++itPosiciones;
	Posicion posicionSiguiente;
	Posicion posicionCalculada;

	bool procesar = true;

	while(itPosiciones != posiciones.end() && procesar)
	{
		posicionSiguiente = *itPosiciones;
		posicionCalculada = this->compararPosiciones(posicionActual,posicionSiguiente,posicionesMinimas);
		posicionActual = posicionCalculada;

		if(posicionCalculada.getPosiciones().size() == 0)
			procesar = false;
		++itPosiciones;
	}


	//Actualizo la lista de posiciones con la minima.
	posiciones.clear();

	list<Posicion> :: iterator itPosicionesMinimas = posicionesMinimas.begin();

	while(itPosicionesMinimas != posicionesMinimas.end())
	{
		Posicion posActual = *itPosicionesMinimas;

		posiciones.push_back(posActual);

		itPosicionesMinimas++;
	}


	itPosicionesMinimas = posicionesMinimas.begin();

	//Una vez que tenemos todas las posiciones en una misma lista las comparamos
	while(itPosicionesMinimas != posicionesMinimas.end())
	{
		Posicion posicionActual = *itPosicionesMinimas;
		this->filtrarPosiciones(pos,posicionActual);
		++itPosicionesMinimas;
	}


	if(procesar)
		distancia = compararPosiciones(pos);

	return distancia;
}

Posicion ProcesadorConsulta::compararPosiciones(Posicion posicionActual, Posicion posicionSiguiente, list<Posicion> & posicionesMinimas)
{

	list<int> posiciones1 = posicionActual.getPosiciones();
	list<int> posiciones2 = posicionSiguiente.getPosiciones();

	list<int> :: iterator itPosiciones1 = posiciones1.begin();
	list<int> :: iterator itPosiciones2;

	int distanciaMinima = 0;
	int distanciaMinimaAnterior = 0;

	Posicion posicionMinima;

	while(itPosiciones1!= posiciones1.end())
	{
		int pos1Actual = *itPosiciones1;

		itPosiciones2 = posiciones2.begin();

		while(itPosiciones2 != posiciones2.end())
		{
			int pos2Actual = *itPosiciones2;

			if(pos1Actual < pos2Actual)
			{
				distanciaMinima = abs(pos2Actual - pos1Actual);

				if(distanciaMinimaAnterior == 0)
					distanciaMinimaAnterior = distanciaMinima;

				if(distanciaMinima < distanciaMinimaAnterior)
				{
					distanciaMinimaAnterior = distanciaMinima;
					posicionesMinimas.clear();
					crearPosicionesNuevas(posicionActual.getPalabra(),pos1Actual,posicionSiguiente.getPalabra(),pos2Actual,posicionesMinimas);
				}
				else
					if(distanciaMinima == distanciaMinimaAnterior)
						crearPosicionesNuevas(posicionActual.getPalabra(),pos1Actual,posicionSiguiente.getPalabra(),pos2Actual,posicionesMinimas);
			}

			itPosiciones2++;

		}

		itPosiciones1++;
	}


	list<Posicion> :: iterator itPosicionesMinimas = posicionesMinimas.begin();
	bool encontrado = false;
	while(itPosicionesMinimas != posicionesMinimas.end() && !encontrado)
	{
		Posicion posicionActual = *itPosicionesMinimas;
		if(posicionActual.getPalabra() == posicionSiguiente.getPalabra())
		{
			posicionMinima = posicionActual;
			encontrado = true;
		}

		itPosicionesMinimas++;
	}

	return posicionMinima;


}


void ProcesadorConsulta::crearPosicionesNuevas(string palabra1,int posicion1, string palabra2,int posicion2, list<Posicion> & posicionesMinimas)
{
	Posicion pos1;
	Posicion pos2;

	list<Posicion> :: iterator itPosiciones = posicionesMinimas.begin();

	pos1.setPalabra(palabra1);
	pos1.agregarPosicion(posicion1);
	pos2.setPalabra(palabra2);
	pos2.agregarPosicion(posicion2);

	bool encontrado = false;

	list<Posicion> actuales1;
	list<Posicion> actuales2;

	if(posicionesMinimas.size() > 0)
	{

		//Agrego todos los elementos en mi nueva lista
		while(itPosiciones != posicionesMinimas.end())
		{
			Posicion posicionActual = *itPosiciones;

			list<int> pos;

			if(posicionActual.getPalabra() == palabra1)
			{
				pos.push_back(posicion1);
				posicionActual.agregarPosiciones(pos);
				encontrado = true;

			}

			actuales1.push_back(posicionActual);

			itPosiciones++;
		}

		if(!encontrado)
			actuales1.push_back(pos1);

		encontrado = false;
		itPosiciones = actuales1.begin();


		while(itPosiciones != actuales1.end())
		{
			Posicion posicionActual = *itPosiciones;

			list<int> pos;

			if(posicionActual.getPalabra() == palabra2)
			{
				pos.push_back(posicion2);
				posicionActual.agregarPosiciones(pos);
				encontrado = true;
			}

			actuales2.push_back(posicionActual);

			itPosiciones++;

		}

		if(!encontrado)
			actuales2.push_back(pos2);

		posicionesMinimas.clear();
		itPosiciones = actuales2.begin();

		while(itPosiciones != actuales2.end())
		{
			Posicion actual = *itPosiciones;
			posicionesMinimas.push_back(actual);
			itPosiciones++;
		}

	}
	else
	{
		posicionesMinimas.push_back(pos1);
		posicionesMinimas.push_back(pos2);
	}


}




Palabra ProcesadorConsulta::filtrarProximidad(Palabra  palabra, list<int> & documentosCoincidentes)
{
	list<Distancia> distancias;

	list<Aparicion> apariciones = palabra.getApariciones();

	list<Aparicion> :: iterator itApariciones = apariciones.begin();

	list<Posicion> posiciones;

	list<Aparicion> aparicionesActualizadas;

	Palabra palabraFiltrada;

	Palabra palabraResultado;

	while(itApariciones != apariciones.end())
	{
		//Obtengo la aparicion actual
		Aparicion aparicionActual = *itApariciones;

		posiciones = aparicionActual.getPosiciones();

		list<int> idDocumento;

		Distancia nuevaDistancia;

		nuevaDistancia.setDistancia(this->procesarPosiciones(posiciones));
		idDocumento.push_back(aparicionActual.getIdDocumento());
		nuevaDistancia.setDocumentos(idDocumento);

		if(nuevaDistancia.getDistancia() != -1)
		{
			distancias.push_back(nuevaDistancia);
		}
		this->actualizarApariciones(aparicionActual.getIdDocumento(),posiciones,aparicionesActualizadas);

		itApariciones++;

	}

	list<Aparicion> :: iterator itApActualizadas = aparicionesActualizadas.begin();

	while(itApActualizadas != aparicionesActualizadas.end())
	{
		palabraFiltrada.agregarAparicion(*itApActualizadas);
		itApActualizadas++;
	}


	palabraFiltrada.setPalabra(palabra.getPalabra());

	palabraResultado = filtrarDistancias(distancias,palabraFiltrada,documentosCoincidentes);

	return palabraResultado;
}

void ProcesadorConsulta::actualizarApariciones(int idDocumento,list<Posicion> posiciones, list<Aparicion> & aparicionesActualizadas)
{
	Aparicion aparicionActualizada;

	aparicionActualizada.setIdDocumento(idDocumento);

	list<Posicion> :: iterator itPos = posiciones.begin();


	while(itPos != posiciones.end())
	{
		Posicion pos = *itPos;
		aparicionActualizada.agregarPosicion(pos);
		itPos++;

	}

	aparicionesActualizadas.push_back(aparicionActualizada);

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


Palabra ProcesadorConsulta::filtrarDistancias(list<Distancia> distancias, Palabra  palabra, list<int> & documentosCoincidentes)
{
	Distancia distanciaMinima;

	Palabra palabraFiltrada;


	if(distancias.begin() != distancias.end())
	{

		list<Distancia> :: iterator itDistancias = distancias.begin();

		Distancia distanciaActual = *itDistancias;
		distanciaMinima = distanciaActual;
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

		palabraFiltrada = filtrarDocumentos(distanciaMinima,palabra);

	}


	list<int> docs = distanciaMinima.getDocumentos();

	list<int> :: iterator itDocs = docs.begin();

	while(itDocs != docs.end())
	{
		documentosCoincidentes.push_back(*itDocs);
		itDocs++;
	}

	return palabraFiltrada;
}

Palabra ProcesadorConsulta::filtrarDocumentos(Distancia distancia, Palabra  palabra)
{
	list<Aparicion> apariciones = palabra.getApariciones();
	list<Aparicion> :: iterator itApariciones;
	list<Aparicion> aparicionesFiltradas;

	Palabra filtrada;

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

	filtrada.setPalabra(palabra.getPalabra());


	list<Aparicion> :: iterator itAparicionFiltrada = aparicionesFiltradas.begin();

	while(itAparicionFiltrada != aparicionesFiltradas.end())
	{
		Aparicion actual = *itAparicionFiltrada;

		filtrada.agregarAparicion(actual);
		itAparicionFiltrada++;

	}

	return filtrada;

}



list<int> ProcesadorConsulta::filtrarRanqueada(Palabra palabra)
{
	list<int> documentos;

	// cantidadApariciones representa la cantidad de libros donde hay coincidencias
	int cantidadApariciones = (palabra.getApariciones()).size();

	int frecTerminoEnDoc = 0;
	list<Aparicion>::iterator itAparicionFiltrada;
	list<Posicion>::iterator itPosicionEnDoc;
	list<int>::iterator itPosicionDocumentos;

	Aparicion aparicion;
	Posicion posicion;
	float pesoGlobal, mayorPeso, pesoTerminosEnDocumento, normaDocumento, sumaParcial;
	CalculadorDePesoGlobal calcPesoGlobal;
	int cantPalabras = 0;
	int cantDocumentosTermino = 0;
	list<Aparicion> apariciones = palabra.getApariciones();

	// por cada documento hay una aparicion
	for (int a = 0; a<cantidadApariciones; a++){

		sumaParcial = 0;
		pesoTerminosEnDocumento = 0;

		itAparicionFiltrada = apariciones.begin();

		for (int b =0; b < a; b++){
			++itAparicionFiltrada;
		}

		aparicion = *itAparicionFiltrada;


		// Calculo el peso:
		// para eso recorro la lista de posiciones (cada una representa a una palabra) y calculo su peso y su frecuencia
		cantPalabras = (aparicion.getPosiciones()).size();
		itPosicionEnDoc = aparicion.getPosiciones().begin();
		for (int c = 0; c < cantPalabras; c++){

			posicion = *itPosicionEnDoc;
			frecTerminoEnDoc = (posicion.getPosiciones()).size();

			// TODO: Obtengo del arbol la cantidad de documentos donde aparece el termino (NECESITO EL ID!!)
			//cantDocumentosTermino = procesarNorma.buscarPesoTermino(idTermino);
			pesoGlobal = calcPesoGlobal.calcularPesoGlobalTermino(cantDocumentosTermino);

			sumaParcial += frecTerminoEnDoc * pesoGlobal;
			++itPosicionEnDoc;
		}

		// TODO: obtener la norma del documento:
		// normaDocumento = procesarNorma.consultarNorma(aparicion.getIdDocumento());
		pesoTerminosEnDocumento = sumaParcial / normaDocumento;

		// Si la lista de documentos esta vacia, no importa el peso que tenga, sera siempre el de mayor peso hasta ahora
		if (documentos.empty()){
			documentos.push_back(aparicion.getIdDocumento());
			mayorPeso = pesoTerminosEnDocumento;
		} else {
			// Comparo pesos
			if (pesoTerminosEnDocumento > mayorPeso){

				int cantDocumentosADevolver = documentos.size();
				// Vacio la lista de documentos
				for (int d = 0; d<cantDocumentosADevolver; d++){
					documentos.pop_back();
				}

				// Inserto el id del documento con mayor peso
				documentos.push_back(aparicion.getIdDocumento());
				mayorPeso = pesoTerminosEnDocumento;


			} else if (pesoTerminosEnDocumento == mayorPeso){
				// Si el peso es el mismo, agrego el id del documento a la lista
				documentos.push_back(aparicion.getIdDocumento());
			}

		}

	}

	return documentos;
}
