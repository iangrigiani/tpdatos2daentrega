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
			//Si no encontre esa clave es porque no existe en la lista de ocurrencias
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

	// Le paso la lista de terminos al handler del archivo de normas.
	HandlerNormasAInfinito handler(this->idTerminos);
}

Termino ProcesadorOcurrencia::agregarTermino(string palabraActual){

	Termino termino;

	//TODO llamar al arbol de terminos
	termino.setIdTermino(0);


	//TODO ver bien esto
	//insertarIdTermino(termino.getIdTermino());

	return termino;
}

/*
bool ProcesadorOcurrencia::existeTermino(int idTermino){

	int totalElem = this->idTerminos.size();
	int medio, pivotDer, pivotIzq;
	pivotIzq=0;

	pivotDer=totalElem-1;

	while ( pivotIzq <= pivotDer) {
		medio = ( pivotIzq + pivotDer )/2;
		if ( idTermino > this->idTerminos[medio] )
			pivotIzq = medio + 1;
		else if ( idTermino < this->idTerminos[medio] )
			pivotDer = medio - 1;
		else return true;
	}

	return false;
}
*/


void ProcesadorOcurrencia::insertarIdTermino(int idTermino){

	int totalElem = this->idTerminos.size();
	int medio, pivotDer, pivotIzq;
	pivotIzq=0;
	pivotDer=totalElem-1;
	bool encontrado=false;

	while ( pivotIzq <= pivotDer) {
		medio = ( pivotIzq + pivotDer )/2;
		if ( idTermino > this->idTerminos[medio] )
			pivotIzq = medio + 1;
		else if ( idTermino < this->idTerminos[medio] )
			pivotDer = medio - 1;
		else encontrado = true;;
	}

	if (!encontrado){
		int aux = this->idTerminos[medio];
		if ( aux > idTermino ){
			this->idTerminos[medio] = idTermino;
			for (int a=medio+1; a<totalElem; a++){
				this->idTerminos[a] = aux;
				aux = this->idTerminos[a+1];
			}
		} else {
			aux = this->idTerminos[medio+1];
			this->idTerminos[medio+1] = idTermino;
			for (int a=medio+2; a<totalElem; a++){
				this->idTerminos[a] = aux;
				aux = this->idTerminos[a+1];
			}

		}
	}
}
