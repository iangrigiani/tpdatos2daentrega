
#include "HashTitulo.h"

HashTitulo::HashTitulo(const string& ruta_arch_bloques, const string& ruta_arch_esp_libre,
		const string& ruta_arch_tabla) {
	HandlerEspLibre handler_esp_libre(ruta_arch_esp_libre);
	this->persistor.set_handler_bloques(ruta_arch_bloques, handler_esp_libre);

	this->handler_tabla.set_ruta_arch_tabla(ruta_arch_tabla);

	this->crear_condiciones_iniciales();
}

int HashTitulo::funcion_hash(const string& termino) {
	int clave = 0;

	for (unsigned int i = 0; i < termino.size(); ++ i) {
		if (termino[i] != 'z')
			clave += ((int)termino[i]) * (termino.size() - i);
	}

	return clave;
}

void HashTitulo::crear_condiciones_iniciales() {
	HandlerBloques& handler_bloques = this->persistor.get_handler_bloques();
	handler_bloques.crear_arch_vacio();
	handler_bloques.get_handler_esp_libre().crear_arch_inicial();
	this->handler_tabla.crear_tabla_inicial();

	if (this->handler_tabla.tabla_vacia() == true) {
		Bucket bloque;

		int num_bloque = this->persistor.guardar_bloque(bloque.Serializar());
		this->handler_tabla.insertar_primer_referencia(num_bloque);
	}
}

void HashTitulo::insertar_reg(RegTitulo& reg) {
	CadenaBytes cadena;
	Bucket bloque;

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
		Bucket nuevo_bloque(bloque.get_tam_disp());
		int num_nuevo_bloque = this->persistor.guardar_bloque(nuevo_bloque.Serializar());

		if (tam_disp_inicial == this->handler_tabla.get_tam_tabla()) {
			this->handler_tabla.duplicar_tabla();
			this->handler_tabla.reemplazar_referencia(num_bloque, num_nuevo_bloque);
		}
		else this->handler_tabla.reemplazar_referencias(pos_tabla_bloque, num_nuevo_bloque, nuevo_bloque);

		list < RegTitulo > regs_desactualizados = bloque.actualizar_regs(num_bloque, this->handler_tabla);

		if (regs_desactualizados.empty() == false) {
			nuevo_bloque.incorporar_regs(regs_desactualizados);
			this->persistor.guardar_bloque(nuevo_bloque.Serializar(), num_nuevo_bloque);
		}

		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		this->insertar_reg(reg);
	}
}

bool HashTitulo::elemento_repetido(RegTitulo& reg, const string& termino) {
	if (reg.existe_elemento(termino) == true)
		return true;
	else {
		if (reg.get_bloque_sig() == -1)
			return false;
		else {
			CadenaBytes cadena;
			Bucket bloque_sig;

			this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
			bloque_sig.Hidratar(cadena);
			RegTitulo& reg_aux = bloque_sig.buscar_reg(reg.get_clave());
			return this->elemento_repetido(reg_aux, termino);
		}
	}
}

void HashTitulo::agregar_nuevo_elemento(Bucket& bloque, int num_bloque, RegTitulo& reg, Elemento& elemento) {
	if (bloque.entra_en_bloque(elemento) == true) {
		reg.agregar_nuevo_elemento(elemento);
		bloque.disminuir_esp_libre(elemento);
		this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
	}
	else {
		Bucket bloque_sig;

		if (reg.get_bloque_sig() == -1) {
			RegTitulo reg_aux(reg.get_clave());
			reg_aux.agregar_nuevo_elemento(elemento);
			bloque_sig.agregar_nuevo_reg(reg_aux);
			int num_bloque_sig = this->persistor.guardar_bloque(bloque_sig.Serializar());
			reg.set_bloque_sig(num_bloque_sig);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
			//cout << "el bloque " << num_bloque << " tiene un reg con clave " << reg.get_clave() << " q apunta al bloque " << num_bloque_sig << endl;
		}
		else {
			CadenaBytes cadena;
			this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
			bloque_sig.Hidratar(cadena);
			RegTitulo& reg_aux = bloque_sig.buscar_reg(reg.get_clave());
			this->agregar_nuevo_elemento(bloque_sig, reg.get_bloque_sig(), reg_aux, elemento);
		}
	}
}

int HashTitulo::alta(const string& termino, int ID) {
	CadenaBytes cadena;
	Bucket bloque;

	int clave = this->funcion_hash(termino);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (bloque.existe_reg(clave) == true) {
		RegTitulo& reg = bloque.buscar_reg(clave);

		if (this->elemento_repetido(reg, termino) == false) {
			Elemento elemento(termino, ID);
			this->agregar_nuevo_elemento(bloque, num_bloque, reg, elemento);
		}
	}
	else {
		Elemento elemento(termino, ID);
		RegTitulo reg(clave);
		reg.agregar_nuevo_elemento(elemento);
		this->insertar_reg(reg);
	}

	return ID;
}

