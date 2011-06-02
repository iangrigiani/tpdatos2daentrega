#ifndef NODO_H_
#define NODO_H_

#include "../EstructurasEnComun/Clave.h"

class Nodo{
	friend class ArbolBMas;
	friend class NodoInterior;
	friend class NodoHoja;
	friend class IteradorArbolBMas;

private:
	int numero;
	int nivel;
	int espacioOcupado;
	int cantidadClaves;
	Clave* claves;

public:
	Nodo(int nivel);
	virtual ~Nodo();

	bool isNodoHoja();
	bool isOverflow(int);
	bool isUnderflow();
	bool puedeCederElementos();

	CadenaBytes Serializar();
	bool Hidratar(CadenaBytes & cadena);

    int getCantidadClaves() const
    {
        return cantidadClaves;
    }

    Clave *getClaves() const
    {
        return claves;
    }

    int getEspacioOcupado() const
    {
        return espacioOcupado;
    }

    int getNivel() const
    {
        return nivel;
    }

    int getNumero() const
    {
        return numero;
    }

    void setNumero(int numero) {
    	this->numero = numero;
    }

};

#endif /* NODO_H_ */
