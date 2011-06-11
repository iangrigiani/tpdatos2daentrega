#include "ProcesadorOcurrencia.h"

ProcesadorOcurrencia::ProcesadorOcurrencia() {

}

ProcesadorOcurrencia::~ProcesadorOcurrencia() {
	if(this->idTerminos) delete[] idTerminos;

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
	//HandlerFrecGlobalTerminos handler(this->idTerminos);
}

Termino ProcesadorOcurrencia::agregarTermino(string palabraActual){

	Termino termino;

	ArbolBMas arbol(PATH_ID_TERMINOS, 1);
	Clave * clave = new Clave(palabraActual);
	CadenaBytes * cadenaDato = new CadenaBytes(palabraActual);
	CadenaBytes * cadenaID = new CadenaBytes(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);
	int idTermino = arbol.insertar(&elemento);
	termino.setIdTermino(idTermino);


	//TODO ver bien esto ( Agrega un termino a la lista de ID para pasar al handler de NORMAS )
	//TODO cambiar esto porque insertarIdTermino no esta andando.
	insertarIdTermino(termino.getIdTermino());

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

	if (this->idTerminos )
	{
		this->idTerminos[0] = idTermino;
		++this->cantidadTerminos;
		return;
	}

	int inferior = 0;
	int superior = (this->cantidadTerminos) - 1;
	int medio = 0;

	while (inferior < superior)
	{
		medio = (inferior + superior) / 2;

		if (idTermino <= this->idTerminos[medio])
		{
			superior = medio - 1;
		}
		else
		{
			inferior = medio + 1;
		}
	}

	if (superior < 0 || idTermino > this->idTerminos[medio])
		superior ++;

	if (this->idTerminos[superior] != idTermino)
	{
		int aux = this->idTerminos[superior];
		this->idTerminos[superior] = idTermino;
		this->idTerminos[superior+1] = aux;
		for (int i = superior+2; i < (int)this->cantidadTerminos; ++ i)
		{
			this->idTerminos[i+1] = this->idTerminos[i];
			++this->cantidadTerminos;
		}
	}
}
