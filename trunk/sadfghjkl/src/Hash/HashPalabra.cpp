
#include "HashPalabra.h"

HashPalabra::HashPalabra(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
		const string& ruta_arch_tabla) {
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->persistor.set_handler_bloques(ruta_arch_bloques, handler_esp_libre);

	this->handler_tabla.set_ruta_arch_tabla(ruta_arch_tabla);

	this->crear_condiciones_iniciales();
}

void HashPalabra::crear_condiciones_iniciales() {
	HandlerBloques& handler_bloques = this->persistor.get_handler_bloques();
	handler_bloques.crear_arch_vacio();
	handler_bloques.get_handler_esp_libre().crear_arch_inicial();
	this->handler_tabla.crear_tabla_inicial();

	if (this->handler_tabla.tabla_vacia() == true) {
		Cubo bloque;

		int num_bloque = this->persistor.guardar_bloque(bloque.Serializar());
		this->handler_tabla.insertar_primer_referencia(num_bloque);
	}
}

void HashPalabra::insertar_reg(RegPalabra& reg) {
	Persistencia cadena;
	Cubo bloque;

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(reg.get_clave());
	int num_bloque = this->handler_tabla.get_num_bloque(reg.get_clave());
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (bloque.entra_en_bloque(reg) == true) {
		bloque.agregar_nuevo_reg(reg);
		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
	}
	else {
		int tam_disp_inicial = bloque.get_tam_disp();
		bloque.duplicar_tam_disp();
		Cubo nuevo_bloque(bloque.get_tam_disp());
		int num_nuevo_bloque = this->persistor.guardar_bloque(nuevo_bloque.Serializar());

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);

		list < RegPalabra > regs_desactualizados = bloque.actualizar_regs(num_bloque, this->handler_tabla);

		if (regs_desactualizados.empty() == false) {
			nuevo_bloque.incorporar_regs(regs_desactualizados);
			this->persistor.guardar_bloque(nuevo_bloque.Serializar(), num_nuevo_bloque);
		}

		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		this->insertar_reg(reg);
	}
}

void HashPalabra::agregar_nuevo_offset(Cubo& bloque, int num_bloque, RegPalabra& reg, int offset) {
	if (bloque.entra_en_bloque(offset) == true) {
		reg.agregar_nuevo_offset(offset);
		bloque.disminuir_esp_libre(offset);
		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
	}
	else {
		Cubo bloque_sig;

		if (reg.get_bloque_sig() == -1) {
			RegPalabra reg_aux(reg.get_clave());
			reg_aux.agregar_nuevo_offset(offset);
			bloque_sig.agregar_nuevo_reg(reg_aux);
			int num_bloque_sig = this->persistor.guardar_bloque(bloque_sig.Serializar());
			reg.set_bloque_sig(num_bloque_sig);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
		else {
			Persistencia cadena;
			this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
			bloque_sig.Hidratar(cadena);
			RegPalabra& reg_aux = bloque_sig.buscar_reg(reg.get_clave());
			this->agregar_nuevo_offset(bloque_sig, reg.get_bloque_sig(), reg_aux, offset);
		}
	}
}

void HashPalabra::alta(int clave, int offset) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (bloque.existe_reg(clave) == true)
		this->agregar_nuevo_offset(bloque, num_bloque, bloque.buscar_reg(clave), offset);
	else {
		RegPalabra reg(clave);
		reg.agregar_nuevo_offset(offset);
		this->insertar_reg(reg);
	}
}

bool HashPalabra::eliminar_reg(int clave) {
	Persistencia cadena;
	Cubo bloque;

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(clave);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (!bloque.eliminar_reg(clave))
		return false;

	if (bloque.esta_vacio() == true) {
		int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
		if (num_otro_bloque != -1) {
			Cubo otro_bloque;

			this->persistor.recuperar_bloque(num_otro_bloque, cadena);
			otro_bloque.Hidratar(cadena);
			this->handler_tabla.liberar_referencias(pos_tabla_bloque, num_otro_bloque, otro_bloque);
			otro_bloque.truncar_tam_disp();
			this->persistor.guardar_bloque(otro_bloque.Serializar(), num_otro_bloque);
			this->persistor.get_handler_bloques().eliminar_bloque(num_bloque);

			if (this->handler_tabla.mitades_iguales() == true)
				this->handler_tabla.truncar_tabla();
		}
		else {
			bloque.get_regs().clear();
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
	}
	else this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);

	return true;
}

