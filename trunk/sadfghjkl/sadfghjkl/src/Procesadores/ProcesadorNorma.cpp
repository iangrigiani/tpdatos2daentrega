#include "ProcesadorNorma.h"

ProcesadorNorma::ProcesadorNorma(){
	this->calc       = new CalculadorDePesoGlobal();
}


ProcesadorNorma::~ProcesadorNorma() {
	delete this->calc;
}


/*Metodos de norma*/
void ProcesadorNorma::guardarIDTerminoFrecuente(int idDocumento, int idTermino){
	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);
	hash.alta(idDocumento, idTermino);
}


int ProcesadorNorma::consultarNorma(int idDocumento){

	int idTermino=0 , norma= 0;
	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);

	idTermino = hash.consultar(idDocumento);
	norma = this->buscarPesoTermino(idTermino);

	return norma;
}


void ProcesadorNorma::eliminarIDTerminoFrecuente(int idDocumento){

	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);
	hash.baja(idDocumento);
}


/*Metodos de pesos globales*/
void ProcesadorNorma::actualizarPesos(int idDocumento, int* lista, int tamanioLista){
	int i = 0;

	while (i < tamanioLista ){
		this->incrementarPesoTermino(lista[i]);
	}
}


int ProcesadorNorma::incrementarPesoTermino(int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, PATH_ID_PESOS, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	Persistencia * cadenaDato = new Persistencia(intToString(IDTermino));
	Persistencia * cadenaID = new Persistencia(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);
	int pesoActual = 1;

	if (!arbol.incrementarID(&elemento, pesoActual)){
		elemento.setID(new Persistencia(intToString(pesoActual)));
		arbol.insertar(&elemento, false);
	}

	return pesoActual;
}


int ProcesadorNorma::buscarPesoTermino(int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, PATH_ID_PESOS, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos*>* listaElementos = new list<Elementos*>();
	arbol.buscar(listaElementos, clave);

	if ( listaElementos->size() > 0){

		Elementos elemento = *(*(listaElementos->begin()));
		delete listaElementos;
		return atoi(elemento.getID()->toString().c_str());
	}
	return ERROR;
}


int ProcesadorNorma::decrementarPesoTermino (int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, PATH_ID_PESOS, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	Persistencia * cadenaDato = new Persistencia(intToString(IDTermino));
	Persistencia * cadenaID = new Persistencia(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);

	if (arbol.decrementarID(&elemento)) return OKEY;
		return ERROR;

}


/*private*/
string ProcesadorNorma::intToString(int integer){
	stringstream ss;
	ss << integer;
	return ss.str();
}
