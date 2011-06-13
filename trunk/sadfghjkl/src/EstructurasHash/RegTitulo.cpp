
#include "RegTitulo.h"

RegTitulo::RegTitulo() : clave(-1), bloque_sig(-1) {}

RegTitulo::RegTitulo(int clave) : clave(clave), bloque_sig(-1) {}

void RegTitulo::set_clave(int clave) {
	this->clave = clave;
}

void RegTitulo::set_bloque_sig(int bloque_sig) {
	this->bloque_sig = bloque_sig;
}

void RegTitulo::set_elementos(const list < Elemento > & elementos) {
	this->elementos = elementos;
}

bool RegTitulo::esta_vacio() {
	if (this->bloque_sig == -1 && this->elementos.empty() == true)
		return true;
	return false;
}

int RegTitulo::get_tam() {
	CadenaBytes cadena_aux = this->Serializar();
	return cadena_aux.getTamanio();
}

void RegTitulo::agregar_nuevo_elemento(const Elemento& elemento) {
	this->elementos.push_back(elemento);
}

bool RegTitulo::eliminar_elemento(const string& termino) {
	list < Elemento > ::iterator it;

	it = this->elementos.begin();
	while (it != this->elementos.end() && termino.compare((*it).get_termino()) != 0)
		++ it;

	if (it != this->elementos.end() && termino.compare((*it).get_termino()) == 0) {
		this->elementos.erase(it);
		return true;
	}

	return false;
}

bool RegTitulo::existe_elemento(const string& termino) {
	list < Elemento > ::iterator it;

	it = this->elementos.begin();
	while (it != this->elementos.end() && termino.compare((*it).get_termino()) != 0)
		++ it;

	if (it != this->elementos.end() && termino.compare((*it).get_termino()) == 0)
		return true;

	return false;
}

Elemento& RegTitulo::buscar_elemento(const string& termino) {
	list < Elemento > ::iterator it;

	it = this->elementos.begin();
	while (termino.compare((*it).get_termino()) != 0)
		++ it;

	return *it;
}

CadenaBytes RegTitulo::Serializar() {
	CadenaBytes cadena;

	cadena.agregarAlFinal(&this->clave, sizeof(this->clave));

	cadena.agregarAlFinal(&this->bloque_sig, sizeof(this->bloque_sig));

	int tam1 = this->elementos.size();
	cadena.agregarAlFinal(&tam1, sizeof(tam1));

	int tam2;
	list < Elemento > ::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++ it) {
		tam2 = (*it).get_tam();
		cadena.agregarAlFinal(&tam2, sizeof(tam2));
		cadena.agregarAlFinal((*it).Serializar());
	}

	return cadena;
}

bool RegTitulo::Hidratar(CadenaBytes& cadena) {
	this->elementos.clear();

	int offset = 0;

	this->clave = cadena.leerEntero(offset);
	offset += sizeof(this->clave);

	this->bloque_sig = cadena.leerEntero(offset);
	offset += sizeof(this->bloque_sig);

	int tam1 = cadena.leerEntero(offset);
	offset += sizeof(tam1);

	int tam2;
	for (int i = 0; i < tam1; ++ i) {
		tam2 = cadena.leerEntero(offset);
		offset += sizeof(tam2);
		CadenaBytes cadena_aux;
		cadena_aux = cadena.leer(offset, tam2);
		Elemento elemento;
		elemento.Hidratar(cadena_aux);
		this->elementos.push_back(elemento);
		offset += tam2;
	}

	return true;
}

void RegTitulo::toString(ostream& os) {
	os << "   Registro --> " << endl;
	os << "     Clave:   " << this->clave << endl;
	os << "     Bloque siguiente:   " << this->bloque_sig << endl;
	os << "     Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;

	list < Elemento > ::iterator it;
	for (it = this->elementos.begin(); it != this->elementos.end(); ++ it)
		(*it).toString(os);
}
