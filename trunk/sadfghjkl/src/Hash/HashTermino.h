
#ifndef HASHTERMINO_H_
#define HASHTERMINO_H_

#include "../Persistencia/PersistorHash.h"
#include "../EstructurasHash/Bucket.h"

class HashTermino {

private :

	HandlerTabla handler_tabla;
	PersistorHash persistor;

	int funcion_hash(const string& termino);


	bool elemento_repetido(RegIndice& reg, const string& termino);

	void agregar_nuevo_elemento(Bucket& bloque, int num_bloque, RegIndice& reg, Elemento& elemento);

	void insertar_reg(RegIndice& reg);


	void obtener_reg(RegIndice& reg, Bucket& bloque_sig, list < int > & bloques_sigs, int clave);

	void eliminar_reg_y_bloques_sigs(Bucket& bloque, int num_bloque, int clave);

	void eliminar_elemento(Bucket& bloque, int num_bloque, int clave, const string& termino);

	bool eliminar_reg(int clave);


	int consultar_elemento(Bucket& bloque, int num_bloque, int clave, const string& termino);


	void mostrar(ostream& os);


	void crear_condiciones_iniciales();

public:

	HashTermino(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
			const string& ruta_arch_tabla);

	virtual ~HashTermino() {};

	int alta(const string& termino, int ID);

	void baja(const string& termino);

	int consultar(const string& termino);

	void mostrar(const string& nombre_arch);

	void mostrar();

};

#endif /* HASHTERMINO_H_ */
