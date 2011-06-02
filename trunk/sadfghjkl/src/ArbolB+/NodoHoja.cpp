
#include "NodoHoja.h"


NodoHoja::NodoHoja() : Nodo(0) {
	hojaSiguiente = 0;
	this->datos = new CadenaBytes[(TAM_EFECTIVO_NODO/(TAM_CONTROL_REGISTRO)) + 2];
	this->Ids = new CadenaBytes[(TAM_EFECTIVO_NODO/(TAM_CONTROL_REGISTRO)) + 2];
}

NodoHoja::~NodoHoja() {
	delete[] datos;
	delete[] Ids;
}

CadenaBytes NodoHoja::Serializar() {
	CadenaBytes cadena;

	cadena.agregarAlFinal(&nivel,sizeof(nivel));
	cadena.agregarAlFinal(&cantidadClaves, sizeof(cantidadClaves));
	for (int posicion = 0; posicion < cantidadClaves; ++posicion) {
		cadena.agregarAlFinal(claves[posicion].Serializar());
		int tamanioDato = datos[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioDato,sizeof(tamanioDato));
		cadena.agregarAlFinal(datos[posicion]);
		int tamanioID = Ids[posicion].getTamanio();
		cadena.agregarAlFinal(&tamanioID,sizeof(tamanioID));
		cadena.agregarAlFinal(Ids[posicion]);
	}
	cadena.agregarAlFinal(&hojaSiguiente, sizeof(hojaSiguiente));

	char vacio = CONST_VACIO;
	int espacioLibre = TAM_TOTAL_NODO - cadena.getTamanio();
	for (int i = 0; i < espacioLibre; i++) {
		cadena.agregarAlFinal(&vacio, sizeof(vacio));
	}
	return cadena;
}

bool NodoHoja::Hidratar(CadenaBytes & cadena) {
	bool exito = true;

	if ((int)cadena.getTamanio() != (TAM_TOTAL_NODO)) {
		exito = false;
	} else {
		int offset = 0;
		nivel = cadena.leerEntero(offset);
		offset += sizeof(nivel);
		cantidadClaves = cadena.leerEntero(offset);
		offset += sizeof(cantidadClaves);

		for (int posicion = 0; posicion < cantidadClaves; ++posicion) {

			char tamanioClave;
			cadena.leer(&tamanioClave,offset,TAM_LONG_CLAVE);
			CadenaBytes cadenaClave = cadena.leer(offset, TAM_LONG_CLAVE + tamanioClave);
			Clave unaClave;
			unaClave.Hidratar(cadenaClave);
			claves[posicion] = unaClave;
			offset += TAM_LONG_CLAVE + tamanioClave;

			int tamanioDato = cadena.leerEntero(offset);
			offset += TAM_LONG_DATO;
			CadenaBytes unDato;
			unDato.agregarAlFinal(cadena.leer(offset,tamanioDato));
			datos[posicion] = unDato;
			offset += tamanioDato;

			int tamanioID = cadena.leerEntero(offset);
			offset += TAM_LONG_DATO;
			CadenaBytes unID;
			unID.agregarAlFinal(cadena.leer(offset,tamanioID));
			Ids[posicion] = unID;
			offset += tamanioID;

			espacioOcupado += tamanioClave + tamanioDato + tamanioID + TAM_CONTROL_REGISTRO;
		}
		hojaSiguiente = cadena.leerEntero(offset);
	}
	return exito;
}

NodoHoja* NodoHoja::Clonar() {
	NodoHoja* nodoHoja = new NodoHoja();
	nodoHoja->nivel = this->nivel;
	nodoHoja->espacioOcupado = this->espacioOcupado;
	nodoHoja->cantidadClaves = this->cantidadClaves;
	nodoHoja->hojaSiguiente = this->hojaSiguiente;
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->claves[i] = this->claves[i];
	}
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->datos[i] = this->datos[i];
	}
	for (int i=0; i < this->cantidadClaves; ++i) {
		nodoHoja->Ids[i] = this->Ids[i];
	}
	return nodoHoja;
}
