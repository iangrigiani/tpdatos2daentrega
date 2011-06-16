
#include "ArbolBMas.h"
#include <iostream>


/***************** Metodos Publicos **********************/


ArbolBMas::ArbolBMas(string ruta_archivo, string ruta_id, int tipoDeArbol) {
	this->primeraHoja = 0;
	this->tipoDeArbol = tipoDeArbol;
	this->pathId = ruta_id;
	this->persistor = new PersistorArbol(ruta_archivo, TAM_TOTAL_NODO);
	this->raiz = hidratarNodo(0);
	if (this->raiz) {
		this->cantidadNodos = persistor->getTamanioArchivo() / TAM_TOTAL_NODO;
	} else {
		this->cantidadNodos = 0;
	}
	hidratarDatosConfiguracion();
}


ArbolBMas::~ArbolBMas() {
	if (raiz) {
		liberarMemoriaNodo(raiz);
	}
	delete this->persistor;
}


int ArbolBMas::insertar(Elementos* registro, bool incrementarID) {

	Nodo* nuevoNodoHijo = NULL;
	Clave clavePromocion;
	int idDevolucion = 0;

	if (raiz == NULL) {
		raiz = crearNodoHoja();
		raiz->numero = primeraHoja = 0;
		persistirDatosConfiguracion();
		(static_cast <NodoHoja*> (raiz))->hojaSiguiente = 0;
		this->cantidadNodos = 1;
	}
	string palabra = registro->getDatos()->toString();

	// Saco el frontcoding antes de insertar recursivamente
	registro->getDatos()->sacarElFrontCoding(palabra, persistor->getRuta());

	Persistencia idInsertado;
	insertarRecursivo(raiz, *(registro->getClave()), *(registro->getDatos()), *(registro->getID()), &clavePromocion, &nuevoNodoHijo, &idInsertado, incrementarID);

	// Si el arbol es primario, devuelvo lo que inserte, sino devuelvo lo mismo que traia
	if (this->tipoDeArbol == 1){
		idDevolucion = atoi( (idInsertado.toString()).c_str() );
	} else {
		idDevolucion = atoi( (registro->getID()->toString()).c_str());
	}

	if (nuevoNodoHijo) {
		persistirNodo(nuevoNodoHijo);
		NodoInterior *nuevaRaiz = crearNodoInterior(raiz->nivel + 1);

		// Muevo la raiz a otra posicion y persisto la nueva raiz en la posicion cero
		raiz->numero = obtenerNumeroDeNodo();
		if (raiz->isNodoHoja()) {
			primeraHoja = raiz->numero;
			persistirDatosConfiguracion();
		}
		persistirNodo(raiz);

		nuevaRaiz->claves[0] = clavePromocion;
		nuevaRaiz->hijos[0] = raiz->numero;
		nuevaRaiz->hijos[1] = nuevoNodoHijo->numero;
		nuevaRaiz->cantidadClaves = 1;
		nuevaRaiz->espacioOcupado += clavePromocion.getTamanio() + TAM_CONTROL_REGISTRO;
		nuevaRaiz->numero = 0;
		persistirNodo(nuevaRaiz);

		liberarMemoriaNodo(raiz);
		liberarMemoriaNodo(nuevoNodoHijo);
		raiz = nuevaRaiz;
	} else {
		persistirNodo(raiz);
	}
	return idDevolucion;
}

