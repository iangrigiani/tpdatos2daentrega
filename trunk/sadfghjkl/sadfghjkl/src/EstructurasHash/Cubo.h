
#ifndef CUBO_H_
#define CUBO_H_

class HandlerTabla;

#include "RegPalabra.h"
#include "../Hash/HandlerTabla.h"

class Cubo : public Bloque {

private:

	int esp_libre;
	list < RegPalabra > regs;

public:

	Cubo(int tam_disp = 1);
	virtual ~Cubo() {};

	int get_tam();
	bool esta_vacio() const;
	bool entra_en_bloque(RegPalabra& reg) const;
	bool entra_en_bloque(int offset) const;

	list < RegPalabra > & get_regs() { return this->regs; }

	void aumentar_esp_libre(int offset);
	void disminuir_esp_libre(int offset);

	void agregar_nuevo_reg(RegPalabra& reg);
	bool eliminar_reg(int clave);

	bool existe_reg(int clave);
	RegPalabra& buscar_reg(int clave);

	void incorporar_regs(list < RegPalabra > & regs);
	list < RegPalabra > actualizar_regs(int num_bloque, HandlerTabla& handler);

	void vaciar();

	Persistencia Serializar();
	bool Hidratar(Persistencia& cadena);

	void toString(ostream& os);

};

#endif /* CUBO_H_ */
