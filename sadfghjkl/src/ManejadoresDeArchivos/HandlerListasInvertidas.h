/*
 * HandlerListasInvertidas.h
 *
 *  Created on: 29/05/2011
 *      Author: lucas
 */

#ifndef HANDLERLISTASINVERTIDAS_H_
#define HANDLERLISTASINVERTIDAS_H_
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../EstructurasEnComun/Ocurrencia.h"
#include "../EstructurasEnComun/Constantes.h"
#include "../CompresorGamma/CodigoGamma.h"

class HandlerListasInvertidas {
public:
	HandlerListasInvertidas();
	void construirListaInvertida(list<Ocurrencia> ocurrencias);
	virtual ~HandlerListasInvertidas();
private:
	string comprimirListaInvertida(list<int> listaInvertida, int primero);
	int insertarLista(string listaEnGamma, int& offset);
	void insertarLineaIndice(string lineaIndice);
	void crearArchivo();
	void guardarPrimero(int primero);
};

#endif /* HANDLERLISTASINVERTIDAS_H_ */
