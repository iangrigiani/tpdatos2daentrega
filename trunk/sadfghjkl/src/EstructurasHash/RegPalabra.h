
#ifndef REGPALABRA_H_
#define REGPALABRA_H_

#include <list>
#include "../Persistencia/Serializable.h"

class RegPalabra: public Serializable {

private:

	int clave;
	int bloque_sig;
	list < int > offsets;

public:

	RegPalabra();
	RegPalabra(int clave);
	virtual ~RegPalabra() {};

	void set_clave(int clave);
	void set_bloque_sig(int bloque_sig);
	void set_offsets(const list < int > & offsets);

	int get_clave() const { return this->clave; }
	int get_bloque_sig() const { return this->bloque_sig; }
	const list < int > & get_offsets() const { return this->offsets; }

	bool esta_vacio();
	int get_tam();

	void agregar_nuevo_offset(int offset);
	bool eliminar_offset(int offset);

	Persistencia Serializar();
	bool Hidratar(Persistencia& cadena);

	void toString(ostream& os);

};

#endif /* REGPALABRA_H_ */
