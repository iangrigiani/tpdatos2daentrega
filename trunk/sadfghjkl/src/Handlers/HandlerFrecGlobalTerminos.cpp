#include "HandlerFrecGlobalTerminos.h"

HandlerFrecGlobalTerminos::HandlerFrecGlobalTerminos() {
}
HandlerFrecGlobalTerminos::HandlerFrecGlobalTerminos(vector<int> idTerminos){
	this->idTerminos = idTerminos;
	this->arbolPesos = new ArbolBMas(PATH_ARCHIVO_FREC_GLOB, 1);
}

HandlerFrecGlobalTerminos::~HandlerFrecGlobalTerminos() {
	delete this->arbolPesos;
}

void HandlerFrecGlobalTerminos::actualizarPesosTerminos (){
	int i = 0 ;
	while (i< (this->idTerminos.size()) ){
		this->incrementarPesoTermino(idTerminos[i]);
		i++;
	}
}


void HandlerFrecGlobalTerminos::incrementarPesoTermino (int IDTermino){
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave); //Debería devolver uno o ninguno

	if (listaElementos!=NULL){

		Elementos elemento = *(listaElementos->begin());
		CadenaBytes* pesoActualCad = elemento.getID();
		string pesoActualStr = pesoActualCad->toString();
		int pesoActual = atoi(pesoActualStr.c_str());
		pesoActual++;

		string pesoNuevo = intToString(pesoActual);
		CadenaBytes* pesoNuevoCad = new CadenaBytes(pesoNuevo);
		elemento.setID(pesoNuevoCad);
		this->arbolPesos->modificar(&elemento);

	}else{
		CadenaBytes* ID = new CadenaBytes (intToString(IDTermino));
		CadenaBytes* peso = new CadenaBytes(intToString(1));
		Elementos* elemento = new Elementos (clave, ID, peso);
		this->arbolPesos->insertar(elemento);
	}
	delete clave;
}



int HandlerFrecGlobalTerminos::decrementarPesoTermino (int IDTermino){
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave); //Debería devolver uno o ninguno

	if (listaElementos!=NULL){

		Elementos elemento = *(listaElementos->begin());
		CadenaBytes* pesoActualCad = elemento.getID();
		string pesoActualStr = pesoActualCad->toString();
		int pesoActual = atoi(pesoActualStr.c_str());
		pesoActual--;

		string pesoNuevo = intToString(pesoActual);
		CadenaBytes* pesoNuevoCad = new CadenaBytes(pesoNuevo);
		elemento.setID(pesoNuevoCad);
		this->arbolPesos->modificar(&elemento);
		return 1;

	}else{
		return ERROR;
	}

}

int HandlerFrecGlobalTerminos::buscarPesoTermino(int IDTermino){

	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave);
	Elementos elemento = *(listaElementos->begin());
	CadenaBytes* pesoActualCad = elemento.getID();
	string pesoActualStr = pesoActualCad->toString();
	return atoi(pesoActualStr.c_str());

}


/*private*/
string HandlerFrecGlobalTerminos::intToString(int integer){
	stringstream ss;
	ss << integer;
	return ss.str();
}