bool HashTitulo::eliminar_reg(int clave) {
	CadenaBytes cadena;
	Bucket bloque;

	int pos_tabla_bloque = this->handler_tabla.get_pos_tabla(clave);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	if (!bloque.eliminar_reg(clave))
		return false;

	if (bloque.esta_vacio() == true) {
		int num_otro_bloque = this->handler_tabla.puedo_liberar_bloque(bloque, pos_tabla_bloque);
		if (num_otro_bloque != -1) {
			Bucket otro_bloque;

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

void HashTitulo::obtener_reg(RegTitulo& reg, Bucket& bloque_sig, list < int > & bloques_sigs, int clave) {
	CadenaBytes cadena;

	this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
	bloque_sig.Hidratar(cadena);
	bloques_sigs.push_back(reg.get_bloque_sig());
	reg = bloque_sig.buscar_reg(clave);
}

void HashTitulo::eliminar_reg_y_bloques_sigs(Bucket& bloque, int num_bloque, int clave) {
	if (bloque.existe_reg(clave) == true) {
		RegTitulo& reg = bloque.buscar_reg(clave);

		if (reg.esta_vacio() == true)
			this->eliminar_reg(clave);
		else {
			if (reg.get_elementos().empty() == true && reg.get_bloque_sig() != -1) {
				Bucket bloque_sig;
				list < int > bloques_sigs;

				this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				while (reg.get_elementos().empty() == true && reg.get_bloque_sig() != -1)
					this->obtener_reg(reg, bloque_sig, bloques_sigs, clave);

				if (reg.get_elementos().empty() == true && reg.get_bloque_sig() == -1) {
					list < int > ::iterator it;

					for (it = bloques_sigs.begin(); it != bloques_sigs.end(); ++ it)
						this->persistor.get_handler_bloques().eliminar_bloque(*it);

					this->eliminar_reg(clave);
				}
			}
		}
	}
}

void HashTitulo::eliminar_elemento(Bucket& bloque, int num_bloque, int clave, const string& termino) {
	if (bloque.existe_reg(clave) == true) {
		RegTitulo& reg = bloque.buscar_reg(clave);

		if (reg.existe_elemento(termino) == false) {
			if (reg.get_bloque_sig() == -1)
				return;
			else {
				CadenaBytes cadena;
				Bucket bloque_sig;

				this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
				bloque_sig.Hidratar(cadena);
				this->eliminar_elemento(bloque_sig, reg.get_bloque_sig(), clave, termino);
			}
		}
		else {
			Elemento elemento = reg.buscar_elemento(termino);
			reg.eliminar_elemento(termino);
			bloque.aumentar_esp_libre(elemento);
			this->persistor.guardar_bloque(bloque.Serializar(), num_bloque);
		}
	}
}

void HashTitulo::baja(const string& termino) {
	CadenaBytes cadena;
	Bucket bloque;

	int clave = this->funcion_hash(termino);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);

	this->eliminar_elemento(bloque, num_bloque, clave, termino);
	this->eliminar_reg_y_bloques_sigs(bloque, num_bloque, clave);
}

int HashTitulo::consultar_elemento(Bucket& bloque, int num_bloque, int clave, const string& termino) {
	if (bloque.existe_reg(clave) == true) {
		RegTitulo& reg = bloque.buscar_reg(clave);

		if (reg.existe_elemento(termino) == false) {
			if (reg.get_bloque_sig() == -1)
				return -1;
			else {
				CadenaBytes cadena;
				Bucket bloque_sig;

				this->persistor.recuperar_bloque(reg.get_bloque_sig(), cadena);
				bloque_sig.Hidratar(cadena);
				return this->consultar_elemento(bloque_sig, reg.get_bloque_sig(), clave, termino);
			}
		}
		else {
			Elemento& elemento = reg.buscar_elemento(termino);
			return elemento.get_ID();
		}
	}
	else return -1;
}

int HashTitulo::consultar(const string& termino) {
	CadenaBytes cadena;
	Bucket bloque;

	int clave = this->funcion_hash(termino);
	int num_bloque = this->handler_tabla.get_num_bloque(clave);
	this->persistor.recuperar_bloque(num_bloque, cadena);
	bloque.Hidratar(cadena);
	return this->consultar_elemento(bloque, num_bloque, clave, termino);
}

void HashTitulo::mostrar(ostream& os) {
	CadenaBytes cadena;
	Bucket bloque;
	int cant_bloques = this->persistor.get_handler_bloques().get_tam_arch_bloques() / TAM_CUBO;

	os << "********************************************************************************" << endl;
	os << "		             Dispersión Extensible de Títulos                            " << endl;
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

void HashTitulo::mostrar(const string& nombre_arch) {
	ofstream arch;

	arch.open(nombre_arch.c_str(), fstream::out);
	this->mostrar(arch);
	arch.close();
}

void HashTitulo::mostrar() {
	this->mostrar(cout);
}
