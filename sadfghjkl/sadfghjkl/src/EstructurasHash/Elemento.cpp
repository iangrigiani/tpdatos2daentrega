
#include "Elemento.h"

Elemento::Elemento() : ID(-1) {}

Elemento::Elemento(const string& termino, int ID) : termino(termino), ID(ID) {}

void Elemento::set_termino(const string& termino) {
	this->termino = termino;
}

void Elemento::set_ID(int ID) {
	this->ID = ID;
}

int Elemento::get_tam() {
	Persistencia cadena_aux = this->Serializar();
	return cadena_aux.getTamanio();
}

Persistencia Elemento::Serializar() {
	Persistencia cadena;

	char tam = this->termino.size();
	cadena.agregarAlFinal(&tam, sizeof(tam));

	cadena.agregarAlFinal(this->termino);

	cadena.agregarAlFinal(&this->ID, sizeof(this->ID));

	return cadena;
}

bool Elemento::Hidratar(Persistencia& cadena) {
	this->termino.clear();

	int offset = 0;

	char tam;
	cadena.leer(&tam, 0, sizeof(char));
	offset += sizeof(tam);

	int size = int(tam);
	char* buffer = (char*)malloc(size);
	cadena.leer(buffer, sizeof(char), size);
	this->termino.append(buffer, size);
	free(buffer);
	offset += size;

	this->ID = cadena.leerEntero(offset);
	offset += sizeof(this->ID);

	return true;
}

void Elemento::toString(ostream& os) {
	os << "      Elemento --> " << endl;
	os << "        Término:   " << this->termino << endl;
	os << "        ID:   " << this->ID << endl;
	os << "        Tamaño ocupado:   " << this->get_tam() << " Bytes" << endl;
}
