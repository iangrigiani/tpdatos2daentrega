
#include "PersistorHash.h"

PersistorHash::PersistorHash(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre) :
		handler_bloques(TAM_CUBO, ruta_arch_bloques, handler_esp_libre) {}

void PersistorHash::set_handler_bloques(const string& ruta_arch_bloques, const HandlerEspLibre& handler_esp_libre) {
	this->handler_bloques.set_tam_bloque(TAM_CUBO);
	this->handler_bloques.set_ruta_arch_bloques(ruta_arch_bloques);
	this->handler_bloques.set_handler_esp_libre(handler_esp_libre);
}

int PersistorHash::guardar_bloque(const Persistencia& cadena) {
	return this->handler_bloques.guardar_bloque((char*)cadena.toString().c_str());
}

void PersistorHash::guardar_bloque(const Persistencia& cadena, int num_bloque) {
	this->handler_bloques.guardar_bloque((char*)cadena.toString().c_str(), num_bloque);
}

void PersistorHash::recuperar_bloque(int num_bloque, Persistencia& cadena) {
	char buffer[TAM_CUBO];
	this->handler_bloques.recuperar_bloque(num_bloque, buffer);
	cadena.agregar(buffer, TAM_CUBO, 0);
}
