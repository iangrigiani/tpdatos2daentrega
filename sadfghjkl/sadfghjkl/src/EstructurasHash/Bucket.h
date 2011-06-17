
#ifndef BUCKET_H_
#define BUCKET_H_

class HandlerTabla;

#include "RegTitulo.h"
#include "../Hash/HandlerTabla.h"

class Bucket : public Bloque {

private:

	int esp_libre;
	list < RegTitulo > regs;

public:

	Bucket(int tam_disp = 1);
	virtual ~Bucket() {};

	int get_tam();
	bool esta_vacio() const;
	bool entra_en_bloque(RegTitulo& reg) const;
	bool entra_en_bloque(Elemento& elemento) const;

	list < RegTitulo > & get_regs() { return this->regs; }

	void aumentar_esp_libre(Elemento& elemento);
	void disminuir_esp_libre(Elemento& elemento);

	void agregar_nuevo_reg(RegTitulo& reg);
	bool eliminar_reg(int clave);

	bool existe_reg(int clave);
	RegTitulo& buscar_reg(int clave);

	void incorporar_regs(list < RegTitulo > & regs);
	list < RegTitulo > actualizar_regs(int num_bloque, HandlerTabla& handler);

	void vaciar();

	Persistencia Serializar();
	bool Hidratar(Persistencia& cadena);

	void toString(ostream& os);

};

#endif /* BUCKET_H_ */
