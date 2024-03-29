
#include "Bucket.h"

Bucket::Bucket(int tam_disp) : Bloque(tam_disp) {
	this->esp_libre = TAM_CUBO - this->get_tam();
}

int Bucket::get_tam() {
	Persistencia cadena_aux = this->Serializar();
	return cadena_aux.getTamanio();
}

bool Bucket::esta_vacio() const {
	if (this->regs.empty() == true)
		return true;
	return false;
}

bool Bucket::entra_en_bloque(RegTitulo& reg) const {
	Persistencia cadena;

	int tam = reg.get_tam();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(reg.Serializar());

	if (this->esp_libre > (int)cadena.getTamanio())
		return true;

	return false;
}

bool Bucket::entra_en_bloque(Elemento& elemento) const {
	Persistencia cadena;

	int tam = elemento.get_tam();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(elemento.Serializar());

	if (this->esp_libre > (int)cadena.getTamanio())
		return true;

	return false;
}

void Bucket::aumentar_esp_libre(Elemento& elemento) {
	Persistencia cadena;

	int tam = elemento.get_tam();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(elemento.Serializar());

	this->esp_libre += cadena.getTamanio();
}

void Bucket::disminuir_esp_libre(Elemento& elemento) {
	Persistencia cadena;

	int tam = elemento.get_tam();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(elemento.Serializar());

	this->esp_libre -= cadena.getTamanio();
}

void Bucket::agregar_nuevo_reg(RegTitulo& reg) {
	this->regs.push_back(reg);

	Persistencia cadena;

	int tam = reg.get_tam();
	cadena.agregarAlFinal(&tam, sizeof(tam));
	cadena.agregarAlFinal(reg.Serializar());

	this->esp_libre -= cadena.getTamanio();
}

bool Bucket::eliminar_reg(int clave) {
	list < RegTitulo > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if (it != this->regs.end() && (*it).get_clave() == clave) {
		Persistencia cadena;

		int tam = (*it).get_tam();
		cadena.agregarAlFinal(&tam, sizeof(tam));
		cadena.agregarAlFinal((*it).Serializar());

		this->esp_libre += cadena.getTamanio();

		this->regs.erase(it);

		return true;
	}

	return false;
}

bool Bucket::existe_reg(int clave) {
	list < RegTitulo > ::iterator it;

	it = this->regs.begin();
	while (it != this->regs.end() && (*it).get_clave() != clave)
		++ it;

	if (it != this->regs.end() && (*it).get_clave() == clave)
		return true;

	return false;
}

RegTitulo& Bucket::buscar_reg(int clave) {
	list < RegTitulo > ::iterator it;

	it = this->regs.begin();
	while ((*it).get_clave() != clave)
		++ it;

	return (*it);
}

void Bucket::vaciar() {
	this->tam_disp = 1;
	this->regs.clear();
	this->esp_libre = TAM_CUBO - this->get_tam();
}

void Bucket::incorporar_regs(list < RegTitulo > & regs) {
	list < RegTitulo > ::iterator it;
	for (it = regs.begin(); it != regs.end(); ++ it)
		this->agregar_nuevo_reg(*it);
}

list < RegTitulo > Bucket::actualizar_regs(int num_bloque, HandlerTabla& handler) {
	list < RegTitulo > ::iterator it;
	list < RegTitulo > list_aux;
	RegTitulo reg_desact;
	int tam;
	unsigned int tam_regs;
	unsigned int contador = 0;

	tam_regs = this->regs.size();
	it = this->regs.begin();

	while (contador != tam_regs) {
		if (num_bloque != handler.get_num_bloque((*it).get_clave())) {
			reg_desact = *it;

			Persistencia cadena;

			tam = reg_desact.get_tam();
			cadena.agregarAlFinal(&tam, sizeof(tam));
			cadena.agregarAlFinal(reg_desact.Serializar());

			this->esp_libre += cadena.getTamanio();

			it = this->regs.erase(it);

			list_aux.push_back(reg_desact);
		}
		else ++ it;
		++ contador;
	}

	return list_aux;
}

Persistencia Bucket::Serializar() {
	Persistencia cadena;

	cadena.agregarAlFinal(&this->tam_disp, sizeof(this->tam_disp));

	int tam = this->regs.size();
	cadena.agregarAlFinal(&tam, sizeof(tam));

	int tam2;
	list < RegTitulo > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it) {
		tam2 = (*it).get_tam();
		cadena.agregarAlFinal(&tam2, sizeof(tam2));
		cadena.agregarAlFinal((*it).Serializar());
	}

	return cadena;
}

bool Bucket::Hidratar(Persistencia& cadena) {
	this->vaciar();

	int offset = 0;

	this->tam_disp = cadena.leerEntero(offset);
	offset += sizeof(this->tam_disp);

	int tam1 = cadena.leerEntero(offset);
	offset += sizeof(tam1);

	int tam2;
	for (int i = 0; i < tam1; ++ i) {
		tam2 = cadena.leerEntero(offset);
		offset += sizeof(tam2);
		Persistencia cadena_aux;
		cadena_aux = cadena.leer(offset, tam2);
		RegTitulo reg;
		reg.Hidratar(cadena_aux);
		this->agregar_nuevo_reg(reg);
		offset += tam2;
	}

	return true;
}

void Bucket::toString(ostream& os) {
	os << "Bloque --> " << endl;
	os << "  Tamaño de dispersión:   " << this->tam_disp << endl;
	os << "  Cantidad de espacio libre:   " << this->esp_libre << endl;

	list < RegTitulo > ::iterator it;
	for (it = this->regs.begin(); it != this->regs.end(); ++ it)
		(*it).toString(os);
}
