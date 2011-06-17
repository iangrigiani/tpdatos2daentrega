#include "ProcesadorNorma.h"

ProcesadorNorma::ProcesadorNorma(){
	this->calc       = new CalculadorDePesoGlobal();
}


ProcesadorNorma::~ProcesadorNorma() {
	delete this->calc;
}


void ProcesadorNorma::actualizarPesosYNormas(int idDocumento, int* lista, int tamanioLista){
	int frecGlobal= 0;
	int i = 0;
	float pesoGlobal= 0, norma = 0;

//	cout << tamanioLista << endl;
//	for ( int i = 0; i < tamanioLista; ++i){
//		cout << lista[i] << endl;
//	}

	while (i < tamanioLista ){
		frecGlobal = this->incrementarPesoTermino(lista[i]);
		pesoGlobal = this->calc->calcularPesoGlobalTermino(frecGlobal);
		pesoGlobal = pow(pesoGlobal, 2);
		norma += pesoGlobal;
		i++;
		cout << "Actualizando pesos y Norma de documento " << idDocumento << " ..." << (int) (((i+1) * 100 / tamanioLista)+1) << "%\r";
	}
	norma = sqrt(norma);
	norma = round(norma*1000)/1000;
	this->persistirNorma(idDocumento, norma);

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


int ProcesadorNorma::decrementarPesoTermino (int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, PATH_ID_PESOS, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	Persistencia * cadenaDato = new Persistencia(intToString(IDTermino));
	Persistencia * cadenaID = new Persistencia(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);
	if (arbol.decrementarID(&elemento)) return OKEY;
		return ERROR;
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

void ProcesadorNorma::eliminarNormaGuardada(int idDocumento){

	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);
	hash.baja(idDocumento);
}


string ProcesadorNorma::intToString(int integer){
	stringstream ss;
	ss << integer;
	return ss.str();
}

void ProcesadorNorma::persistirNorma(int idDocumento, float norma){

	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);

	stringstream nn;
	nn << norma;

	stringstream ss;
	ss << idDocumento;

	hash.alta(idDocumento, atoi(nn.str().c_str()));
}

float ProcesadorNorma::consultarNorma(int idDocumento){

	float retorno;
	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);

	stringstream ss;
	ss << idDocumento;

	retorno = (float)hash.consultar(idDocumento);

	return retorno;
}
