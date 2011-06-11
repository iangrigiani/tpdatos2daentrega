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
	// TODO Buscar elemento en el arbol
	Clave clave(IDTerminoToString(IDTermino));

/*
	pair<Elementos*, IteradorArbolBMas*> resultado = this->arbolPesos->buscar(clave); //Debería devolver uno o ninguno

	if (resultado!=NULL){
		//TODO Extraer elemento del par
		Elementos* elemento = resultado.first();
		int pesoActual = atoi(elemento->getID().c_str());
		pesoActual++;

		stringstream ss2;
		ss2<<pesoActual;
		string pesoNuevo = ss2.str();
		elemento->setID(*pesoNuevo);
		this->arbolPesos->modificar(elemento);

	}else{
		//TODO usar archivo de ultimo ID para generar clave
		Elementos* elemento = new Elementos (clave, ID, '1');
		this->arbolPesos->insertar(elemento);
	}
*/
}



int HandlerNormasAInfinito::decrementarPesoTermino (int IDTermino){
	Clave clave(IDTerminoToString(IDTermino));

/*
	pair<Elementos*, IteradorArbolBMas*> resultado = this->arbolPesos->buscar(clave); //Debería devolver uno o ninguno

	if (resultado!=NULL){
		//TODO Extraer elemento del par
		Elementos* elemento = resultado.first();
		int pesoActual = atoi(elemento->getID().c_str());
		pesoActual--;

		stringstream ss2;
		ss2<<pesoActual;
		string pesoNuevo = ss2.str();
		elemento->setID(*pesoNuevo);
		this->arbolPesos->modificar(elemento);
		return OK;

	}else{
		return ERROR;
	}
*/
}

int HandlerNormasAInfinito::buscarPesoTermino(int IDTermino){
	int peso = 0;
	Clave clave(IDTerminoToString(IDTermino));
/*
	pair<Elementos*, IteradorArbolBMas*> resultado = this->arbolPesos->buscar(clave);
	Elementos* elemento = resultado.first();
	peso = atoi(elemento->getID().c_str() );*/
	return peso;
}


/*private*/
string HandlerNormasAInfinito::IDTerminoToString(int IDTermino){
	stringstream ss;
	ss << IDTermino;
	return ss.str();
}
