/*
 * HandlerListasInvertidas.cpp
 *
 *  Created on: 29/05/2011
 *      Author: lucas
 */

#include "HandlerListasInvertidas.h"

HandlerListasInvertidas::HandlerListasInvertidas() {
	std::fstream fio;
	fio.open(PATH_INDICE_INVERTIDO, std::ios_base::in | std::ios_base::out);
	if ( !fio.is_open() ){
		this->crearArchivo();
	}else{
		fio.clear();
	}
}

HandlerListasInvertidas::~HandlerListasInvertidas() {
}

void HandlerListasInvertidas::construirListaInvertida(list<Ocurrencia> ocurrencias){
	list<Ocurrencia>::iterator it = ocurrencias.begin();
	list<int> listaInvertida;
	int idAux = (*it).getIdPalabra();
	int primero = (*it).getIdDocumento();
	int offset = 0;
	guardarPrimero(primero);

	listaInvertida.push_back((*it).getIdDocumento());
	++it;
	while( it != ocurrencias.end()){
		if ((*it).getIdPalabra() == idAux){
			// Sigo armando la lista de documento si es el mismo termino
			listaInvertida.push_back((*it).getIdDocumento());

		}else{
			// Guardo en el archivo de lista invertida
			string listaEnGamma = comprimirListaInvertida(listaInvertida, primero);
			int offsetALista  = insertarLista(listaEnGamma, offset);
			stringstream ss;
			ss << idAux << "." << offsetALista << "\n";
			insertarLineaIndice(ss.str());
			listaInvertida.clear();
			listaInvertida.push_back((*it).getIdDocumento());
			idAux = (*it).getIdPalabra();
		}
		++it;
	}
	--it;
	string listaEnGamma = comprimirListaInvertida(listaInvertida, primero);
	int offsetALista = insertarLista(listaEnGamma, offset);
	if ( offset != ERROR){
		stringstream ss;
		ss << idAux << "-->" << offsetALista << "\n";
		insertarLineaIndice(ss.str());
	}

}

string HandlerListasInvertidas::comprimirListaInvertida(list<int> listaInvertida, int primero){
	CodigoGamma gamma;
	return (gamma.comprimirLista(listaInvertida, primero));
}

int HandlerListasInvertidas::insertarLista(string listaEnGamma, int& offset){
	int retorno  = 0;
	std::fstream fio_lista;
	fio_lista.open(PATH_LISTAS_INVERTIDAS, std::ios_base::in | std::ios_base::out);
	if (!fio_lista.is_open()){
		fio_lista.open(PATH_LISTAS_INVERTIDAS, std::ios_base::out);
		fio_lista.close();
		fio_lista.open(PATH_LISTAS_INVERTIDAS, std::ios_base::in | std::ios_base::out);
	}

	// Me paro en ese offset y grabo la cadena
	fio_lista.seekg(offset);
	fio_lista.write(listaEnGamma.c_str(), listaEnGamma.length());
	fio_lista.flush();
	fio_lista.close();
	retorno  = offset;

	// Actualizo el offset y lo guardo en la primer linea
	offset += listaEnGamma.length();
	return retorno;
}
void HandlerListasInvertidas::insertarLineaIndice(string lineaIndice){
	std::ofstream fio;
	fio.open(PATH_INDICE_INVERTIDO, std::ios_base::app);
	if (fio.is_open()){
		fio.open(PATH_INDICE_INVERTIDO, std::ios_base::out);
		fio.close();
		fio.open(PATH_INDICE_INVERTIDO, std::ios_base::app);
	}
	fio.write(lineaIndice.c_str(), lineaIndice.length());
	fio.flush();
	fio.close();
}

void HandlerListasInvertidas::crearArchivo(){
	std::ofstream fio;
	fio.open(PATH_INDICE_INVERTIDO);
	stringstream ss;
	ss << 0 << "\n";
	fio.seekp(0);
	fio.write(ss.str().c_str(), ss.str().length());
	fio.flush();
	fio.close();
}

void HandlerListasInvertidas::guardarPrimero(int primero){
	std::fstream fio;
	fio.open(PATH_INDICE_INVERTIDO, std::ios_base::in | std::ios_base::out);
	if (fio.is_open()){
		// Me posiciono en el archivo de listasInvertidas para obtener el offset donde escribir
		fio.seekg(0);
		stringstream ss;
		ss << primero << "\n";
		fio.seekg(0);
		fio.write(ss.str().c_str(), ss.str().length());
		fio.flush();
		fio.close();
	}
}
