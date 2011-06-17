
#ifndef HASHPALABRA_H_
#define HASHPALABRA_H_

#include "../Persistencia/PersistorHash.h"
#include "../EstructurasHash/Cubo.h"

class HashPalabra {

private :

	HandlerTabla handler_tabla;
	PersistorHash persistor;


	void agregar_nuevo_offset(Cubo& bloque, int num_bloque, RegPalabra& reg, int offset);

	void insertar_reg(RegPalabra& reg);


	void obtener_reg(RegPalabra& reg, Cubo& bloque_sig ,list < int > & bloques_sigs, int clave);

	void eliminar_reg_y_bloques_sigs(Cubo& bloque, int num_bloque, int clave);

	void eliminar_offset(Cubo& bloque, int num_bloque, int clave, int offset);

	bool eliminar_reg(int clave);


	void concatenar_offsets(list < int > & lista_1, list < int > & lista_2);

	list < int > consultar_offsets(Cubo& bloque, int num_bloque, int clave);


	void mostrar(ostream& os);


	void crear_condiciones_iniciales();

public:

	HashPalabra(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
			const string& ruta_arch_tabla);

	virtual ~HashPalabra() {};

	void alta(int clave, int offset);

	void baja(int clave, int offset);

	list < int > consultar(int clave);

	void mostrar(const string& nombre_arch);

	void mostrar();

};

#endif /* HASHPALABRA_H_ */
