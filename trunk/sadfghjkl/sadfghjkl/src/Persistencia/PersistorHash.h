
#ifndef PERSISTORHASH_H_
#define PERSISTORHASH_H_

#include "Persistencia.h"
#include "../Handlers/HandlerBloques.h"

class PersistorHash {

private:

	HandlerBloques handler_bloques;

public:

	PersistorHash() {};
	PersistorHash(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre);
	virtual ~PersistorHash() {};

	void set_handler_bloques(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre);

	HandlerBloques& get_handler_bloques() { return this->handler_bloques; }

	int guardar_bloque(const Persistencia& cadena);

	void guardar_bloque(const Persistencia& cadena, int num_bloque);

	void recuperar_bloque(int num_bloque, Persistencia& cadena);

};

#endif /* PERSISTORHASH_H_ */
