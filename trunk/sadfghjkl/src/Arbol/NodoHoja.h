
#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"

class NodoHoja : public Nodo {

	friend class ArbolBMas;
	friend class IteradorArbolBMas;

private:
	int hojaSiguiente;
	CadenaBytes* datos;
	CadenaBytes* Ids;

public:
	NodoHoja();
	virtual ~NodoHoja();

	CadenaBytes Serializar();
	bool Hidratar(CadenaBytes & cadena);

    CadenaBytes *getDatos() const
    {
        return datos;
    }

    int getHojaSiguiente() const
    {
        return hojaSiguiente;
    }

    CadenaBytes *getIds(){
    	return Ids;
    }

    NodoHoja* Clonar();
};

#endif /* NODOHOJA_H_ */
