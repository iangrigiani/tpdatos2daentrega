#include "HandlerNormasAInfinito.h"

HandlerNormasAInfinito::HandlerNormasAInfinito() {
}
HandlerNormasAInfinito::HandlerNormasAInfinito(vector<int> idTerminos){
	this->idTerminos = idTerminos;
	this->arbolPesos = new ArbolBMas(PATH_ARCHIVO_NORMA, 1);
}

HandlerNormasAInfinito::~HandlerNormasAInfinito() {
	delete this->arbolPesos;
}

void HandlerNormasAInfinito::actualizarPesosTerminos (){
	int i = 0 ;
	while (i< (this->idTerminos.size()) ){
		this->incrementarPesoTermino(idTerminos[i]);
		i++;
	}
}


void HandlerNormasAInfinito::incrementarPesoTermino (int IDTermino){
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



int HandlerNormasAInfinito::decrementarPesoTermino (int IDTermino){
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

int HandlerNormasAInfinito::buscarPesoTermino(int IDTermino){

	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos>* listaElementos;
	this->arbolPesos->buscar(listaElementos, clave);
	Elementos elemento = *(listaElementos->begin());
	CadenaBytes* pesoActualCad = elemento.getID();
	string pesoActualStr = pesoActualCad->toString();
	return atoi(pesoActualStr.c_str());

}


/*private*/
string HandlerNormasAInfinito::intToString(int integer){
	stringstream ss;
	ss << integer;
	return ss.str();
}


