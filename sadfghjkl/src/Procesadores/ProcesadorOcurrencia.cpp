#include "ProcesadorOcurrencia.h"

ProcesadorOcurrencia::ProcesadorOcurrencia() {


}

ProcesadorOcurrencia::~ProcesadorOcurrencia() {

}

list<Ocurrencia> ProcesadorOcurrencia::obtenerOcurrencias (list<string> palabras)
{

	list<Ocurrencia> ocurrencias;
	this->getOcurrencias(palabras, ocurrencias);
	return ocurrencias;
}

void ProcesadorOcurrencia::getOcurrencias(list<string> palabras, list<Ocurrencia> & ocurrencias)
{
	list <string> ::iterator itPalabras;
	list<Ocurrencia> :: iterator itOcurrencias;
	Parser parser;

	int iteracion = 0;
	bool encontrado = false;

	for(itPalabras = palabras.begin();itPalabras!= palabras.end(); ++itPalabras)
	{
		string palabraActual = *itPalabras;

		char * cadena = (char*)calloc (palabraActual.length(), sizeof(char));

		palabraActual.copy(cadena,palabraActual.length(),0);

		itOcurrencias = ocurrencias.begin();

		bool esStopWords = parser.esStopWords(cadena);

		if(!esStopWords)
		{
			// Agrego palabra al archivo de termino.

			Termino termino = agregarTermino(palabraActual);

			while(itOcurrencias != ocurrencias.end() && !encontrado)
			{
				//Si es asi hay que agregar una nueva posicion a la palabra.
				if(strcmp(palabraActual.c_str(),(*itOcurrencias).getPalabra().c_str()) == 0)
				{
					(*itOcurrencias).agregarPosicion(iteracion);
					encontrado = true;
				}
				++itOcurrencias;
			}
			//Si no encontre esa clave es porque no existe en la lista de apariciones
			//entonces la agrego por primera vez.
			if(!encontrado)
			{
				Ocurrencia nuevaOcurrencia;

				nuevaOcurrencia.setPalabra(palabraActual);
				nuevaOcurrencia.agregarPosicion(iteracion);
				nuevaOcurrencia.setIdPalabra(termino.getIdTermino());
				ocurrencias.push_back(nuevaOcurrencia);
			}

			encontrado = false;
		}
		free(cadena);
		iteracion++;
	}
}

Termino ProcesadorOcurrencia::agregarTermino(string palabraActual){

	Termino termino;

	//TODO llamar al arbol de terminos

	return termino;
}
