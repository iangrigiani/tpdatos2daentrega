#include "HandlerArchivoOcurrencias.h"

HandlerArchivoOcurrencias::HandlerArchivoOcurrencias()
{
	this->offsetAAEL = 0;
	this->crearArchivoVacio();

}

void HandlerArchivoOcurrencias::crearArchivoVacio()
{
	fstream arch;
	arch.open(PATH_ARCHIVO_OCURRENCIAS, fstream::app);
	arch.close();
}

int HandlerArchivoOcurrencias::obtenerOffsetABorrar(list<int>& offsets,int idDocumento){

	int retorno;
	std::list < int > ::iterator it = offsets.begin();
	int numeroDocumento = 0;
	CodigoGamma codigoGamma;
	bool encontrado = false;

	while (it != offsets.end() && encontrado == false) {

		Ocurrencia o = this->buscarOcurrencia(*it);
		numeroDocumento = codigoGamma.interpretarConversion(o.getCodigoGammaDocumento());
		if (numeroDocumento == idDocumento) {
			encontrado = true;
			retorno = (*it);
		}
		++ it;
	}

	if (encontrado == true)
		return retorno;

	return ERROR;
}


int HandlerArchivoOcurrencias::buscarOffsetArchivoEspaciosLibres(int tamanioOcurrencia)
{
	std:: fstream fEspLibreOcurrencias;
	fEspLibreOcurrencias.open(PATH_ESPACIO_LIBRE_OCURRENCIAS, std::ios_base::in | std::ios_base::out);

	if (!fEspLibreOcurrencias.is_open()){
		fEspLibreOcurrencias.open(PATH_ESPACIO_LIBRE_OCURRENCIAS, std::ios_base::out);
		fEspLibreOcurrencias.close();
		fEspLibreOcurrencias.open(PATH_ESPACIO_LIBRE_OCURRENCIAS, std::ios_base::in | std::ios_base::out);
	}

	char* cadena = (char*)calloc(100, sizeof(char));
	bool encontrado  = false;
	char * caracterProcesado;
	int retorno = ERROR;
	int tamanioOcurrenciaActual = 0;
	string cad;

	while (!encontrado && !fEspLibreOcurrencias.eof())
	{
		this->offsetAAEL = fEspLibreOcurrencias.tellg();

		fEspLibreOcurrencias.getline(cadena, 100);
		cad = cadena;
		if (cad.length() > 0)
		{
			retorno = atoi(strtok(cadena,"|"));
			caracterProcesado = strtok(NULL,"\n");
			tamanioOcurrenciaActual= atoi(caracterProcesado);
			if(tamanioOcurrenciaActual >= tamanioOcurrencia)
				encontrado = true;
			else
			{
				retorno = ERROR;
				tamanioOcurrenciaActual = 0;
			}

		}else
			retorno = ERROR;
	}

	fEspLibreOcurrencias.close();
	return retorno;
}


int HandlerArchivoOcurrencias::obtenerTamanioMaestro()
{
	FILE* archivoOCurrencias;

	if ((archivoOCurrencias = fopen(PATH_ARCHIVO_OCURRENCIAS, "r")) == NULL)
	{
			archivoOCurrencias = fopen(PATH_ARCHIVO_OCURRENCIAS, "w");
			fclose(archivoOCurrencias);
			archivoOCurrencias = fopen(PATH_ARCHIVO_OCURRENCIAS, "r");
	}

	fseek(archivoOCurrencias, 0 , SEEK_END);
	int retorno = ftell(archivoOCurrencias);
	rewind(archivoOCurrencias);
	fclose(archivoOCurrencias);
	return retorno;
}


void HandlerArchivoOcurrencias::actualizarEspaciosLibres(int offset,int espacioLibre)
{
	std::ofstream fEspLibreOcurrencias;
	fEspLibreOcurrencias.open(PATH_ESPACIO_LIBRE_OCURRENCIAS, std::ios_base::app);
	stringstream ss;
	ss <<offset<<"|"<<espacioLibre<<"\n" ;
	string str = ss.str();
	fEspLibreOcurrencias.write(str.c_str(), str.length());
	fEspLibreOcurrencias.flush();
	fEspLibreOcurrencias.close();
}


