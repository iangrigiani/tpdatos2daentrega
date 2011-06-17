
#ifndef CLAVE_H_
#define CLAVE_H_
#include "../Persistencia/Serializable.h"
#include "../Comunes/Constantes.h"
#include <string.h>

class Clave : public Serializable{

private:
	/*
	 * La clave debera ser un string
	 */
	string clave;

public:

	/*
	 * Constructor vacio
	 */
	Clave();

	/*
	 * Constructor
	 */
	Clave(string clave);

	/*
	 * Metodo que devuelve un string con los datos almacenados en el objeto (clave)
	 * Pre:
	 * Pos: string con los datos.
	 */
	string toString() const;

	/*
	 * Metodo que serializa la clave.
	 * Se utiliza 1 char para representar el tamaño de la clave (0 a 255)
	 * El resto de los bytes representan la propia clave.
	 */
	Persistencia Serializar();

	/*
	 * Metodo que hidrata la clave (heredado de Serializable)
	 * Pre: la cadena de tipo CadenaBytes que se pasa por parametro, tiene que tener
	 * 		al menos el tamanio de un char, utilizado para representar el tamaño de la clave.
	 * Pos: Devuelve TRUE si pudo hidratar correctamente la cadena y la guarda
	 * 		en el atributo clave. Si la cadena tiene una longitud invalida devuelve FALSE.
	 */
	bool Hidratar(Persistencia &cadena);

	/*
	 * Metodo que clona a la clave
	 * Pre:-
	 * Pos: Se retorna un puntero a un objeto de tipo clave, cuya memoria es alocada dinamicamente,
	 * 		con los mismos valores que el actual.
	 */
	Clave* Clonar();

//	 Getters y setters.
	/*
	 * Metodo que retorna el tamaño de la representacion de la clave
	 * en bytes
	 */
	int getTamanio();
	string getClave() const;
	void setClave(string clave);

	/*
	 * Destructor:
	 * Pos: libera la memoria de clave.
	 */
	virtual ~Clave();

	bool operator != (const Clave& otra) const;

	bool operator == (const Clave& otra) const;

	bool operator < (const Clave& otra) const;

	bool operator > (const Clave& otra) const;

	bool operator <= (const Clave& otra) const;
};

#endif /* CLAVE_H_ */
