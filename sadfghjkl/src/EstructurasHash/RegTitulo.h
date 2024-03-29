
#ifndef REGTITULO_H_
#define REGTITULO_H_

#include "Elemento.h"

class RegTitulo : public Serializable {

private:

	int clave;
	int bloque_sig;
	list < Elemento > elementos;

public:

	RegTitulo();
	RegTitulo(int clave);
	virtual ~RegTitulo() {};

	void set_clave(int clave);
	void set_bloque_sig(int bloque_sig);
	void set_elementos(const list < Elemento > & elementos);

	int get_clave() const { return this->clave; }
	int get_bloque_sig() const { return this->bloque_sig; }
	const list < Elemento > & get_elementos() const { return this->elementos; }

	bool esta_vacio();
	int get_tam();

	void agregar_nuevo_elemento(const Elemento& elemento);
	bool eliminar_elemento(const string& termino);

	bool existe_elemento(const string& termino);
	Elemento& buscar_elemento(const string& termino);

	Persistencia Serializar();
	bool Hidratar(Persistencia& cadena);

	void toString(ostream& os);

};

#endif /* REGTITULO_H_ */
