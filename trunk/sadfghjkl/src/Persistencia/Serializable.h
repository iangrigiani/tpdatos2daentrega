#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include "Persistencia.h"

class Serializable{

public:
	/*
	 * Metodo que deberan implementar las clases descendietes
	 * Pre:-
	 * Pos: Se retorna un puntero a un elemento CadenaBytes que representa a el objeto
	 */
	virtual Persistencia Serializar()=0;

	/*
	 * Metodo que deberan implementar las clases descendientes
	 * Pre: la cadena de bytes debe ser una representacion del objetod
	 * Pos: El objeto queda creado segun los parametros de la cadena de bytes
	 */
	virtual bool Hidratar(Persistencia &cadena)=0;
};

#endif /* SERIALIZABLE_H_ */
