#include "ProcesadorNorma.h"

ProcesadorNorma::ProcesadorNorma() {
}

ProcesadorNorma::ProcesadorNorma(vector<int> idTerminos){
	this->idTerminos = idTerminos;
//	this->arbolPesos = new ArbolBMas(PATH_ARCHIVO_FREC_GLOB, 1);
	this->calc       = new CalculadorDePesoGlobal();
}


ProcesadorNorma::~ProcesadorNorma() {
//	delete this->arbolPesos;
	delete this->calc;
}


void ProcesadorNorma::actualizarPesosYNormas(int idDocumento){
	int i = 0 , frecGlobal= 0;
	float pesoGlobal= 0, norma = 0;

	while (i< (int)(this->idTerminos.size()) ){
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


int ProcesadorNorma::incrementarPesoTermino(int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	CadenaBytes * cadenaDato = new CadenaBytes(intToString(IDTermino));
	CadenaBytes * cadenaID = new CadenaBytes(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);
	int pesoActual = 1;


//	Clave* clave = new Clave(intToString(IDTermino));
//	list<Elementos*>* listaElementos = new list<Elementos*>();
//	this->arbolPesos->buscar(listaElementos, clave); //Debería devolver uno o ninguno

//	if (listaElementos->size() > 0){
	if (!arbol.incrementarID(&elemento, pesoActual)){
		elemento.setID(new CadenaBytes(intToString(pesoActual)));
		arbol.insertar(&elemento);
	}
//		Elementos elemento = *(*(listaElementos->begin()));
//		CadenaBytes* pesoActualCad = elemento.getID();
//		string pesoActualStr = pesoActualCad->toString();
//		pesoActual = atoi(pesoActualStr.c_str());
//		pesoActual++;
//
//		string pesoNuevo = intToString(pesoActual);
//		CadenaBytes* pesoNuevoCad = new CadenaBytes(pesoNuevo);
//		elemento.setID(pesoNuevoCad);
//		delete listaElementos;
//		this->arbolPesos->modificar(&elemento);

//
//	}else{
//		CadenaBytes* ID = new CadenaBytes (intToString(IDTermino));
//		CadenaBytes* peso = new CadenaBytes(intToString(pesoActual));
//		Elementos* elemento = new Elementos (clave, ID, peso);
//		this->arbolPesos->insertar(elemento);
//
//	}

	return pesoActual;
}


int ProcesadorNorma::decrementarPesoTermino (int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	CadenaBytes * cadenaDato = new CadenaBytes(intToString(IDTermino));
	CadenaBytes * cadenaID = new CadenaBytes(" ");
	Elementos elemento(clave, cadenaDato, cadenaID);

//	Clave* clave = new Clave(intToString(IDTermino));
//	list<Elementos*>* listaElementos = new list<Elementos*>();
//	this->arbolPesos->buscar(listaElementos, clave); //Debería devolver uno o ninguno

//	if (listaElementos!=NULL){
	if (arbol.decrementarID(&elemento)) return OKEY;
		return ERROR;
//		Elementos elemento = *(*(listaElementos->begin()));
//		CadenaBytes* pesoActualCad = elemento.getID();
//		string pesoActualStr = pesoActualCad->toString();
//		int pesoActual = atoi(pesoActualStr.c_str());
//		pesoActual--;
//
//		string pesoNuevo = intToString(pesoActual);
//		CadenaBytes* pesoNuevoCad = new CadenaBytes(pesoNuevo);
//		elemento.setID(pesoNuevoCad);
//		this->arbolPesos->modificar(&elemento);
//		delete listaElementos;
//		return OKEY;
//
//	}else{
//		return ERROR;
//	}

}

int ProcesadorNorma::buscarPesoTermino(int IDTermino){

	ArbolBMas arbol(PATH_ARCHIVO_FREC_GLOB, 1);
	Clave* clave = new Clave(intToString(IDTermino));
	list<Elementos*>* listaElementos = new list<Elementos*>();
	arbol.buscar(listaElementos, clave);

	if ( listaElementos->size() > 0){

		Elementos elemento = *(*(listaElementos->begin()));
		delete listaElementos;
		return atoi(elemento.getID()->toString().c_str());

	}

	return ERROR;
//	this->arbolPesos->buscar(listaElementos, clave);
//	CadenaBytes* pesoActualCad = elemento.getID();
//	string pesoActualStr = pesoActualCad->toString();

}

void ProcesadorNorma::eliminarNormaGuardada(int idDocumento){

	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);
	stringstream ss;
	ss << idDocumento;

	hash.baja(ss.str());
//	int puntero = 0;
//	// TODO ESTO NO COMPILA ----->>>> puntero = buscarRegistro(idDocumento);
//	string linea = "\n";
//	ofstream archivoLog;
//
//	if (puntero != ERROR){
//		//si existe el ID, solamente limpio las estructuras
//		archivoLog.open(PATH_ARCHIVO_NORMA, std::ios_base::in | std::ios_base::out);
//		if (!archivoLog.is_open()){
//			archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::out);
//			archivoLog.close();
//			archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::in | std::ios_base::out);
//		}
//		archivoLog.seekp(puntero);
//		archivoLog.write(linea.c_str(), linea.length());
//	    archivoLog.close();
//	}
//	return OKEY;
}


/*private*/
string ProcesadorNorma::intToString(int integer){
	stringstream ss;
	ss << integer;
	return ss.str();
}

//
//string ProcesadorNorma::lineaArchivoNorma(int idDocument, float norma){
//	stringstream ss;
//	ss << idDocument<<"|"<<norma<< "\n";
//	return ss.str();
//}


void ProcesadorNorma::persistirNorma(int idDocumento, float norma){

	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);

	stringstream nn;
	nn << norma;

	stringstream ss;
	ss << idDocumento;

	hash.alta(ss.str(), atoi(nn.str().c_str()));
//	string linea = lineaArchivoNorma(idDocumento, norma);
//	ofstream archivoLog;
//
//	archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::app);
//	if (!archivoLog.is_open()){
//		archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::out);
//		archivoLog.close();
//		archivoLog.open(PATH_ARCHIVO_NORMA,std::ios_base::app);
//	}
//	archivoLog.write(linea.c_str(), linea.length());
//	archivoLog.close();

}

float ProcesadorNorma::consultarNorma(int idDocumento){

	float retorno;
	HashTitulo hash(NOM_BLOQUES_NORMA, NOM_ESP_LIBRE_NORMA, NOM_TABLA_NORMA);

	stringstream ss;
	ss << idDocumento;

	retorno = (float)hash.consultar(ss.str());

	return retorno;
}