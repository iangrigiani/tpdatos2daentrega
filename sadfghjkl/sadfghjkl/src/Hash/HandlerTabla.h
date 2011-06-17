
#ifndef HANDLERTABLA_H_
#define HANDLERTABLA_H_

class Bloque;

#include <cstdio>
#include <fstream>
#include "../EstructurasHash/Bloque.h"
#include "../Comunes/Constantes.h"

class HandlerTabla {

private:

	int tam_tabla;
	string ruta_arch_tabla;

public:

	HandlerTabla();
	virtual ~HandlerTabla() {};

	void set_ruta_arch_tabla(const string& ruta_arch_tabla);

	const string& get_ruta_arch_tabla() const { return this->ruta_arch_tabla; }

	bool tabla_vacia();
	void crear_tabla_inicial();
	void insertar_primer_referencia(int num_bloque);

	void duplicar_tabla();
	void truncar_tabla();

	int get_tam_tabla() const { return this->tam_tabla; }

	bool mitades_iguales() const;

	int get_num_bloque(int clave) const;

	int get_pos_tabla(int clave) const;

	void reemplazar_referencia(int num_bloque_a_reemplazar, int num_nuevo_bloque);
	void reemplazar_referencias(int pos_inicial, int num_nuevo_bloque, const Bloque& nuevo_bloque);

	int puedo_liberar_bloque(const Bloque& bloque_a_liberar, int pos_actual) const;
	void liberar_referencias(int pos_inicial, int num_bloque_por_reemplazar,
			const Bloque& bloque_por_reemplazar);

};

#endif /* HANDLERTABLA_H_ */
