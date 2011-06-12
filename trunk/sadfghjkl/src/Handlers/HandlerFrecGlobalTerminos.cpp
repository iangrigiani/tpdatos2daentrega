#include "HandlerFrecGlobalTerminos.h"

HandlerFrecGlobalTerminos::HandlerFrecGlobalTerminos() {
}

HandlerFrecGlobalTerminos::HandlerFrecGlobalTerminos(vector<int> idTerminos){
	this->idTerminos = idTerminos;
	this->arbolPesos = new ArbolBMas(PATH_ARCHIVO_FREC_GLOB, 1);
	this->calc       = new CalculadorDePesoGlobal();
}


HandlerFrecGlobalTerminos::~HandlerFrecGlobalTerminos() {
	delete this->arbolPesos;
	delete this->calc;
}


void HandlerFrecGlobalTerminos::actualizarPesosYNormas(int idDocumento){
	int i = 0 , frecGlobal= 0;
	float pesoGlobal= 0, norma = 0;

	while (i< (this->idTerminos.size()) ){
		frecGlobal = this->incrementarPesoTermino(idTerminos[i]);
		pesoGlobal = this->calc->calcularPesoGlobalTermino(frecGlobal);
		pesoGlobal = pow(pesoGlobal, 2);
		norma += pesoGlobal;
		i++;
	}
	norma = sqrt(norma);
	norma = round(norma*1000)/1000;
	this->persistirNorma(idDocumento, norma);

}


int HandlerFrecGlobalTerminos::incrementarPesoTermino(int IDTermino){
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos*>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave); //Debería devolver uno o ninguno
	int pesoActual = 1;

	if (listaElementos!=NULL){

		Elementos elemento = *(*(listaElementos->begin()));
		CadenaBytes* pesoActualCad = elemento.getID();
		string pesoActualStr = pesoActualCad->toString();
		pesoActual = atoi(pesoActualStr.c_str());
		pesoActual++;

		string pesoNuevo = intToString(pesoActual);
		CadenaBytes* pesoNuevoCad = new CadenaBytes(pesoNuevo);
		elemento.setID(pesoNuevoCad);
		this->arbolPesos->modificar(&elemento);


	}else{
		CadenaBytes* ID = new CadenaBytes (intToString(IDTermino));
		CadenaBytes* peso = new CadenaBytes(intToString(pesoActual));
		Elementos* elemento = new Elementos (clave, ID, peso);
		this->arbolPesos->insertar(elemento);

	}
	delete clave;
	return pesoActual;
}


int HandlerFrecGlobalTerminos::decrementarPesoTermino (int IDTermino){
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos*>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave); //Debería devolver uno o ninguno

	if (listaElementos!=NULL){

		Elementos elemento = *(*(listaElementos->begin()));
		CadenaBytes* pesoActualCad = elemento.getID();
		string pesoActualStr = pesoActualCad->toString();
		int pesoActual = atoi(pesoActualStr.c_str());
		pesoActual--;

		string pesoNuevo = intToString(pesoActual);
		CadenaBytes* pesoNuevoCad = new CadenaBytes(pesoNuevo);
		elemento.setID(pesoNuevoCad);
		this->arbolPesos->modificar(&elemento);
		return OKEY;

	}else{
		return ERROR;
	}

}


int HandlerFrecGlobalTerminos::buscarPesoTermino(int IDTermino){
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos*>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave);
	Elementos elemento = *(*(listaElementos->begin()));
	CadenaBytes* pesoActualCad = elemento.getID();
	string pesoActualStr = pesoActualCad->toString();
	return atoi(pesoActualStr.c_str());

}

int HandlerFrecGlobalTerminos::eliminarNormaGuardada(int idDocumento){
	int puntero = buscarRegistro(idDocumento);
	string linea = "\n";
	ofstream archivoLog;

	if (puntero != ERROR){
		//si existe el ID, solamente limpio las estructuras
		archivoLog.open(PATH_ARCHIVO_NORMA, std::ios_base::in | std::ios_base::out);
		if (!archivoLog.is_open()){
			archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::out);
			archivoLog.close();
			archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::in | std::ios_base::out);
		}
		archivoLog.seekp(puntero);
		archivoLog.write(linea.c_str(), linea.length());
	    archivoLog.close();
	}

}


/*private*/
string HandlerFrecGlobalTerminos::intToString(int integer){
	stringstream ss;
	ss << integer;
	return ss.str();
}


string HandlerFrecGlobalTerminos::lineaArchivoNorma(int idDocument, float norma){
	stringstream ss;
	ss << idDocument<<"|"<<norma<< "\n";
	return ss.str();
}


void HandlerFrecGlobalTerminos::persistirNorma(int idDocumento, float norma){
	string linea = lineaArchivoNorma(idDocument, norma);
	ofstream archivoLog;

	archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::app);
	if (!archivoLog.is_open()){
		archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::out);
		archivoLog.close();
		archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::app);
	}
	archivoLog.write(linea.c_str(), linea.length());
	archivoLog.close();

}
