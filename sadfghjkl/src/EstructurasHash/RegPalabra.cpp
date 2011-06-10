
#include "RegPalabra.h"

RegPalabra::RegPalabra() : clave(-1), bloque_sig(-1) {}

RegPalabra::RegPalabra(int clave): clave(clave), bloque_sig(-1) {}

void RegPalabra::set_clave(int clave) {
	this->clave = clave;
}

void RegPalabra::set_bloque_sig(int bloque_sig) {
	this->bloque_sig = bloque_sig;
}

void RegPalabra::set_offsets(const list < int > & offsets) {
	this->offsets = offsets;
}

bool RegPalabra::esta_vacio() {
	if (this->bloque_sig == -1 && this->offsets.empty() == true)
		return true;
	return false;
}

int RegPalabra::get_tam() {
	CadenaBytes cadena_aux = this->Serializar();
	return cadena_aux.getTamanio();
}

void RegPalabra::agregar_nuevo_offset(int offset) {
	this->offsets.push_back(offset);
}

bool RegPalabra::eliminar_offset(int offset) {
	list < int > ::iterator it;

	it = this->offsets.begin();
	while (it != this->offsets.end() && *it != offset)
		++ it;

	if (it != this->offsets.end() && *it == offset) {
		this->offsets.erase(it);
		return true;
	}

	return false;
}

CadenaBytes RegPalabra::Serializar() {
	CadenaBytes cadena;

	cadena.agregarAlFinal(&this->clave, sizeof(this->clave));

	cadena.agregarAlFinal(&this->bloque_sig, sizeof(this->bloque_sig));

	int tam = this->offsets.size();
	cadena.agregarAlFinal(&tam, sizeof(tam));

	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
		cadena.agregarAlFinal(&(*it), sizeof(*it));

	return cadena;
}

bool RegPalabra::Hidratar(CadenaBytes& cadena) {
	this->offsets.clear();

	int offset = 0;

	this->clave = cadena.leerEntero(offset);
	offset += sizeof(this->clave);

	this->bloque_sig = cadena.leerEntero(offset);
	offset += sizeof(this->bloque_sig);

	int tam = cadena.leerEntero(offset);
	offset += sizeof(tam);

	int aux;
	for (int i = 0; i < tam; ++ i) {
		aux = cadena.leerEntero(offset);
		offset += sizeof(aux);
		this->offsets.push_back(aux);
	}

	return true;
}

void RegPalabra::toString(ostream& os) {
	os << "   Registro --> " << endl;
	os << "     Clave:   " << this->clave << endl;
	os << "     Bloque siguiente:   " << this->bloque_sig << endl;
	os << "     Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;

	list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		os << "     Offset #" << i << ":   " << *it << endl;
		++ i;
	}
}