void HandlerArchivoOcurrencias::borrarOffsetArchivoDeEspaciosLibres()
{
	std::fstream fEspLibreOcurrencias;
	char  cadenaDeDatos[100];

	fEspLibreOcurrencias.open(PATH_ESPACIO_LIBRE_OCURRENCIAS, std::ios_base::in | std::ios_base::out);
	fEspLibreOcurrencias.seekg(this->offsetAAEL);
	fEspLibreOcurrencias.get(cadenaDeDatos,100);

	string cad = cadenaDeDatos;

	int longitudCadena = cad.length();
	fEspLibreOcurrencias.seekg(this->offsetAAEL);
	char * espacioLeido = (char*)calloc (longitudCadena, sizeof(char));
	free(espacioLeido);

	fEspLibreOcurrencias.write(espacioLeido, longitudCadena);
	fEspLibreOcurrencias.flush();
	fEspLibreOcurrencias.close();
}


int HandlerArchivoOcurrencias::insertarOcurrencia(Ocurrencia ocurrencia,int idDocumento)
{
	std::fstream fOcurrencias;

	fOcurrencias.open(PATH_ARCHIVO_OCURRENCIAS, std::ios_base::in | std::ios_base::out);

	//Convierto el numero de documento a Gamma
	string codigoGammaDocumento;
	if (idDocumento != 0) {
		CodigoGamma codigoGamma;
		codigoGamma.setNumAConvertir(idDocumento);
		codigoGammaDocumento = codigoGamma.aplicarConversion();
	}
	else codigoGammaDocumento = "0";

	//Le seteo a la ocurrencia su respectivo codigo gamma de documento
	ocurrencia.setCodigoGammaDocumento(codigoGammaDocumento);

	string cadenaDePosiciones;
	bool esEspacioLibre = false;
	stringstream cadenaFinal;

	if(fOcurrencias.is_open())
	{
		int offsetOcurrencia = buscarOffsetArchivoEspaciosLibres(this->obtenerTamanioOcurrencia(ocurrencia));

		if (offsetOcurrencia == ERROR)
				offsetOcurrencia = this->obtenerTamanioMaestro();
		else
			{
				this->borrarOffsetArchivoDeEspaciosLibres();
				esEspacioLibre = true;
			}


		list<int> :: iterator itPosiciones;
		unsigned int iteracion = 0;
		list<int> posiciones = ocurrencia.getPosiciones();

		for(itPosiciones = posiciones.begin(); itPosiciones != posiciones.end();++itPosiciones)
		{
			int posicionActual = *itPosiciones;

			stringstream ss;
			string posicion;

			if(iteracion+1 < posiciones.size())
			{
				ss<<posicionActual<<",";
				posicion = ss.str();
				cadenaDePosiciones+= posicion;
			}
			else
			{
				ss<<posicionActual;
				posicion = ss.str();
				cadenaDePosiciones+=posicion;
			}

			iteracion++;
		}

		if(esEspacioLibre)
			cadenaFinal << ocurrencia.getIdPalabra() << "|" << codigoGammaDocumento << "|" << cadenaDePosiciones;
		else
			cadenaFinal << ocurrencia.getIdPalabra() << "|" << codigoGammaDocumento << "|" << cadenaDePosiciones<<"\n";


		string cadenaAInsertar = cadenaFinal.str();

		// Escribo en el archivo de ocurrencias
		fOcurrencias.seekg(offsetOcurrencia);
		fOcurrencias.write(cadenaAInsertar.c_str(),cadenaAInsertar.length());
		fOcurrencias.close();


		// Retorno el offset de ocurrencias que se guarda en el hash.
		return offsetOcurrencia;

	}
	else
		return ERROR;
}

Ocurrencia HandlerArchivoOcurrencias::buscarOcurrencia(int offset)
{
	Ocurrencia  ocurrencia;

	std::ifstream archivoOcurrencias;
	char  cadenaDeDatos[100];

	archivoOcurrencias.open(PATH_ARCHIVO_OCURRENCIAS, std::ios_base::in);

	if (archivoOcurrencias.is_open())
	{
		archivoOcurrencias.seekg(offset);

		archivoOcurrencias.get(cadenaDeDatos,100);

		this->procesarCadenaDeDatos(cadenaDeDatos,ocurrencia);

		archivoOcurrencias.close();
	}

	return ocurrencia;
}



void HandlerArchivoOcurrencias::procesarCadenaDeDatos(char * cadena,Ocurrencia & ocurrencia)
{

	 char * caracteres;
	 caracteres = strtok (cadena,"|");

	 int  idPalabra;
	 list<int> posiciones;


	 idPalabra = atoi(caracteres);

	 ocurrencia.setIdPalabra(idPalabra);

	 caracteres = strtok(NULL,"|");

	 ocurrencia.setCodigoGammaDocumento(caracteres);

	 caracteres = strtok(NULL,"|,");
	 do
	 {
		 int posicion = atoi(caracteres);
		 posiciones.push_back(posicion);
	 }while((caracteres = strtok(NULL,",")) != NULL);

	 ocurrencia.agregarPosiciones(posiciones);

}