void HashPalabra::obtener_reg(RegPalabra& reg, Cubo& bloque_sig, list < int > & bloques_sigs, int clave) {
	Persistencia cadena;

	this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
	bloque_sig.Hidratar(cadena);
	bloques_sigs.push_back(reg.get_bloque_sig());
	reg = bloque_sig.buscar_reg(clave);
}

void HashPalabra::eliminar_reg_y_bloques_sigs(Cubo& bloque, int num_bloque, int clave) {
	if (bloque.existe_reg(clave) == true) {
		RegPalabra& reg = bloque.buscar_reg(clave);

		if (reg.esta_vacio() == true)
			this->eliminar_reg(clave);
		else {
			if (reg.get_offsets().empty() == true && reg.get_bloque_sig() != -1) {
				Cubo bloque_sig;
				list < int > bloques_sigs;

				this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				while (reg.get_offsets().empty() == true && reg.get_bloque_sig() != -1)
					this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				if (reg.get_offsets().empty() == true && reg.get_bloque_sig() == -1) {
					list < int > ::iterator it;

					for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
						this->persistor.get_handler_bloques().eliminar_bloque(*it);

					this->eliminar_reg(clave);
				}
			}
		}
	}
}

void HashPalabra::eliminar_offset(Cubo& bloque, int num_bloque, int clave, int offset) {
	if (bloque.existe_reg(clave) == true) {
		RegPalabra& reg = bloque.buscar_reg(clave);

		if (reg.eliminar_offset(offset) == false) {
			if (reg.get_bloque_sig() == -1)
				return;
			else {
				Persistencia cadena;
				Cubo bloque_sig;

				this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
				bloque_sig.Hidratar(cadena);
				this->eliminar_offset(bloque_sig, reg.get_bloque_sig(), clave, offset);
			}
		}
		else {
			bloque.aumentar_esp_libre(offset);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
	}
}

void HashPalabra::baja(int clave, int offset) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	this->eliminar_offset(bloque, num_bloque, clave, offset);
	this->eliminar_reg_y_bloques_sigs(bloque, num_bloque, clave);
}

void HashPalabra::concatenar_offsets(list < int > & lista_1, list < int > & lista_2) {
	list < int > ::iterator it;
	for (it = lista_2.begin(); it != lista_2.end(); ++ it)
		lista_1.push_back(*it);
}

list < int > HashPalabra::consultar_offsets(Cubo& bloque, int num_bloque, int clave) {
	Persistencia cadena;
	list < int > lista_1;

	if (bloque.existe_reg(clave) == true) {
		bool fin_lista = false;

		while (fin_lista == false) {
			RegPalabra& reg = bloque.buscar_reg(clave);
			list < int > lista_2 = reg.get_offsets();
			this->concatenar_offsets(lista_1, lista_2);
			if (reg.get_bloque_sig() != -1) {
				this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
				bloque.Hidratar(cadena);
			}
			else fin_lista = true;
		}
	}

	return lista_1;
}

list < int > HashPalabra::consultar(int clave) {
	Persistencia cadena;
	Cubo bloque;

	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);
	return this->consultar_offsets(bloque, num_bloque, clave);
}

void HashPalabra::mostrar(ostream& os) {
	Persistencia cadena;
	Cubo bloque;
	int cant_bloques = this->persistor.get_handler_bloques().get_tam_arch_bloques() / TAM_CUBO;

	os << "********************************************************************************" << endl;
	os << "		                          Hash de Palabras                                 " << endl;
	os << "********************************************************************************" << endl;
	os << endl;

	for (int i = 0; i < cant_bloques; ++ i) {
		os << "N° " << i << ":" << endl;
		this->persistor.recuperar_bloque(i, cadena);
		bloque.Hidratar(cadena);
		bloque.toString(os);
		os << endl;
	}
}

void HashPalabra::mostrar(const string& nombre_arch) {
	ofstream arch;

	arch.open(nombre_arch.c_str(), fstream::out);
	this->mostrar(arch);
	arch.close();
}

void HashPalabra::mostrar() {
	this->mostrar(cout);
}
