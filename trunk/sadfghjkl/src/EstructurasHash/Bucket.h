
#ifndef BUCKET_H_
#define BUCKET_H_

class HandlerTabla;

#include "RegIndice.h"
#include "../Hash/HandlerTabla.h"

class Bucket : public Bloque {

private:

	int esp_libre;
	list < RegIndice > regs;

public:

	Bucket(int tam_disp = 1);
	virtual ~Bucket() {};

	int get_tam();
	bool esta_vacio() const;
	bool entra_en_bloque(RegIndice& reg) const;
	bool entra_en_bloque(Elemento& elemento) const;

	list < RegIndice > & get_regs() { return this->regs; }

	void aumentar_esp_libre(Elemento& elemento);
	void disminuir_esp_libre(Elemento& elemento);

	void agregar_nuevo_reg(RegIndice& reg);
	bool eliminar_reg(int clave);

	bool existe_reg(int clave);
	RegIndice& buscar_reg(int clave);

	void incorporar_regs(list < RegIndice > & regs);
	list < RegIndice > actualizar_regs(int num_bloque, HandlerTabla& handler);

	void vaciar();

	CadenaBytes Serializar();
	bool Hidratar(CadenaBytes& cadena);

	void toString(ostream& os);

};

#endif /* BUCKET_H_ */