void HandlerArchivoOcurrencias::eliminarOcurrencia(int offset)
{
	std::fstream archivoOcurrencias;
	char cadenaDeDatos[255];

	archivoOcurrencias.open(PATH_ARCHIVO_OCURRENCIAS, std::ios_base::in | std::ios_base::out);
	archivoOcurrencias.seekg(offset);
	archivoOcurrencias.get(cadenaDeDatos,255);

	string cad = cadenaDeDatos;

	int tamanioArchivo = obtenerTamanioMaestro();

	if (tamanioArchivo > BASURA_RLV)
	{
		int espacioOcupado = cad.length();
		if (espacioOcupado > 0)
		{
			archivoOcurrencias.seekg(offset);

			char * ocurrenciaLeida = (char*)calloc (espacioOcupado, sizeof(char));
			free(ocurrenciaLeida);
			archivoOcurrencias.write(ocurrenciaLeida, espacioOcupado);
			archivoOcurrencias.flush();
			archivoOcurrencias.close();

			// Agrego los datos en el archivo de espacios libres.
			actualizarEspaciosLibres(offset,espacioOcupado);
		}
	}
}

int HandlerArchivoOcurrencias::obtenerTamanioOcurrencia(Ocurrencia ocurrencia)
{
	int tamanioOcurrencia = 0;

	list<int> posiciones = ocurrencia.getPosiciones();

	int longitudPosiciones = 0;
	int longitudIdPalabra = 0;
	int longitudIdDocumento = 0;
	int longitudSeparadores = 2;

	stringstream ssIdPalabra,ssDocumento;

	ssIdPalabra<<ocurrencia.getIdPalabra();

	//ssDocumento<<ocurrencia.getIdDocumento();
	longitudIdDocumento = ocurrencia.getCodigoGammaDocumento().length();
	//longitudIdDocumento = ssDocumento.str().length();

	string cadenaIdPalabra = ssIdPalabra.str();
	longitudIdPalabra = cadenaIdPalabra.length();

	list<int> ::iterator itPosiciones;

	for(itPosiciones = posiciones.begin(); itPosiciones != posiciones.end(); ++ itPosiciones)
	{
		stringstream ssPosiciones;
		ssPosiciones<<*itPosiciones;
		string cadenaPosiciones = ssPosiciones.str();
		longitudPosiciones+= cadenaPosiciones.length();

	}


	longitudSeparadores+= (posiciones.size() -1);


	tamanioOcurrencia+= (longitudPosiciones + longitudIdPalabra + longitudIdDocumento + longitudSeparadores);

	return tamanioOcurrencia;
}

list<int> HandlerArchivoOcurrencias::obtenerListaDocumentos(list<int> offsets){

	list<int> documentos;
	list<int>::iterator it = offsets.begin();
	CodigoGamma codigoGamma;
	int numeroDocumento;

	while ( it != offsets.end()){
		Ocurrencia ocurrencia = this->buscarOcurrencia((*it));
		numeroDocumento = codigoGamma.interpretarConversion(ocurrencia.getCodigoGammaDocumento());
		//numeroDocumento = ocurrencia.getIdDocumento();
//		cout<<"Numero Documento " << numeroDocumento << "offset: " << *it << endl;
		documentos.push_back(numeroDocumento);
		++it;
	}

	//Ordeno la lista de documentos ascendentemente.
	documentos.sort();

	// Magia
	documentos.unique();

	return documentos;
}


Palabra HandlerArchivoOcurrencias::obtenerPalabra(list<int> offsets, string nombrePalabra)
{

	Palabra palabra;
	list<int>::iterator it = offsets.begin();

	CodigoGamma codigoGamma;
	int numeroDocumento;

	Ocurrencia ocurrencia;

	while ( it != offsets.end())
	{
		ocurrencia =this->buscarOcurrencia((*it));
		numeroDocumento = codigoGamma.interpretarConversion(ocurrencia.getCodigoGammaDocumento());

		//numeroDocumento = ocurrencia.getIdDocumento();
		//cout<<"Numero Documento"<<numeroDocumento<<endl;
		Aparicion aparicion;
		aparicion.setIdDocumento(numeroDocumento);
		aparicion.agregarPosiciones(ocurrencia.getPosiciones(),nombrePalabra,ocurrencia.getIdPalabra());
		palabra.agregarAparicion(aparicion);

		++it;
	}

	return palabra;
}
