
#include "NodoInterior.h"


NodoInterior::NodoInterior(int nivel) : Nodo(nivel) {
	this->hijos = new int[(TAM_EFECTIVO_NODO/(TAM_CONTROL_REGISTRO)) + 2];
}

NodoInterior::NodoInterior() : Nodo(0) {
	this->hijos = new int[(TAM_EFECTIVO_NODO/(TAM_CONTROL_REGISTRO)) + 2];
}

NodoInterior::~NodoInterior() {
	delete[] hijos;
}

Persistencia NodoInterior::Serializar() {
	Persistencia cadena;

	cadena.agregarAlFinal(&nivel,sizeof(nivel));
	cadena.agregarAlFinal(&cantidadClaves, sizeof(cantidadClaves));

	int posicion;
	for (posicion = 0; posicion < cantidadClaves; ++posicion) {
		cadena.agregarAlFinal(claves[posicion].Serializar());
		cadena.agregarAlFinal(&hijos[posicion], sizeof(int));
	}
	cadena.agregarAlFinal(&hijos[posicion], sizeof(int));

	char vacio = CONST_VACIO;
	int espacioLibre = TAM_TOTAL_NODO - cadena.getTamanio();
	for (int i = 0; i < espacioLibre; i++) {
		cadena.agregarAlFinal(&vacio, sizeof(vacio));
	}
	return cadena;
}

bool NodoInterior::Hidratar(Persistencia & cadena) {
	bool exito = true;

	if ((int)cadena.getTamanio() != (TAM_TOTAL_NODO)) {
		exito = false;
	} else {
		int offset = 0;
		nivel = cadena.leerEntero(offset);
		offset += sizeof(nivel);
		cantidadClaves = cadena.leerEntero(offset);
		offset += sizeof(cantidadClaves);

		int posicion;
		for (posicion = 0; posicion < cantidadClaves; ++posicion) {

			char tamanioClave;
			cadena.leer(&tamanioClave,offset,TAM_LONG_CLAVE);
			Persistencia cadenaClave = cadena.leer(offset, TAM_LONG_CLAVE + tamanioClave);
			Clave unaClave;
			unaClave.Hidratar(cadenaClave);
			claves[posicion] = unaClave;
			offset += TAM_LONG_CLAVE + tamanioClave;

			hijos[posicion] = cadena.leerEntero(offset);
			offset += sizeof(int);
			espacioOcupado += tamanioClave + TAM_CONTROL_REGISTRO;
		}
		hijos[posicion] = cadena.leerEntero(offset);
	}
	return exito;
}
