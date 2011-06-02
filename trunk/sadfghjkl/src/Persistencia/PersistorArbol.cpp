#include "PersistorArbol.h"
#include "fstream"

PersistorArbol::PersistorArbol(string ruta, int tamanioBloque) {
	this->tamanioBloque = tamanioBloque;
	this->rutaOut = ruta;
	this->ruta = ruta + "_Nodos.txt";
	this->handlerBloque = new HandlerBloques(this->tamanioBloque, this->ruta);
}

PersistorArbol::~PersistorArbol() {
	delete this->handlerBloque;
}
bool PersistorArbol::guardarBloque (int nroBloque, CadenaBytes cadena){
	this->handlerBloque->guardar_bloque_arbol((char*)cadena.toString().c_str(), nroBloque);
	return true;
}
CadenaBytes PersistorArbol::leerBloque (int nroBloque){
	CadenaBytes cadena;
	int uno = (nroBloque) * tamanioBloque + tamanioBloque;
	int dos = this->handlerBloque->get_tam_arch_bloques();

	if  (uno <= dos){
		char buffer[this->tamanioBloque];
		this->handlerBloque->recuperar_bloque_arbol(nroBloque, buffer);
		cadena.agregar(buffer,this->tamanioBloque,0);
	}
	return cadena;
}
int PersistorArbol::getTamanioArchivo(){
	return this->handlerBloque->get_tam_arch_bloques();
}

int PersistorArbol::getCantidadBloques(){
	return ( this->handlerBloque->get_tam_arch_bloques() / this->tamanioBloque);
}

string PersistorArbol::getRuta(){
	return this->rutaOut;
}
