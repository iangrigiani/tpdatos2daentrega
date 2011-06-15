#include "Clave.h"

using std::string;


Clave::Clave()
{
	this->clave = "";
}

Clave::Clave(string clave)
{
	this->clave = clave;
}

string Clave::toString() const{
	return this->clave;
}

/*
 * Hay que guardar el tamaño tambien.
 */
Persistencia Clave::Serializar()
{
	Persistencia cadena;
	char tamano = this->getTamanio();
	cadena.agregarAlFinal(&tamano,TAM_LONG_CLAVE);
	cadena.agregarAlFinal(this->clave);
	return cadena;
}

bool Clave::Hidratar(Persistencia &cadena){
	bool exito;
	if (cadena.getTamanio() < TAM_LONG_CLAVE){
		exito = false;
	}else{
		this->clave = "";
		if(cadena.getTamanio() > TAM_LONG_CLAVE){
			char tamano;
			cadena.leer(&tamano,0,TAM_LONG_CLAVE);
			int size = int(tamano);
			char* buffer = (char*)malloc(size);
			cadena.leer(buffer,TAM_LONG_CLAVE,size);
			this->clave.append(buffer,size);
			free(buffer);
		}
		exito = true;
	}
	return exito;
}

Clave* Clave::Clonar(){
	return new Clave(this->clave);
}

int Clave::getTamanio(){
	return (clave.size());
}

string Clave::getClave() const
{
	return clave;
}

void Clave::setClave(string clave)
{
    this->clave = clave;
}

Clave::~Clave() {

}

bool Clave::operator == (const Clave& otra) const{
	return (this->clave == otra.clave);
}

bool Clave::operator != (const Clave& otra) const{
	return (this->clave != otra.clave);
}

bool Clave::operator < (const Clave& otra) const{
	return (this->clave < otra.clave);
}

bool Clave::operator > (const Clave& otra) const{
	return (this->clave > otra.clave);
}

bool Clave::operator <= (const Clave& otra) const{
	return (this->clave <= otra.clave);
}

