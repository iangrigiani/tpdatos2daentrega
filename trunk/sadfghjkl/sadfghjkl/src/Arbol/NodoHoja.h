
#ifndef NODOHOJA_H_
#define NODOHOJA_H_

#include "Nodo.h"

class NodoHoja : public Nodo {

	friend class ArbolBMas;
	friend class IteradorArbolBMas;

private:
	int hojaSiguiente;
	Persistencia* datos;
	Persistencia* Ids;

public:
	NodoHoja();
	virtual ~NodoHoja();

	Persistencia Serializar();
	bool Hidratar(Persistencia & cadena);

    Persistencia *getDatos() const
    {
        return datos;
    }

    int getHojaSiguiente() const
    {
        return hojaSiguiente;
    }

    Persistencia *getIds(){
    	return Ids;
    }

    NodoHoja* Clonar();
};

#endif /* NODOHOJA_H_ */
