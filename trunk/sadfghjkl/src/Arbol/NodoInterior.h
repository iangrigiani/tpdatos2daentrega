
#ifndef NODOINTERIOR_H_
#define NODOINTERIOR_H_

#include "Nodo.h"

class NodoInterior : public Nodo {

	friend class ArbolBMas;

private:
	int* hijos;

public:
	NodoInterior(int nivel);
	NodoInterior();
	virtual ~NodoInterior();

	CadenaBytes Serializar();
	bool Hidratar(CadenaBytes & cadena);

    int *getHijos() const
    {
        return hijos;
    }
};

#endif /* NODOINTERIOR_H_ */
