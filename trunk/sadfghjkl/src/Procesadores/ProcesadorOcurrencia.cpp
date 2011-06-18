#include "ProcesadorOcurrencia.h"

ProcesadorOcurrencia::ProcesadorOcurrencia() {
	this->cantidadTerminos = 0;
	this->idTerminos = new int[STRING_BUFFER_PALABRAS];
}

ProcesadorOcurrencia::~ProcesadorOcurrencia() {
	if (this->idTerminos) delete[] this->idTerminos;
}

vector<Ocurrencia> ProcesadorOcurrencia::obtenerOcurrencias (list<string> palabras, int idDocumento)
{

	vector<Ocurrencia> ocurrencias;
	this->getOcurrencias(palabras, ocurrencias, idDocumento);
	return ocurrencias;
}

void ProcesadorOcurrencia::getOcurrencias(list<string> palabras, vector<Ocurrencia> & ocurrencias, int idDocumento)
{
	list <string> ::iterator itPalabras;
	vector<Ocurrencia> :: iterator itOcurrencias;
	Parser parser;

	int iteracion = 0;
	FrecuenciaTermino frecTermino;
	frecTermino.frecuencia = 0;
	frecTermino.idTermino = -1;

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
			//Si es asi hay que agregar una nueva posicion a la palabra.
			insertarBinarioOcurrencia(palabraActual, iteracion, termino.getIdTermino(), ocurrencias, &frecTermino);
		}
		free(cadena);
		iteracion++;

	}
		cout << "Indexando palabras Libro de ID " << idDocumento << " ..." << endl;
    // Le paso la lista de terminos al handler del archivo de normas.

    //ver como guardar el número de documento indexado (total de docs +1
    ProcesadorNorma handlerFrec;
    handlerFrec.actualizarPesos(idDocumento, this->idTerminos, this->cantidadTerminos);
    handlerFrec.guardarIDTerminoFrecuente(idDocumento, frecTermino.idTermino);

}

Termino ProcesadorOcurrencia::agregarTermino(string palabraActual){

	Termino termino;

	ArbolBMas arbol(PATH_ID_TERMINOS, PATH_IDS, 1);
	Clave * clave = new Clave(palabraActual);
	Persistencia * cadenaDato = new Persistencia(palabraActual);
	Persistencia * cadenaID = new Persistencia(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);
	int idTermino = arbol.insertar(&elemento, true);
	termino.setIdTermino(idTermino);

	insertarIdTermino(termino.getIdTermino());

	return termino;
}

void ProcesadorOcurrencia::insertarBinarioOcurrencia(string palabraActual, int iteracion, int idTermino, vector<Ocurrencia> & ocurrencias, FrecuenciaTermino * frecTermino){

	Ocurrencia nuevaOcurrencia;
	if ( ocurrencias.empty() )
	{
		nuevaOcurrencia.setPalabra(palabraActual);
		nuevaOcurrencia.agregarPosicion(iteracion);
		nuevaOcurrencia.setIdPalabra(idTermino);
		ocurrencias.push_back(nuevaOcurrencia);

		frecTermino->frecuencia = 1;
		frecTermino->idTermino = idTermino;
		return;
	}

	int inferior = 0;
	int superior = (ocurrencias.size()) - 1;
	int medio = 0;

	while (inferior <= superior)
	{
		medio = (inferior + superior) / 2;

		if (idTermino < ocurrencias[medio].getIdPalabra())
		{
			superior = medio - 1;
		}
		else
		{
			inferior = medio + 1;
		}
	}

	if (superior < 0 || idTermino > ocurrencias[medio].getIdPalabra())
		superior ++;

	if (ocurrencias[superior].getIdPalabra() != idTermino) {
		nuevaOcurrencia.setPalabra(palabraActual);
		nuevaOcurrencia.agregarPosicion(iteracion);
		nuevaOcurrencia.setIdPalabra(idTermino);


		if (superior < (int)ocurrencias.size()){
			Ocurrencia aux, aux2;

			aux = ocurrencias[superior];
			ocurrencias[superior] = nuevaOcurrencia;

			for (int i = superior+1; i < (int)ocurrencias.size()-1; ++ i)
			{
				aux2 = ocurrencias[i];
				ocurrencias[i] = aux;
				aux = aux2;
			}
			ocurrencias.push_back(aux);
		} else {
			ocurrencias.push_back(nuevaOcurrencia);
		}
	} else {
		ocurrencias[superior].agregarPosicion(iteracion);
		int cantidadPosiciones = (ocurrencias[superior].getPosiciones()).size();

		if (cantidadPosiciones > frecTermino->frecuencia){
			frecTermino->idTermino = idTermino;
			frecTermino->frecuencia = cantidadPosiciones;
		}
	}
}


void ProcesadorOcurrencia::insertarIdTermino(int idTermino){

	if (this->cantidadTerminos == 0 )
	{
		this->idTerminos[0] = idTermino;
		++this->cantidadTerminos;
		return;
	}

	int inferior = 0;
	int superior = (this->cantidadTerminos) - 1;
	int medio = 0;

	while (inferior <= superior)
	{
		medio = (inferior + superior) / 2;

		if (idTermino < this->idTerminos[medio])
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
		int aux2;
		for (int i = superior+1; i < (int)this->cantidadTerminos-1; ++ i)
		{
			aux2 = this->idTerminos[i];
			this->idTerminos[i] = aux;
			aux = aux2;
		}

		++this->cantidadTerminos;
	}
}
