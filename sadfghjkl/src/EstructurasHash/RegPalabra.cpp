
#include "RegPalabra.h"

int RegPalabra::get_tam() {
	int tam = 0;

	stringstream ss1;
	ss1 << this->clave << ' ';
	string s(ss1.str());
	tam += s.size();
	s.clear();

	stringstream ss2;
	ss2 << this->bloque_sig << ' ';
	s = ss2.str();
	tam += s.size();
	s.clear();

	stringstream ss3;
	ss3 << this->offsets.size() << ' ';
	s = ss3.str();
	tam += s.size();
	s.clear();

	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
	{
		stringstream ss4;
		ss4 << *it << ' ';
		s = ss4.str();
		tam += s.size();
		s.clear();
	}

	return tam;
}

void RegPalabra::set_bloque_sig(int bloque_sig) {
	this->bloque_sig = bloque_sig;
}

void RegPalabra::set_offsets(list < int > & offsets) {
	this->offsets = offsets;
}

void RegPalabra::agregar_nuevos_offsets(list < int > & offsets) {
	list < int > ::iterator it;
	for (it = offsets.begin(); it != offsets.end(); ++ it)
		this->offsets.push_back(*it);
}

bool RegPalabra::eliminar_offset(int offset) {
	list < int > ::iterator it;

	it = this->offsets.begin();
	while (it != this->offsets.end() && *it != offset)
		++ it;

	if (*it == offset) {
		this->offsets.erase(it);
		return true;
	}
	return false;
}

void RegPalabra::serializar(char* buffer, unsigned int& offset) {
	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);
	Persistencia::PonerEnteroEnChar(buffer, offset, this->bloque_sig);

	Persistencia::PonerEnteroEnChar(buffer, offset, this->offsets.size());
	list < int > ::iterator it;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it)
		Persistencia::PonerEnteroEnChar(buffer, offset, (*it));
}

void RegPalabra::hidratar(char* buffer, unsigned int& offset) {
	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	this->bloque_sig = Persistencia::getEnteroDesdeBuffer(buffer, offset);

	int tam_offsets = Persistencia::getEnteroDesdeBuffer(buffer, offset);
	for (int i = 0; i < tam_offsets; ++ i)
		this->offsets.push_back(Persistencia::getEnteroDesdeBuffer(buffer,offset));
}

void RegPalabra::toString(ofstream& fo) {

	fo << " Registro --> " << endl;
	fo << " Clave:   " << this->clave << endl;
	fo << " Bloque siguiente:   " << this->bloque_sig << endl;
	fo << " Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;

/*	list < int > ::iterator it;
	int i = 0;
	for (it = this->offsets.begin(); it != this->offsets.end(); ++ it) {
		cout << " Offset #" << i << ":   " << *it << endl;
		++ i;
	}
*/
}

void RegPalabra::agregar_nuevo_offset(int offset) {
	this->offsets.push_back(offset);
}