void ArbolBMas::refactorizarNodoFrontCoding(NodoHoja** nodo){
	// Resto el tamaño del 1er dato
    (*nodo)->espacioOcupado -= ((*nodo))->datos[0].getTamanio();
    // Le saco el frontcoding a esa clave
    (*nodo)->datos[0].sacarElFrontCoding(((*nodo))->datos[0].toString(), persistor->getRuta());
    // Le sumo al nodo el tamaño del dato con la clave nueva
    (*nodo)->espacioOcupado += (*nodo)->datos[0].getTamanio();
	string primera = (*nodo)->datos[0].toString();

	// Hago lo mismo con el resto de las claves, pasandolas a frontcoding con respecto a la primera
	for (int i = 1; i < (*nodo)->cantidadClaves ; i++){
		(*nodo)->espacioOcupado -= ((*nodo))->datos[i].getTamanio();
		(*nodo)->datos[i].transformarAFrontCoding(primera, persistor->getRuta());
		(*nodo)->espacioOcupado += ((*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::refactorizarNodoNoHojaFrontCoding(Nodo** nodo){
	// Resto el tamaño del 1er dato
	static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[0].getTamanio();
	// Le saco el frontcoding a esa clave
	static_cast<NodoHoja*>(*nodo)->datos[0].sacarElFrontCoding((static_cast<NodoHoja*>(*nodo))->datos[0].toString(),  persistor->getRuta());
	// Le sumo al nodo el tamaño del dato con la clave nueva
	static_cast<NodoHoja*>(*nodo)->espacioOcupado += static_cast<NodoHoja*>(*nodo)->datos[0].getTamanio();
	string primera = static_cast<NodoHoja*>(*nodo)->datos[0].toString();

	// Hago lo mismo con el resto de las claves, pasandolas a frontcoding con respecto a la primera
	for (int i = 1; i < static_cast<NodoHoja*>(*nodo)->cantidadClaves ; i++){
		static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
		static_cast<NodoHoja*>(*nodo)->datos[i].transformarAFrontCoding(primera,  persistor->getRuta());
		static_cast<NodoHoja*>(*nodo)->espacioOcupado += (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
	}
}
void ArbolBMas::sacarFrontCodingNodo (Nodo ** nodo){
	// Resto el tamaño original en el nodo
	static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[0].getTamanio();
	// Le saco el frontcoding
	static_cast<NodoHoja*>(*nodo)->datos[0].sacarElFrontCoding((static_cast<NodoHoja*>(*nodo))->datos[0].toString(),  persistor->getRuta());
	// Sumo el nuevo tamaño sin el frontcoding en el nodo
	static_cast<NodoHoja*>(*nodo)->espacioOcupado += static_cast<NodoHoja*>(*nodo)->datos[0].getTamanio();

	// Hago lo mismo con el resto de las claves
	for (int i = 1; i < static_cast<NodoHoja*>(*nodo)->cantidadClaves ; i++){
		static_cast<NodoHoja*>(*nodo)->espacioOcupado -= (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
		static_cast<NodoHoja*>(*nodo)->datos[i].sacarElFrontCoding(static_cast<NodoHoja*>(*nodo)->datos[i].toString(),  persistor->getRuta());
		static_cast<NodoHoja*>(*nodo)->espacioOcupado += (static_cast<NodoHoja*>(*nodo))->datos[i].getTamanio();
	}
}

void ArbolBMas::sacarFrontCodingNodoHoja (NodoHoja ** nodo){
	// Resto el tamaño original en el nodo
    (*nodo)->espacioOcupado -= ((*nodo))->datos[0].getTamanio();
    // Le saco el frontcoding
    (*nodo)->datos[0].sacarElFrontCoding(((*nodo))->datos[0].toString(), persistor->getRuta());
    // Sumo el nuevo tamaño sin el frontcoding en el nodo
    (*nodo)->espacioOcupado += (*nodo)->datos[0].getTamanio();

    // Hago lo mismo con el resto de las claves
	for (int i = 1; i < (*nodo)->cantidadClaves ; i++){
		(*nodo)->espacioOcupado -= ((*nodo))->datos[i].getTamanio();
		(*nodo)->datos[i].sacarElFrontCoding((*nodo)->datos[i].toString(),  persistor->getRuta());
		(*nodo)->espacioOcupado += ((*nodo))->datos[i].getTamanio();
	}
}
//IteradorArbolBMas* ArbolBMas::begin() {
//	IteradorArbolBMas* iterador = NULL;
//	NodoHoja* nodoHoja = static_cast <NodoHoja*> (hidratarNodo(primeraHoja));
//	if (nodoHoja) {
//		iterador = new IteradorArbolBMas(nodoHoja->Clonar(), 0, persistor);
//		liberarMemoriaNodo(nodoHoja);
//	}
//	return iterador;
//}
//
//
//pair<Elementos*, IteradorArbolBMas*> ArbolBMas::buscar(Clave clave) {
//	Nodo *unNodo = raiz;
//	if (!unNodo)
//		return pair<Elementos*, IteradorArbolBMas*> (NULL, NULL);
//
//	while (!unNodo->isNodoHoja()) {
//		NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
//		int posicion = obtenerPosicion(unNodoInterior, clave);
//		unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
//		if (unNodoInterior != raiz)
//			liberarMemoriaNodo(unNodoInterior);
//	}
//	NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
//	Elementos* registro = NULL;
//	IteradorArbolBMas* iterador = NULL;
//	int posicion = obtenerPosicion(unNodoHoja, clave);
//	if (posicion < unNodoHoja->cantidadClaves && claveIgual(clave, unNodoHoja->claves[posicion])) {
//		registro = new Elementos(unNodoHoja->claves[posicion].Clonar(), new CadenaBytes(unNodoHoja->datos[posicion]));
//		iterador = new IteradorArbolBMas(unNodoHoja->Clonar(), posicion, persistor);
//	}
//	if (unNodoHoja != raiz)
//		liberarMemoriaNodo(unNodoHoja);
//	return pair<Elementos*, IteradorArbolBMas*> (registro, iterador);
//}


void ArbolBMas::mostrar(){
	ofstream fo;
	string ruta = this->persistor->getRuta() + "_Salida.txt";
	fo.open(ruta.c_str(), ios_base::out);
	fo << "********************************************************************************" << endl << endl;
	fo << "		                   Arbol B+ de "; fo << this->persistor->getRuta() << "                    " << endl << endl;
	fo << "********************************************************************************" << endl << endl;
	if (raiz){
		fo << "Tamanio de Nodo:  " << TAM_TOTAL_NODO << endl;
		fo << "	Primer Hoja:  " << primeraHoja << endl;
		fo << "--------------------------------------------------------------------------------" << endl << endl;
	}
	if (this->raiz){
		toString(this->raiz,1, fo);
	}
	fo.flush();
	fo.close();
}

void ArbolBMas::toString(Nodo* nodoAmostrar, int tab, ofstream& fo){

	if(nodoAmostrar){
		if (nodoAmostrar->isNodoHoja()) {
			NodoHoja *nodo = static_cast<NodoHoja*> (nodoAmostrar);
			for(int i=0 ; i<tab ; i++) fo << "  ";
				fo   << "Numero: " << nodo->numero <<  "  Nivel: " << nodo->nivel << "  Cant.Elem: " << nodo->cantidadClaves
				<< " Esp.Libre: " << TAM_EFECTIVO_NODO - nodo->espacioOcupado << "  Hoja.Sig: " << nodo->hojaSiguiente << "    " << endl;

			for(int i=0 ; i<tab ; i++) fo << "  ";
			for (int posicion = 0; posicion < nodo->cantidadClaves; ++posicion){
				fo << "(";
				Clave clave = nodo->claves[posicion].toString();
				fo << "ID: " << clave.getClave();
				fo << " , ";
				fo << "Elemento: " << "(" << nodo->datos[posicion].toString() << ";" << nodo->Ids[posicion].toString() << ")";
				fo << ")";
			}
			fo << endl;
		} else {
			NodoInterior *nodoInt= static_cast<NodoInterior*> (nodoAmostrar);
			fo << endl;
			for(int i=0; i<tab ; i++)
				fo << "  ";
			fo << "Numero: " << nodoInt->numero << "  Nivel: " << nodoInt->nivel << "  Cant.Elem: " << nodoInt->cantidadClaves
					<< "  Esp.Libre: " << TAM_EFECTIVO_NODO - nodoInt->espacioOcupado << "  Claves: (";
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {
				if (posicion < nodoInt->cantidadClaves) {
					Clave clave = nodoInt->claves[posicion];
					fo << clave.getClave();
					if (posicion == nodoInt->cantidadClaves-1){
						fo << ")" << endl;
					}else{
						fo << "," ;
					}
				}
			}
			int * hijos;
			Nodo *hijo;
			for (int posicion = 0; posicion <= nodoInt->cantidadClaves; ++posicion) {

				hijos = nodoInt->getHijos();
				hijo = hidratarNodo(hijos[posicion]);
				toString(hijo, tab+2, fo);
				if (hijo)
					liberarMemoriaNodo(hijo);
			}
			fo << endl;
		}
	}
}
int ArbolBMas::getCantidadBloques(){
	int tamanio = this->persistor->getTamanioArchivo();

	return (tamanio / TAM_TOTAL_NODO);
}


Nodo* ArbolBMas::leerNodo(int numeroDeNodo) {
	return hidratarNodo(numeroDeNodo);
}


/***************** Metodos Privados **********************/


bool ArbolBMas::claveMenor(Clave clave1, Clave clave2) {
	if (clave1.getClave() < clave2.getClave()) return true;
	return false;
}


bool ArbolBMas::claveMenorIgual(Clave clave1, Clave clave2) {
	if (clave1.getClave() <= clave2.getClave()) return true;
	return false;
}


bool ArbolBMas::claveIgual(Clave clave1, Clave clave2) {
	if (clave1.getClave() == clave2.getClave()) return true;
	return false;
}


NodoHoja* ArbolBMas::crearNodoHoja() {
	NodoHoja* unNodoHoja = new NodoHoja();
	return unNodoHoja;
}


NodoInterior* ArbolBMas::crearNodoInterior(int nivel) {
	NodoInterior* unNodoInterior = new NodoInterior(nivel);
	return unNodoInterior;
}


void ArbolBMas::liberarMemoriaNodo(Nodo *unNodo) {
	if (unNodo->isNodoHoja()) {
		delete static_cast<NodoHoja*> (unNodo);
	} else {
		delete static_cast<NodoInterior*> (unNodo);
	}
	unNodo = NULL;
}


int ArbolBMas::obtenerPosicion(Nodo *unNodo, Clave clave) {

	if (unNodo->cantidadClaves == 0)
		return 0;

	int inferior = 0;
	int superior = (unNodo->cantidadClaves)-1;

	while (inferior < superior) {
		int medio = (inferior + superior) / 2;

		if (claveMenorIgual(clave, unNodo->claves[medio])) {
			superior = medio - 1;
		} else {
			inferior = medio + 1;
		}
	}

	if (superior < 0 || claveMenor(unNodo->claves[superior], clave))
		superior++;

	return superior;
}


bool ArbolBMas::insertarRecursivo(Nodo* nodoCorriente, Clave clave, Persistencia dato, Persistencia id, Clave* clavePromocion, Nodo** nuevoNodo, Persistencia* idInsertado, bool incrementarID) {

	if (!nodoCorriente->isNodoHoja()) {

		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		Clave nuevaClave;
		Nodo* nuevoNodoHijo = NULL;
		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);

		bool resultado = insertarRecursivo(nodoHijo, clave, dato, id, &nuevaClave, &nuevoNodoHijo, idInsertado, incrementarID);

		if (nuevoNodoHijo) {

			if (nodoInteriorCorriente->isOverflow(nuevaClave.getTamanio() + TAM_CONTROL_REGISTRO + TAM_CONTROL_OVERFLOW)) {

				dividirNodoInterior(nodoInteriorCorriente, clavePromocion, nuevoNodo, posicion);

				if (posicion == nodoInteriorCorriente->cantidadClaves + 1
						&& nodoInteriorCorriente->cantidadClaves < (*nuevoNodo)->cantidadClaves) {

					NodoInterior *nuevoNodoInterior = static_cast<NodoInterior*> (*nuevoNodo);
					nodoInteriorCorriente->claves[nodoInteriorCorriente->cantidadClaves] = *clavePromocion;
					nodoInteriorCorriente->hijos[nodoInteriorCorriente->cantidadClaves + 1] = nuevoNodoInterior->hijos[0];
					nodoInteriorCorriente->cantidadClaves++;
					nodoInteriorCorriente->espacioOcupado += (*clavePromocion).getTamanio() + TAM_CONTROL_REGISTRO;
					nuevoNodoInterior->hijos[0] = nuevoNodoHijo->numero;
					*clavePromocion = nuevaClave;

					persistirNodo(nuevoNodoHijo);
					liberarMemoriaNodo(nuevoNodoHijo);

					persistirNodo(nodoHijo);
					liberarMemoriaNodo(nodoHijo);

					return resultado;

				} else {

					if (posicion >= nodoInteriorCorriente->cantidadClaves + 1) {
						posicion -= (nodoInteriorCorriente->cantidadClaves + 1);
						nodoInteriorCorriente = static_cast<NodoInterior*> (*nuevoNodo);
					}
				}
			}

			int i = nodoInteriorCorriente->cantidadClaves;
			while (i > posicion) {
				nodoInteriorCorriente->claves[i] = nodoInteriorCorriente->claves[i - 1];
				nodoInteriorCorriente->hijos[i + 1] = nodoInteriorCorriente->hijos[i];
				i--;
			}
			nodoInteriorCorriente->claves[posicion] = nuevaClave;
			nodoInteriorCorriente->hijos[posicion + 1] = nuevoNodoHijo->numero;
			nodoInteriorCorriente->cantidadClaves++;
			nodoInteriorCorriente->espacioOcupado += nuevaClave.getTamanio() + TAM_CONTROL_REGISTRO;

			persistirNodo(nuevoNodoHijo);
			liberarMemoriaNodo(nuevoNodoHijo);
		}
		persistirNodo(nodoHijo);
		liberarMemoriaNodo(nodoHijo);

		return resultado;

	} else {

		NodoHoja *nodoHojaCorriente = static_cast<NodoHoja*> (nodoCorriente);

		// Saco el frontcoding antes de calcular la posicion
		sacarFrontCodingNodoHoja(&nodoHojaCorriente);
		int posicion = obtenerPosicion(nodoHojaCorriente, clave);
		if (this->tipoDeArbol == 1){
			// chequea que no exista la clave
			if (posicion < nodoHojaCorriente->cantidadClaves && claveIgual(clave, nodoHojaCorriente->claves[posicion])) {
				*idInsertado = nodoHojaCorriente->Ids[posicion];
				return false;
			}
		}

		int i = nodoHojaCorriente->cantidadClaves - 1;
		while (i >= 0 && claveMenor(clave, nodoHojaCorriente->claves[i])) {
			nodoHojaCorriente->claves[i + 1] = nodoHojaCorriente->claves[i];
			nodoHojaCorriente->datos[i + 1] = nodoHojaCorriente->datos[i];
			nodoHojaCorriente->Ids[i + 1] = nodoHojaCorriente->Ids[i];
			i--;
		}
		nodoHojaCorriente->claves[i + 1] = clave;
		nodoHojaCorriente->datos[i + 1] = dato;
		if (this->tipoDeArbol == 1){
			if (incrementarID){
				id = obtenerNuevoId(this->pathId);
			}else{
				Persistencia uno("1");
				id = uno;
			}
				*idInsertado = id;
		}
		nodoHojaCorriente->Ids[i + 1] = id;
		nodoHojaCorriente->cantidadClaves++;
		if (nodoHojaCorriente->cantidadClaves > 1){
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
		}
		nodoHojaCorriente->espacioOcupado += nodoHojaCorriente->Ids[i + 1].getTamanio() + nodoHojaCorriente->datos[i + 1].getTamanio() + nodoHojaCorriente->claves[i + 1].getTamanio() + TAM_CONTROL_REGISTRO;

		if (nodoHojaCorriente->isOverflow(TAM_CONTROL_OVERFLOW)) {

			dividirNodoHoja(nodoHojaCorriente, clavePromocion, nuevoNodo);
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
			refactorizarNodoNoHojaFrontCoding(&(*nuevoNodo));
			if (posicion >= nodoHojaCorriente->cantidadClaves) {
				posicion -= nodoHojaCorriente->cantidadClaves;
				nodoHojaCorriente = static_cast<NodoHoja*> (*nuevoNodo);
			}
		}
		else{
			if (nodoHojaCorriente->nivel == 0){
				refactorizarNodoFrontCoding(&nodoHojaCorriente);
			}
		}
		if (nuevoNodo && nodoHojaCorriente != *nuevoNodo && posicion == nodoHojaCorriente->cantidadClaves - 1) {
			*clavePromocion = clave;
		}

		return true;
	}
}


void ArbolBMas::dividirNodoHoja(NodoHoja* unNodoHoja, Clave* clavePromocion, Nodo** nuevoNodoHoja) {
	sacarFrontCodingNodoHoja(&unNodoHoja);
	int espacioMedio = (unNodoHoja->espacioOcupado) / 2;
	int espacioNodoIzquierdo = 0;
	int cantidadClaves = 0;
	while (cantidadClaves < unNodoHoja->cantidadClaves && espacioNodoIzquierdo < espacioMedio){
		espacioNodoIzquierdo += unNodoHoja->Ids[cantidadClaves].getTamanio() + unNodoHoja->datos[cantidadClaves].getTamanio() + unNodoHoja->claves[cantidadClaves].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClaves++;
		if (espacioNodoIzquierdo > TAM_EFECTIVO_NODO) {
			cantidadClaves--;
			espacioNodoIzquierdo -= (unNodoHoja->Ids[cantidadClaves].getTamanio() + unNodoHoja->datos[cantidadClaves].getTamanio() + unNodoHoja->claves[cantidadClaves].getTamanio() + TAM_CONTROL_REGISTRO);
			break;
		}
	}

	NodoHoja *auxNuevoNodoHoja = crearNodoHoja();
	auxNuevoNodoHoja->numero = obtenerNumeroDeNodo();
	auxNuevoNodoHoja->cantidadClaves = unNodoHoja->cantidadClaves - cantidadClaves;
	auxNuevoNodoHoja->espacioOcupado = unNodoHoja->espacioOcupado - espacioNodoIzquierdo;
	auxNuevoNodoHoja->hojaSiguiente = unNodoHoja->hojaSiguiente;

	for (int posicion = cantidadClaves; posicion < unNodoHoja->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - cantidadClaves;
		auxNuevoNodoHoja->claves[auxPosicion] = unNodoHoja->claves[posicion];
		auxNuevoNodoHoja->datos[auxPosicion] = unNodoHoja->datos[posicion];
		auxNuevoNodoHoja->Ids[auxPosicion] = unNodoHoja->Ids[posicion];
	}

	unNodoHoja->espacioOcupado -= auxNuevoNodoHoja->espacioOcupado;
	unNodoHoja->cantidadClaves = cantidadClaves;
	unNodoHoja->hojaSiguiente = auxNuevoNodoHoja->numero;
	*clavePromocion = unNodoHoja->claves[unNodoHoja->cantidadClaves - 1];
	*nuevoNodoHoja = auxNuevoNodoHoja;
}


void ArbolBMas::dividirNodoInterior(NodoInterior* unNodoInterior, Clave* clavePromocion, Nodo** nuevoNodoInterior, int nuevaPosicion) {

	int medio = unNodoInterior->cantidadClaves / 2;

	if (nuevaPosicion <= medio && medio > unNodoInterior->cantidadClaves - (medio + 1)) {
		medio--;
	}

	NodoInterior *auxNuevoNodoInterior = crearNodoInterior(unNodoInterior->nivel);
	auxNuevoNodoInterior->numero = obtenerNumeroDeNodo();
	auxNuevoNodoInterior->cantidadClaves = unNodoInterior->cantidadClaves - (medio + 1);
	for (int posicion = medio + 1; posicion < unNodoInterior->cantidadClaves; ++posicion) {
		int auxPosicion = posicion - (medio + 1);
		auxNuevoNodoInterior->claves[auxPosicion] = unNodoInterior->claves[posicion];
		auxNuevoNodoInterior->hijos[auxPosicion] = unNodoInterior->hijos[posicion];
		auxNuevoNodoInterior->espacioOcupado += unNodoInterior->claves[posicion].getTamanio() + TAM_CONTROL_REGISTRO;
	}

	auxNuevoNodoInterior->hijos[auxNuevoNodoInterior->cantidadClaves] = unNodoInterior->hijos[unNodoInterior->cantidadClaves];
	unNodoInterior->cantidadClaves = medio;
	unNodoInterior->espacioOcupado -= auxNuevoNodoInterior->espacioOcupado;
	*clavePromocion = unNodoInterior->claves[medio];
	*nuevoNodoInterior = auxNuevoNodoInterior;
}

bool ArbolBMas::borrar(Elementos* elem) {
	if (!raiz)
		return false;
	int resultado = ArbolBMas::borrarRecursivo(elem, *(elem->getClave()), raiz, NULL, NULL, NULL, NULL, NULL, 0);
//	return !resultado.contiene(Resultado::NO_ENCONTRADO);
	return resultado != NO_ENCONTRADO;
}
int ArbolBMas::borrarRecursivo(Elementos* elem, Clave clave, Nodo *nodoCorriente, Nodo *nodoIzquierda, Nodo *nodoDerecha,
		NodoInterior *nodoPadreIzquierda, NodoInterior *nodoPadreDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	if (nodoCorriente->isNodoHoja()) {
		sacarFrontCodingNodo(&nodoCorriente);
		NodoHoja *nodoHojaCorriente = static_cast<NodoHoja*> (nodoCorriente);
		NodoHoja *nodoHojaIzquierda = static_cast<NodoHoja*> (nodoIzquierda);
		NodoHoja *nodoHojaDerecha = static_cast<NodoHoja*> (nodoDerecha);
		int posicion = obtenerPosicion(nodoHojaCorriente, clave);
		if (posicion >= nodoHojaCorriente->cantidadClaves || !claveIgual(clave, nodoHojaCorriente->claves[posicion])) {
//			return Resultado::NO_ENCONTRADO;
			return NO_ENCONTRADO;
		}

		//	Se fija cual es el que debe borrar en caso de que sea un arbol secundario
		if (this->tipoDeArbol == 2){
			Solucion res = buscarSecuencialClave(nodoHojaCorriente->numero, elem, posicion);
			posicion = res.getPosicion();

			if ( posicion == ERROR){
				return NO_ENCONTRADO;
			}
			if (nodoHojaCorriente->numero != res.getNodo()){


				Nodo *auxNodoActual, *auxNodoIzquierda, *auxNodoDerecha;
				auxNodoActual = hidratarNodo(res.getNodo());
				NodoHoja* aux =  static_cast<NodoHoja*>(auxNodoActual);
				int anterior = nodoHojaCorriente->numero;
				nodoHojaCorriente = aux;

				if ( aux->hojaSiguiente == 0){
					nodoHojaIzquierda = NULL;
					auxNodoDerecha = hidratarNodo(anterior);
					nodoHojaDerecha = static_cast<NodoHoja*>(auxNodoDerecha);
				}else{
					auxNodoIzquierda = hidratarNodo(aux->hojaSiguiente);
					nodoHojaIzquierda = static_cast<NodoHoja*>(auxNodoIzquierda);
					auxNodoDerecha = hidratarNodo(anterior);
					nodoHojaDerecha = static_cast<NodoHoja*>(auxNodoDerecha);
				}

			}
		}
		nodoHojaCorriente->espacioOcupado -= (nodoHojaCorriente->Ids[posicion].getTamanio() + nodoHojaCorriente->datos[posicion].getTamanio() + nodoHojaCorriente->claves[posicion].getTamanio() + TAM_CONTROL_REGISTRO);
		nodoHojaCorriente->cantidadClaves--;
		for (int i = posicion; i < nodoHojaCorriente->cantidadClaves; i++) {
			nodoHojaCorriente->claves[i] = nodoHojaCorriente->claves[i + 1];
			nodoHojaCorriente->datos[i] = nodoHojaCorriente->datos[i + 1];
			nodoHojaCorriente->Ids[i] = nodoHojaCorriente->Ids[i + 1];
		}

		int resultado = RESULTADO_OK;
//		Resultado resultado = Resultado::OK;

		// si se borro el elemento de la ultima posicion y no es la raiz
		if (posicion == nodoHojaCorriente->cantidadClaves && nodoPadre) {
			if (posicionPadre < nodoPadre->cantidadClaves) {
				if (nodoHojaCorriente->cantidadClaves >= 1) {
					nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
					nodoPadre->espacioOcupado += nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1].getTamanio();
					nodoPadre->claves[posicionPadre] = nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1];
				}
			} else {
				if (nodoHojaCorriente->cantidadClaves >= 1) {
					resultado = ACTUALIZAR_ULTIMA_CLAVE;
					ultimaClave = nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1];
				} else {
					resultado = ACTUALIZAR_ULTIMA_CLAVE;
					ultimaClave = nodoHojaIzquierda->claves[nodoHojaIzquierda->cantidadClaves - 1];
				}
//				if (nodoHojaCorriente->cantidadClaves >= 1) {
//					resultado |= Resultado (Resultado::ACTUALIZAR_ULTIMA_CLAVE, nodoHojaCorriente->claves[nodoHojaCorriente->cantidadClaves - 1]);
//				} else {
//					resultado |= Resultado (Resultado::ACTUALIZAR_ULTIMA_CLAVE, nodoHojaIzquierda->claves[nodoHojaIzquierda->cantidadClaves - 1]);
//				}
			}
		}
		refactorizarNodoFrontCoding(&nodoHojaCorriente);
		if (nodoHojaCorriente->isUnderflow() && !(nodoHojaCorriente == raiz && nodoHojaCorriente->cantidadClaves >= 1)) {

			if (nodoHojaIzquierda == NULL && nodoHojaDerecha == NULL) {
				if (raiz)
					liberarMemoriaNodo(raiz);
				raiz = nodoHojaCorriente = NULL;
				primeraHoja = 0;
				string archivoConfiguracion = persistor->getRuta() + "_Configuracion.txt";
				remove(archivoConfiguracion.c_str());

				string archivoNodos = persistor->getRuta() + "_Nodos.txt";
				remove(archivoNodos.c_str());

				string archivoFrontCoding = persistor->getRuta() + "_FrontCoding.txt";
				remove(archivoFrontCoding.c_str());

				return RESULTADO_OK;
//				return Resultado::OK;

			} else if (((nodoHojaIzquierda == NULL || !nodoHojaIzquierda->puedeCederElementos())
					&& (nodoHojaDerecha == NULL || !nodoHojaDerecha->puedeCederElementos()))
					|| nodoHojaCorriente->cantidadClaves == 0) {

				if (nodoPadreIzquierda == nodoPadre) {
					resultado = fusionarHojas(nodoHojaIzquierda, nodoHojaCorriente);
				} else {
					resultado = fusionarHojas(nodoHojaCorriente, nodoHojaDerecha);
				}

			} else if ((nodoHojaIzquierda != NULL && !nodoHojaIzquierda->puedeCederElementos())
					&& (nodoHojaDerecha != NULL && nodoHojaDerecha->puedeCederElementos())) {

				if (nodoPadreDerecha == nodoPadre) {
					resultado = pasarElementosHojaIzquierda(nodoHojaCorriente, nodoHojaDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					resultado = fusionarHojas(nodoHojaIzquierda, nodoHojaCorriente);
				}

			} else if ((nodoHojaIzquierda != NULL && nodoHojaIzquierda->puedeCederElementos())
					&& (nodoHojaDerecha != NULL && !nodoHojaDerecha->puedeCederElementos())) {

				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosHojaDerecha(nodoHojaIzquierda, nodoHojaCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					resultado = fusionarHojas(nodoHojaCorriente, nodoHojaDerecha);
				}

			} else if (nodoPadreIzquierda == nodoPadreDerecha) {
				if (nodoHojaIzquierda->espacioOcupado <= nodoHojaDerecha->espacioOcupado) {
					resultado = pasarElementosHojaIzquierda(nodoHojaCorriente, nodoHojaDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					pasarElementosHojaDerecha(nodoHojaIzquierda, nodoHojaCorriente, nodoPadreIzquierda, posicionPadre - 1);
				}

			} else {
				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosHojaDerecha(nodoHojaIzquierda, nodoHojaCorriente, nodoPadreIzquierda, posicionPadre	- 1);
				} else {
					resultado = pasarElementosHojaIzquierda(nodoHojaCorriente, nodoHojaDerecha, nodoPadreDerecha, posicionPadre);
				}
			}
		} else {
			refactorizarNodoFrontCoding(&nodoHojaCorriente);
			persistirNodo(nodoHojaCorriente);
		}
		return resultado;

	} else {

		NodoInterior *nodoInteriorCorriente = static_cast<NodoInterior*> (nodoCorriente);
		NodoInterior *nodoInteriorIzquierda = static_cast<NodoInterior*> (nodoIzquierda);
		NodoInterior *nodoInteriorDerecha = static_cast<NodoInterior*> (nodoDerecha);
		Nodo *auxNodoIzquierda, *auxNodoDerecha;
		NodoInterior *auxPadreIzquierda, *auxPadreDerecha;

		int posicion = obtenerPosicion(nodoInteriorCorriente, clave);
		if (posicion == 0) {
			auxNodoIzquierda = (nodoIzquierda == NULL) ? NULL : hidratarNodo((static_cast<NodoInterior*> (nodoIzquierda))->hijos[nodoIzquierda->cantidadClaves]);
			auxPadreIzquierda = nodoPadreIzquierda;
		} else {
			auxNodoIzquierda = hidratarNodo(nodoInteriorCorriente->hijos[posicion - 1]);
			auxPadreIzquierda = nodoInteriorCorriente;
		}

		if (posicion == nodoInteriorCorriente->cantidadClaves) {
			auxNodoDerecha = (nodoDerecha == NULL) ? NULL : hidratarNodo((static_cast<NodoInterior*> (nodoDerecha))->hijos[0]);
			auxPadreDerecha = nodoPadreDerecha;
		} else {
			auxNodoDerecha = hidratarNodo(nodoInteriorCorriente->hijos[posicion + 1]);
			auxPadreDerecha = nodoInteriorCorriente;
		}

		Nodo* auxNodoCorriente = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);
		int resultadoParcial = borrarRecursivo(elem, clave, auxNodoCorriente, auxNodoIzquierda, auxNodoDerecha, auxPadreIzquierda, auxPadreDerecha, nodoInteriorCorriente, posicion);
//		Resultado resultado = Resultado::OK;
		int resultado = RESULTADO_OK;

		if (auxNodoIzquierda)
			liberarMemoriaNodo(auxNodoIzquierda);
		if (auxNodoDerecha)
			liberarMemoriaNodo(auxNodoDerecha);
		if (auxNodoCorriente)
			liberarMemoriaNodo(auxNodoCorriente);

//		if (resultadoParcial.contiene(Resultado::NO_ENCONTRADO)) {
		if (resultadoParcial == NO_ENCONTRADO) {
			return resultadoParcial;
		}

//		if (resultadoParcial.contiene(Resultado::ACTUALIZAR_ULTIMA_CLAVE)) {
		if ( resultadoParcial == ACTUALIZAR_ULTIMA_CLAVE ) {
			if (nodoPadre && posicionPadre < nodoPadre->cantidadClaves) {
				nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
				nodoPadre->espacioOcupado += ultimaClave.getTamanio();
				nodoPadre->claves[posicionPadre] = ultimaClave;
			}
		}

//		if (resultadoParcial.contiene(Resultado::FUSION_NODOS)) {
		if (resultadoParcial == FUSION) {
			Nodo* nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);
			if (nodoHijo->cantidadClaves != 0)
				posicion++;

			Clave claveInteriorBorrada = nodoInteriorCorriente->claves[posicion - 1];
			for (int i = posicion; i < nodoInteriorCorriente->cantidadClaves; i++) {
				nodoInteriorCorriente->claves[i - 1] = nodoInteriorCorriente->claves[i];
				nodoInteriorCorriente->hijos[i] = nodoInteriorCorriente->hijos[i + 1];
			}
			nodoInteriorCorriente->cantidadClaves--;
			nodoInteriorCorriente->espacioOcupado -= (claveInteriorBorrada.getTamanio() + TAM_CONTROL_REGISTRO);
			nodoInteriorCorriente->espacioOcupado -= nodoInteriorCorriente->claves[nodoInteriorCorriente->cantidadClaves].getTamanio();

			if (nodoHijo)
				liberarMemoriaNodo(nodoHijo);
			if (nodoInteriorCorriente->nivel == 1) {
				posicion--;
				nodoHijo = hidratarNodo(nodoInteriorCorriente->hijos[posicion]);
				nodoInteriorCorriente->espacioOcupado -= nodoInteriorCorriente->claves[posicion].getTamanio();
				nodoInteriorCorriente->espacioOcupado += nodoHijo->claves[nodoHijo->cantidadClaves - 1].getTamanio();
				nodoInteriorCorriente->claves[posicion] = nodoHijo->claves[nodoHijo->cantidadClaves - 1];
				if (nodoHijo)
					liberarMemoriaNodo(nodoHijo);
			}
		}

//		if (resultadoParcial.contiene(Resultado::FUSION_NODOS)
		if (resultadoParcial == FUSION
				&& nodoInteriorCorriente->isUnderflow()
				&& !(nodoInteriorCorriente == raiz && nodoInteriorCorriente->cantidadClaves >= 1)) {

			if (nodoInteriorIzquierda == NULL && nodoInteriorDerecha == NULL) {
				raiz = hidratarNodo(nodoInteriorCorriente->hijos[0]);
				raiz->numero = 0;
				persistirNodo(raiz);
				nodosLibres.push_back(nodoInteriorCorriente->hijos[0]);
				persistirDatosConfiguracion();
//				return Resultado::OK;
				return RESULTADO_OK;

			} else if ((nodoInteriorIzquierda == NULL || !nodoInteriorIzquierda->puedeCederElementos())
					&& (nodoInteriorDerecha == NULL || !nodoInteriorDerecha->puedeCederElementos())) {

				if (nodoPadreIzquierda == nodoPadre) {
					resultado = fusionarNodosInteriores(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					resultado = fusionarNodosInteriores(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				}

			} else if ((nodoInteriorIzquierda != NULL && !nodoInteriorIzquierda->puedeCederElementos())
					&& (nodoInteriorDerecha != NULL && nodoInteriorDerecha->puedeCederElementos())) {

				if (nodoPadreDerecha == nodoPadre) {
					pasarElementosNodoInteriorIzquierdo(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					resultado = fusionarNodosInteriores(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				}

			} else if ((nodoInteriorIzquierda != NULL && nodoInteriorIzquierda->puedeCederElementos())
					&& (nodoInteriorDerecha != NULL && !nodoInteriorDerecha->puedeCederElementos())) {

				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosNodoInteriorDerecho(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					resultado = fusionarNodosInteriores(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				}

			} else if (nodoPadreIzquierda == nodoPadreDerecha) {

				if (nodoInteriorIzquierda->cantidadClaves <= nodoInteriorDerecha->cantidadClaves) {
					pasarElementosNodoInteriorIzquierdo(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				} else {
					pasarElementosNodoInteriorDerecho(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				}

			} else {

				if (nodoPadreIzquierda == nodoPadre) {
					pasarElementosNodoInteriorDerecho(nodoInteriorIzquierda, nodoInteriorCorriente, nodoPadreIzquierda, posicionPadre - 1);
				} else {
					pasarElementosNodoInteriorIzquierdo(nodoInteriorCorriente, nodoInteriorDerecha, nodoPadreDerecha, posicionPadre);
				}
			}

		} else {
			persistirNodo(nodoInteriorCorriente);
		}

		return resultado;
	}
}


int ArbolBMas::fusionarHojas(NodoHoja* hojaIzquierda, NodoHoja* hojaDerecha) {
	sacarFrontCodingNodoHoja(&hojaIzquierda);
	sacarFrontCodingNodoHoja(&hojaDerecha);
	for (int i = 0; i < hojaDerecha->cantidadClaves; i++) {
		hojaIzquierda->claves[hojaIzquierda->cantidadClaves + i] = hojaDerecha->claves[i];
		hojaIzquierda->datos[hojaIzquierda->cantidadClaves + i] = hojaDerecha->datos[i];
		hojaIzquierda->Ids[hojaIzquierda->cantidadClaves + i] = hojaDerecha->Ids[i];
	}
	hojaIzquierda->cantidadClaves += hojaDerecha->cantidadClaves;
	hojaIzquierda->espacioOcupado += hojaDerecha->espacioOcupado;
	hojaIzquierda->hojaSiguiente = hojaDerecha->hojaSiguiente;

	hojaDerecha->cantidadClaves = 0;
	hojaDerecha->espacioOcupado = 0;

	nodosLibres.push_back(hojaDerecha->numero);
	persistirDatosConfiguracion();
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);

	return FUSION;
}


int ArbolBMas::fusionarNodosInteriores(NodoInterior* nodoIzquierda, NodoInterior* nodoDerecha, NodoInterior* nodoPadre, int posicionPadre) {

	int resultado;
	int espacioOcupadoTotal = (nodoIzquierda->espacioOcupado + nodoDerecha->espacioOcupado + nodoPadre->claves[posicionPadre].getTamanio() + TAM_CONTROL_REGISTRO);

	if (espacioOcupadoTotal > TAM_EFECTIVO_NODO) {
		resultado = RESULTADO_OK;
	} else {
		nodoIzquierda->claves[nodoIzquierda->cantidadClaves] = nodoPadre->claves[posicionPadre];
		nodoIzquierda->cantidadClaves++;
		nodoIzquierda->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio() + TAM_CONTROL_REGISTRO;
		for (int i = 0; i < nodoDerecha->cantidadClaves; i++) {
			nodoIzquierda->claves[nodoIzquierda->cantidadClaves + i] = nodoDerecha->claves[i];
			nodoIzquierda->hijos[nodoIzquierda->cantidadClaves + i] = nodoDerecha->hijos[i];
		}
		nodoIzquierda->cantidadClaves += nodoDerecha->cantidadClaves;
		nodoIzquierda->espacioOcupado += nodoDerecha->espacioOcupado;
		nodoIzquierda->hijos[nodoIzquierda->cantidadClaves] = nodoDerecha->hijos[nodoDerecha->cantidadClaves];
		nodoDerecha->cantidadClaves = 0;
		nodoDerecha->espacioOcupado = 0;

		nodosLibres.push_back(nodoDerecha->numero);
		persistirDatosConfiguracion();

		resultado = FUSION;
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);

	return resultado;
}


int ArbolBMas::pasarElementosHojaIzquierda(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int tamanioMedio = (hojaDerecha->espacioOcupado - hojaIzquierda->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	while (cantidadClavesDesplazadas < hojaDerecha->cantidadClaves && espacioDesplazado < tamanioMedio){
		espacioDesplazado += hojaDerecha->Ids[cantidadClavesDesplazadas].getTamanio()
							+ hojaDerecha->datos[cantidadClavesDesplazadas].getTamanio()
						   + hojaDerecha->claves[cantidadClavesDesplazadas].getTamanio()
						   + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + hojaIzquierda->espacioOcupado > TAM_EFECTIVO_NODO) {
			cantidadClavesDesplazadas--;
			espacioDesplazado -= (hojaDerecha->Ids[cantidadClavesDesplazadas].getTamanio()
							   + hojaDerecha->datos[cantidadClavesDesplazadas].getTamanio()
							   + hojaDerecha->claves[cantidadClavesDesplazadas].getTamanio()
							   + TAM_CONTROL_REGISTRO);
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		for (int i = 0; i < cantidadClavesDesplazadas; i++) {
			hojaIzquierda->claves[hojaIzquierda->cantidadClaves + i] = hojaDerecha->claves[i];
			hojaIzquierda->datos[hojaIzquierda->cantidadClaves + i] = hojaDerecha->datos[i];
			hojaIzquierda->Ids[hojaIzquierda->cantidadClaves + i] = hojaDerecha->Ids[i];
		}

		hojaIzquierda->cantidadClaves += cantidadClavesDesplazadas;
		hojaIzquierda->espacioOcupado += espacioDesplazado;
		hojaDerecha->cantidadClaves -= cantidadClavesDesplazadas;
		hojaDerecha->espacioOcupado -= espacioDesplazado;
		for (int i = 0; i < hojaDerecha->cantidadClaves; i++) {
			hojaDerecha->claves[i] = hojaDerecha->claves[i + cantidadClavesDesplazadas];
			hojaDerecha->datos[i] = hojaDerecha->datos[i + cantidadClavesDesplazadas];
			hojaDerecha->Ids[i] = hojaDerecha->Ids[i + cantidadClavesDesplazadas];
		}
	}
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);

	if (cantidadClavesDesplazadas > 0) {
		if (posicionPadre < nodoPadre->cantidadClaves) {
			nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
			nodoPadre->espacioOcupado += hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1].getTamanio();
			nodoPadre->claves[posicionPadre] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
			return RESULTADO_OK;
		} else {
//			return Resultado(Resultado::ACTUALIZAR_ULTIMA_CLAVE, hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1]);
			ultimaClave = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
			return ACTUALIZAR_ULTIMA_CLAVE;
		}
	} else {
		return RESULTADO_OK;
	}
}


void ArbolBMas::pasarElementosNodoInteriorIzquierdo(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha,	NodoInterior *nodoPadre, int posicionPadre) {

	int tamanioMedio = (nodoDerecha->espacioOcupado - nodoIzquierda->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	while (cantidadClavesDesplazadas < nodoDerecha->cantidadClaves && espacioDesplazado < tamanioMedio){
		espacioDesplazado += nodoDerecha->claves[cantidadClavesDesplazadas].getTamanio()
						   + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + nodoIzquierda->espacioOcupado > TAM_EFECTIVO_NODO) {
			cantidadClavesDesplazadas--;
			espacioDesplazado -= (nodoDerecha->claves[cantidadClavesDesplazadas].getTamanio()
							   + TAM_CONTROL_REGISTRO);
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		espacioDesplazado = 0;

		nodoIzquierda->claves[nodoIzquierda->cantidadClaves] = nodoPadre->claves[posicionPadre];
		nodoIzquierda->cantidadClaves++;
		nodoIzquierda->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio() + TAM_CONTROL_REGISTRO;

		for (int i = 0; i < cantidadClavesDesplazadas - 1; i++) {
			nodoIzquierda->claves[nodoIzquierda->cantidadClaves + i] = nodoDerecha->claves[i];
			nodoIzquierda->hijos[nodoIzquierda->cantidadClaves + i] = nodoDerecha->hijos[i];
			espacioDesplazado += nodoDerecha->claves[i].getTamanio() + TAM_CONTROL_REGISTRO;
		}

		nodoIzquierda->cantidadClaves += cantidadClavesDesplazadas - 1;
		nodoIzquierda->espacioOcupado += espacioDesplazado;
		nodoIzquierda->hijos[nodoIzquierda->cantidadClaves] = nodoDerecha->hijos[cantidadClavesDesplazadas - 1];
		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += nodoDerecha->claves[cantidadClavesDesplazadas - 1].getTamanio();
		nodoPadre->claves[posicionPadre] = nodoDerecha->claves[cantidadClavesDesplazadas - 1];
		nodoDerecha->cantidadClaves -= cantidadClavesDesplazadas;
		nodoDerecha->espacioOcupado -= espacioDesplazado;
		nodoDerecha->espacioOcupado -= nodoDerecha->claves[cantidadClavesDesplazadas - 1].getTamanio();

		for (int i = 0; i < nodoDerecha->cantidadClaves; i++) {
			nodoDerecha->claves[i] = nodoDerecha->claves[i + cantidadClavesDesplazadas];
			nodoDerecha->hijos[i] = nodoDerecha->hijos[i + cantidadClavesDesplazadas];
		}
		nodoDerecha->hijos[nodoDerecha->cantidadClaves] = nodoDerecha->hijos[nodoDerecha->cantidadClaves + cantidadClavesDesplazadas];
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);
}


void ArbolBMas::pasarElementosHojaDerecha(NodoHoja *hojaIzquierda, NodoHoja *hojaDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int espacioOcupadoMedio = (hojaIzquierda->espacioOcupado - hojaDerecha->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	for (int i = hojaIzquierda->cantidadClaves; i > 0 && espacioDesplazado < espacioOcupadoMedio; i--) {
		espacioDesplazado += hojaIzquierda->Ids[i-1].getTamanio() + hojaIzquierda->datos[i-1].getTamanio() + hojaIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + hojaDerecha->espacioOcupado > TAM_EFECTIVO_NODO) {
			espacioDesplazado -= (hojaIzquierda->Ids[i-1].getTamanio() + hojaIzquierda->datos[i-1].getTamanio() + hojaIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO);
			cantidadClavesDesplazadas--;
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		for (int i = hojaDerecha->cantidadClaves; i >= 0; i--) {
			hojaDerecha->claves[i + cantidadClavesDesplazadas] = hojaDerecha->claves[i];
			hojaDerecha->datos[i + cantidadClavesDesplazadas] = hojaDerecha->datos[i];
			hojaDerecha->Ids[i + cantidadClavesDesplazadas] = hojaDerecha->Ids[i];
		}
		hojaDerecha->cantidadClaves += cantidadClavesDesplazadas;
		hojaDerecha->espacioOcupado += espacioDesplazado;

		for (int i = 0; i < cantidadClavesDesplazadas; i++) {
			hojaDerecha->claves[i] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
			hojaDerecha->datos[i] = hojaIzquierda->datos[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
			hojaDerecha->Ids[i] = hojaIzquierda->Ids[hojaIzquierda->cantidadClaves - cantidadClavesDesplazadas + i];
		}
		hojaIzquierda->cantidadClaves -= cantidadClavesDesplazadas;
		hojaIzquierda->espacioOcupado -= espacioDesplazado;
		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1].getTamanio();
		nodoPadre->claves[posicionPadre] = hojaIzquierda->claves[hojaIzquierda->cantidadClaves - 1];
	}
	refactorizarNodoFrontCoding(&hojaDerecha);
	refactorizarNodoFrontCoding(&hojaIzquierda);
	persistirNodo(hojaIzquierda);
	persistirNodo(hojaDerecha);
}


void ArbolBMas::pasarElementosNodoInteriorDerecho(NodoInterior *nodoIzquierda, NodoInterior *nodoDerecha, NodoInterior *nodoPadre, int posicionPadre) {

	int espacioOcupadoMedio = (nodoIzquierda->espacioOcupado - nodoDerecha->espacioOcupado) / 2;
	int espacioDesplazado = 0;
	int cantidadClavesDesplazadas = 0;
	for (int i = nodoIzquierda->cantidadClaves; i > 0 && espacioDesplazado < espacioOcupadoMedio; i--) {
		espacioDesplazado += nodoIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO;
		cantidadClavesDesplazadas++;
		if (espacioDesplazado + nodoDerecha->espacioOcupado > TAM_EFECTIVO_NODO) {
			espacioDesplazado -= (nodoIzquierda->claves[i-1].getTamanio() + TAM_CONTROL_REGISTRO);
			cantidadClavesDesplazadas--;
			break;
		}
	}

	if (cantidadClavesDesplazadas > 0) {
		espacioDesplazado = 0;

		nodoDerecha->hijos[nodoDerecha->cantidadClaves + cantidadClavesDesplazadas] = nodoDerecha->hijos[nodoDerecha->cantidadClaves];

		for (int i = nodoDerecha->cantidadClaves - 1; i >= 0; i--) {
			nodoDerecha->claves[i + cantidadClavesDesplazadas] = nodoDerecha->claves[i];
			nodoDerecha->hijos[i + cantidadClavesDesplazadas] = nodoDerecha->hijos[i];
		}

		nodoDerecha->cantidadClaves += cantidadClavesDesplazadas;
		nodoDerecha->claves[cantidadClavesDesplazadas - 1] = nodoPadre->claves[posicionPadre];
		nodoDerecha->hijos[cantidadClavesDesplazadas - 1] = nodoIzquierda->hijos[nodoIzquierda->cantidadClaves];
		nodoDerecha->espacioOcupado += nodoPadre->claves[posicionPadre].getTamanio()+ TAM_CONTROL_REGISTRO;

		for (int i = 0; i < cantidadClavesDesplazadas - 1; i++) {
			nodoDerecha->claves[i] = nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas + i + 1];
			nodoDerecha->hijos[i] = nodoIzquierda->hijos[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas + i + 1];
			espacioDesplazado += nodoDerecha->claves[i].getTamanio() + TAM_CONTROL_REGISTRO;
		}
		nodoDerecha->espacioOcupado += espacioDesplazado;

		nodoPadre->espacioOcupado -= nodoPadre->claves[posicionPadre].getTamanio();
		nodoPadre->espacioOcupado += nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas].getTamanio();
		nodoPadre->claves[posicionPadre] = nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas];
		nodoIzquierda->cantidadClaves -= cantidadClavesDesplazadas;
		nodoIzquierda->espacioOcupado -= espacioDesplazado;
		nodoIzquierda->espacioOcupado -= (nodoIzquierda->claves[nodoIzquierda->cantidadClaves - cantidadClavesDesplazadas].getTamanio());
	}
	persistirNodo(nodoIzquierda);
	persistirNodo(nodoDerecha);
}

void ArbolBMas::persistirNodo(Nodo* unNodo) {
	persistor->guardarBloque(unNodo->numero, unNodo->Serializar());
}


Nodo* ArbolBMas::hidratarNodo(int numeroDeNodo) {

	Persistencia cadena = this->persistor->leerBloque(numeroDeNodo);
	if (cadena.estaVacia()) {
		return NULL;
	} else {
		int nivel = cadena.leerEntero(0);
		if (nivel == 0) {
			NodoHoja *nuevoNodoHoja = crearNodoHoja();
			nuevoNodoHoja->Hidratar(cadena);
			nuevoNodoHoja->numero = numeroDeNodo;
			return nuevoNodoHoja;
		} else {
			NodoInterior *nuevoNodoInterior = crearNodoInterior(nivel);
			nuevoNodoInterior->Hidratar(cadena);
			nuevoNodoInterior->numero = numeroDeNodo;
			return nuevoNodoInterior;
		}
	}
}


int ArbolBMas::obtenerNumeroDeNodo() {
	int numeroDeNodo;
	if (nodosLibres.empty()) {
		this->cantidadNodos++;
		numeroDeNodo = this->cantidadNodos-1;
	} else {
		numeroDeNodo = nodosLibres.back();
		nodosLibres.pop_back();
		persistirDatosConfiguracion();
	}
	return numeroDeNodo;
}


void ArbolBMas::persistirDatosConfiguracion() {
	vector<int>::iterator it = nodosLibres.begin();
	string nombreArchivo = persistor->getRuta() + "_Configuracion.txt";
	ofstream ofs(nombreArchivo.c_str());

	if (!ofs.fail()) {

		ofs.write((char*)(&primeraHoja),sizeof(int));

		while (it != nodosLibres.end()) {
			int numeroDeNodo = *it;
			ofs.write((char*)(&numeroDeNodo),sizeof(int));
			it++;
		}
	}
	ofs.close();
}


void ArbolBMas::hidratarDatosConfiguracion() {

	nodosLibres.clear();
	string nombreArchivo = persistor->getRuta() + "_Configuracion.txt";
	fstream ifs(nombreArchivo.c_str());

	if (ifs.is_open()) {

		ifs.seekg(0, ios_base::end);
		int tamanio = ifs.tellg();
		ifs.seekg(0, ios_base::beg);


	if (tamanio != 0){
		char* sPrimeraHoja = new char[sizeof(int)];
		ifs.read(sPrimeraHoja,sizeof(int));
		primeraHoja = *((int*)sPrimeraHoja);
		delete[] sPrimeraHoja;

			while (ifs.tellg() < tamanio) {
				char* s = new char[sizeof(int)];
				ifs.read(s,sizeof(int));
				int numeroDeNodo = *((int*)s);
				nodosLibres.push_back(numeroDeNodo);
				delete[] s;
		}
	}
		ifs.close();
	}else{
		ifs.open(nombreArchivo.c_str(), ios_base::out);
		ifs.close();

	}
}
Solucion ArbolBMas::buscarSecuencialClave(int nodo, Elementos* elemento, int posicion){

	Solucion res;
	bool encontrado = false;
	int i = 0;
	Nodo* auxNodo = hidratarNodo(nodo);
	NodoHoja* hojaCorriente = static_cast<NodoHoja*>(auxNodo);
	sacarFrontCodingNodoHoja(&hojaCorriente);

	while (!encontrado && hojaCorriente->datos[posicion + i].toString() == elemento->getDatos()->toString() && ((posicion+i) < hojaCorriente->cantidadClaves)){
		if (hojaCorriente->Ids[posicion + i].toString() == elemento->getID()->toString()){
			encontrado = true;
		}
		++i;
	}
	if (!encontrado){
		if (hojaCorriente->datos[posicion + i -1].toString() == elemento->getDatos()->toString() && (posicion + i ) == hojaCorriente->cantidadClaves){
			Nodo* nodoAux = hidratarNodo(hojaCorriente->hojaSiguiente);
			NodoHoja *nodoHojaDerecha = static_cast<NodoHoja*> (nodoAux);
			res = buscarSecuencialClave(nodoHojaDerecha->numero, elemento,0);
		}else{
			res.setNodo(hojaCorriente->numero);
			res.setPosicion(ERROR);
		}
	}else{
		res.setNodo(hojaCorriente->numero);
		res.setPosicion(posicion + i -1);
	}
	return res;
}

void ArbolBMas::buscar(list<Elementos*>* listaElementos, Clave* clave){

	Nodo *unNodo = raiz;
	if (unNodo){

		while (!unNodo->isNodoHoja()) {
			NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
			int posicion = obtenerPosicion(unNodoInterior, *(clave));
			unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
			if (unNodoInterior != raiz)
				liberarMemoriaNodo(unNodoInterior);
		}

		NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
		int posicion = obtenerPosicion(unNodoHoja, *(clave));

		llenarListadeBusqueda(listaElementos, unNodoHoja, posicion, clave);
	}

}

void ArbolBMas::llenarListadeBusqueda(list<Elementos*>* listaElementos, NodoHoja* nodo, int posicion, Clave* clave){
	bool distinto = false;
	this->sacarFrontCodingNodoHoja(&nodo);
	for (int i = posicion; (i < nodo->cantidadClaves) && (!distinto); ++i){
		if (nodo->claves[i].getClave() == clave->getClave()){
			Elementos* elemento = new Elementos(clave, new Persistencia(nodo->datos[i].toString()), new Persistencia(nodo->Ids[i].toString()));
			listaElementos->push_back(elemento);
		}else{
			distinto = true;
		}
	}
	if(!distinto && nodo->hojaSiguiente != 0){
		Nodo * nuevoNodo = hidratarNodo(nodo->hojaSiguiente);
		NodoHoja* nuevoNodoHoja = static_cast<NodoHoja*> (nuevoNodo);
		refactorizarNodoFrontCoding(&nodo);
		llenarListadeBusqueda(listaElementos, nuevoNodoHoja, 0 , clave);
	}
}
Persistencia ArbolBMas::obtenerNuevoId(string path){
	Persistencia cadenaRetorno;
	string modificacion;
	modificacion.clear();
	std::fstream archivoId;
	char  cadenaDeDatos[50];

	archivoId.open(path.c_str(), std::ios_base::in | std::ios_base::out);

	if (archivoId.is_open()){
		archivoId.seekg(0);
		archivoId.get(cadenaDeDatos,50);
		modificacion = cadenaDeDatos;
		archivoId.close();
	}else{
		archivoId.open(path.c_str(), std::ios_base::out);
		archivoId.close();
		archivoId.open(path.c_str(), std::ios_base::in | std::ios_base::out);
		modificacion  = "0";
		archivoId.close();
	}
	cadenaRetorno.setBytes(modificacion);
	int valor = atoi(modificacion.c_str());
	++valor;
	stringstream ss;
	ss << valor;
	archivoId.open(path.c_str(), std::ios_base::out);
	archivoId.close();
	archivoId.open(path.c_str(), std::ios_base::in | std::ios_base::out);

	archivoId.seekg(0);
	archivoId.write(ss.str().c_str(), ss.str().length());
	archivoId.flush();
	archivoId.close();
	return cadenaRetorno;
}

bool ArbolBMas::modificar(Elementos* registro) {
	Nodo *unNodo = raiz;
	if (!unNodo)
		return false;

	while (!unNodo->isNodoHoja()) {
		NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
		int posicion = obtenerPosicion(unNodoInterior, *(registro->getClave()));
		unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
		if (unNodoInterior != raiz)
			liberarMemoriaNodo(unNodoInterior);
	}

	NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
	int posicion = obtenerPosicion(unNodoHoja, *(registro->getClave()));
	bool existe = (posicion < unNodoHoja->cantidadClaves && claveIgual(*(registro->getClave()), unNodoHoja->claves[posicion]));
	if (existe) {
		unNodoHoja->Ids[posicion].setBytes(registro->getID()->toString());
		persistirNodo(unNodoHoja);
		return true;
	} else {
		if (unNodoHoja != raiz)
			liberarMemoriaNodo(unNodoHoja);
		return false;
	}
}

bool ArbolBMas::incrementarID(Elementos* registro, int & frecuencia){

	Nodo *unNodo = raiz;
	if (!unNodo)
		return false;

	while (!unNodo->isNodoHoja()) {
		NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
		int posicion = obtenerPosicion(unNodoInterior, *(registro->getClave()));
		unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
		if (unNodoInterior != raiz)
			liberarMemoriaNodo(unNodoInterior);
	}

	NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
	int posicion = obtenerPosicion(unNodoHoja, *(registro->getClave()));
	bool existe = (posicion < unNodoHoja->cantidadClaves && claveIgual(*(registro->getClave()), unNodoHoja->claves[posicion]));
	if (existe) {
		int actual = atoi(unNodoHoja->Ids[posicion].toString().c_str());
		++actual;
		frecuencia = actual;
		stringstream ss;
		ss << actual;
		unNodoHoja->Ids[posicion].setBytes(ss.str());
		persistirNodo(unNodoHoja);
		return true;
	} else {
		if (unNodoHoja != raiz)
			liberarMemoriaNodo(unNodoHoja);
		return false;
	}
}

bool ArbolBMas::decrementarID(Elementos* registro){

	Nodo *unNodo = raiz;
	if (!unNodo)
		return false;

	while (!unNodo->isNodoHoja()) {
		NodoInterior *unNodoInterior = static_cast<NodoInterior*> (unNodo);
		int posicion = obtenerPosicion(unNodoInterior, *(registro->getClave()));
		unNodo = hidratarNodo(unNodoInterior->hijos[posicion]);
		if (unNodoInterior != raiz)
			liberarMemoriaNodo(unNodoInterior);
	}

	NodoHoja *unNodoHoja = static_cast<NodoHoja*> (unNodo);
	int posicion = obtenerPosicion(unNodoHoja, *(registro->getClave()));
	bool existe = (posicion < unNodoHoja->cantidadClaves && claveIgual(*(registro->getClave()), unNodoHoja->claves[posicion]));
	if (existe) {
		int actual = atoi(unNodoHoja->Ids[posicion].toString().c_str());
		if (actual > 0){
			--actual;
			stringstream ss;
			ss << actual;
			unNodoHoja->Ids[posicion].setBytes(ss.str());
			persistirNodo(unNodoHoja);
		}
		return true;
	} else {
		if (unNodoHoja != raiz)
			liberarMemoriaNodo(unNodoHoja);
		return false;
	}
}
