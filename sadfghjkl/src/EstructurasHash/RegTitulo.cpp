
#include "RegTitulo.h"

int RegTitulo::get_tam() const {

	int tam = 0;

	stringstream ss1;
	ss1 << this->clave << ' ';
	string s(ss1.str());
	tam += s.size();
	s.clear();

	stringstream ss2;
	ss2 << this->offset << ' ';
	s = ss2.str();
	tam += s.size();
	s.clear();

	return tam;
}
CadenaBytes RegTitulo::Serializar(){
	CadenaBytes cadena;
	return cadena;
}
bool RegTitulo::Hidratar(CadenaBytes &cadena){
	return true;
}
//void RegTitulo::serializar(char* buffer, unsigned int& offset) {
//	Persistencia::PonerEnteroEnChar(buffer, offset, this->clave);
//	Persistencia::PonerEnteroEnChar(buffer, offset, this->offset);
//}
//
//void RegTitulo::hidratar(char* buffer, unsigned int& offset) {
//	this->clave = Persistencia::getEnteroDesdeBuffer(buffer, offset);
//	this->offset = Persistencia::getEnteroDesdeBuffer(buffer, offset);
//}

void RegTitulo::toString(ofstream& fo) {
	fo << " Registro de titulo --> " << endl;
	fo << " Clave:   " << this->clave << endl;
	fo << " Offset:   " << this->offset << endl;
}
