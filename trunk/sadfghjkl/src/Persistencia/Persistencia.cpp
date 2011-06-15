#include "Persistencia.h"

Persistencia::Persistencia() {}

Persistencia::Persistencia(string bytes){
	this->bytes = bytes;
}

Persistencia::Persistencia(const Persistencia &cadDeBytes) {
	this->bytes = cadDeBytes.bytes;
}

Persistencia::~Persistencia() {}

bool Persistencia::estaVacia() const {
	return (this->getTamanio() == 0);
}

string Persistencia::toString() const {
	return this->bytes;
}

bool Persistencia::agregar(const Persistencia& bytes,unsigned int posicion) {
	bool exito = true;
	if (posicion > this->bytes.length()) {
		exito = false;
	}else{
		this->bytes.insert(posicion,bytes.toString());
	}
	return exito;
}

bool Persistencia::agregar(const string &bytes,unsigned int posicion) {
	bool exito = true;
	if (posicion > this->bytes.length()){
		exito = false;
	}else{
		this->bytes.insert(posicion,bytes);
	}
	return exito;
}

bool Persistencia::agregar(void* valor, unsigned int tamanio, unsigned int posicion){
	bool exito = true;
		string cadena;
		char* buffer = (char*)malloc(tamanio);
		memcpy(buffer,valor,tamanio);
		cadena.append(buffer,tamanio);
		exito = agregar(cadena,posicion);
		free(buffer);
	return exito;
}
void Persistencia::transformarAFrontCoding(string primera, string ruta){
	if (!estaTransformada(this->bytes)){
		FrontCoding* fc = new FrontCoding(ruta);
		string modificada = fc->pasarAFrontCoding(primera, this->bytes);
		this->setBytes(modificada);
		modificada.clear();
		delete fc;
	}
}

void Persistencia::sacarElFrontCoding(string palabra, string ruta){
	if (estaTransformada(this->bytes)){
		FrontCoding* fc = new FrontCoding(ruta);
		string modificada = fc->interpretarFrontCoding(palabra);
		this->setBytes(modificada);
		modificada.clear();
		delete fc;
	}
}

bool Persistencia::estaTransformada(string cadena){
	if (strchr(cadena.c_str(), 46)) return true;
	return false;
}
bool Persistencia::agregarAlFinal(const string &bytes) {
	this->bytes.append(bytes);
	return true;
}

bool Persistencia::agregarAlFinal(const Persistencia& bytes) {
	bool exito = agregar(bytes,getTamanio());
	return exito;
}

bool Persistencia::agregarAlFinal(void* valor,int tamanio){
	bool exito = agregar(valor,tamanio,this->getTamanio());
	return exito;
}

bool Persistencia::reemplazar(const string &bytes, unsigned int posicion) {
	bool exito = true;
	if ((posicion + bytes.length()) > this->getTamanio()) {
		exito = false;
	}else {
		this->eliminar(posicion,posicion + bytes.length() -1);
		this->agregar(bytes,posicion);
	}
	return exito;
}

bool Persistencia::reemplazar(const Persistencia &cadDeBytes, unsigned int posicion){
	bool exito = true;
	exito = reemplazar(cadDeBytes.toString(),posicion);
	return exito;
}

bool Persistencia::eliminar(unsigned int inicio,unsigned int fin) {
	bool exito = true;
	if ((inicio > fin) || ((fin > this->bytes.length()) || ( fin > this->bytes.length()))) {
		exito = false;
	}else{
		this->bytes.erase(inicio,fin - inicio + 1);
	}
	return exito;
}

bool Persistencia::leer(char* buffer, unsigned int inicio,unsigned int tamanio)const {
	bool exito = true;
	Persistencia aux = this->leer(inicio,tamanio);
	if(aux.getTamanio()==0){
		exito = false;
	}else{
		memcpy(buffer,aux.bytes.data(),tamanio);
		exito = true;
	}
	return exito;
}

Persistencia Persistencia::leer(unsigned int inicio, unsigned int tamanio) const {
	if (inicio + tamanio > getTamanio()) {
		return Persistencia("");
	}
	return this->bytes.substr(inicio,tamanio);
}

int Persistencia::leerEntero(unsigned int inicio){
	int n = -1;
	char buffer[sizeof(int)];
	bool leido = this->leer(buffer,inicio,sizeof(int));
	if(leido) memcpy(&n,buffer,sizeof(int));
	return n;
}

bool Persistencia::vaciar() {
	this->bytes.clear();
	return true;
}

unsigned int Persistencia::getTamanio() const {
	return this->bytes.length();
}

void Persistencia::setBytes(const string &bytes) {
	this->bytes = bytes;
}
