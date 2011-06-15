#ifndef PERSISTENCIA_H_
#define PERSISTENCIA_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include "../EstructurasArbol/FrontCoding.h"

using namespace std;

class Persistencia {
private:

	string bytes;
	bool estaTransformada(string cadena);
public:
	/*
	 * Constructor
	 */
	Persistencia();

	/*
	 * Constructor que crea una nueva instancia con los bytes del objeto pasado por argumento.
	 */
	Persistencia(const Persistencia &cadDeBytes);

	/*
	 * Constructor que se crea con un string
	 */
	Persistencia (string bytes);

	/*
	 * Destructor
	 */
	virtual ~Persistencia();

	/*
	 * Metodo que dice si el objeto no tiene ningun byte
	 * Pre:
	 * Pos: Si esta vacia devuelve TRUE, y sino, FALSE
	 */
	bool estaVacia() const;

	/*
	 * Metodo que devuelve un string con los datos almacenados en el objeto
	 * Pre:
	 * Pos: string con los datos.
	 */
	string toString() const;


	/*
	 * Metodo que sirve para agregar los bytes en una posicion especifica (pasada por argumento)
	 * Pre: La posicion debe ser valida
	 * Pos: Devuelve TRUE si pudo agregar los bytes en la posicion requerida,
	 * 		de lo contrario devuelve FALSE.
	 */
	bool agregar(const Persistencia& bytes,unsigned int posicion);

	/*
	 * Metodo que agrega los bytes del string en una posicion especifica (pasada por argumento)
	 * Pre: La posicion debe ser valida
	 * Pos: Devuelve TRUE si pudo agregar los bytes en la posicion requerida,
	 * 		de lo contrario devuelve FALSE.
	 */
	bool agregar(const string& bytes,unsigned int posicion);

	/*
	 * Metodo que agrega el valor convertido a bytes en la posicion indicada
	 * Pre: El tamanio y la posicion deben ser validas.
	 * Pos: Devuelve TRUE si lo pudo agregar correctamente y FALSE en
	 *      caso contrario.
	 */
	bool agregar(void* valor, unsigned int tamanio, unsigned int posicion);

	/*
	 * Metodo que agrega los bytes al final de los bytes ya almacenados
	 * Pre:
	 * Pos: Devuelve TRUE si pudo agregar los bytes al final,
	 * 		de lo contrario devuelve FALSE.
	 */
	bool agregarAlFinal(const string& bytes);

	/*
	 * Metodo que agrega los bytes al final de los bytes ya almacenados
	 * Pre:
	 * Pos: Devuelve TRUE si pudo agregar los bytes al final,
	 * 		de lo contrario devuelve FALSE.
	 */
	bool agregarAlFinal(const Persistencia& bytes);

	/*
	 * Metodo que agrega el valor convertido a bytes al final de la cadena.
	 * Pre:
	 * Pos: Devuelve TRUE si lo pudo agregar, y FALSE en caso contrario
	 */
	bool agregarAlFinal(void* valor, int tamanio);

	/*
	 * Metodo que sirve para reemplazar el contenido de la cadena.
	 * Pre:
	 * Pos: Devuelve TRUE si pudo reemplazar el contenido, de lo contrario
	 *      devuelve FALSE.
	 */
	bool reemplazar(const string &bytes, unsigned int posicion);

	/*
	 * Metodo que sirve para reemplazar el contenido de la cadena.
	 * Pre:
	 * Pos: Devuelve TRUE si pudo reemplazar el contenido, de lo contrario
	 *      devuelve FALSE.
	 */
	bool reemplazar(const Persistencia &cadDeBytes, unsigned int posicion);

	/*
	 * Pre: Argumentos validos.
	 * Pos: remueve los bytes indicados.
	 */
	bool eliminar(unsigned int inicio,unsigned int fin);

	/*
	 * Metodo que sirve para leer una cadena de bytes y guardarla en un buffer
	 * Pre: El buffer debe ser valido.
	 * Pos: Guarda en el buffer (char*) los bytes leidos. Devuelve TRUE si lo
	 *      pudo devolver, de lo contrario FALSE (y el buffer no se modifica)
	 */
	bool leer(char* buffer, unsigned int inicio,unsigned int tamanio)const;

	/*
	 * Metodo que sirve para crear una instancia de "CadenaBytes" con los bytes
	 * pasados por parametro.
	 * Pre:
	 * Pos: Devuelve la instancia indicada con el contenido desde inicio
	 *      hasta inicio + tamanio. Si estos 2 valores no son validos,
	 *      devuelve el contenido de la instancia vacia.
	 */
	Persistencia leer(unsigned int inicio, unsigned int tamanio) const;

	/*
	 * Metodo que sirve para leer una serie de bytes dados por el tamaño de un entero
	 * y devolverlo en dicho formato.
	 * Pre: la cadena debe tener al menos una cantidad de bytes de al menos "sizeof(int)"
	 * 		luego del parametro "inicio". Si no se respeta el entero retornado sera -1.
	 * Pos: retorna el valor entero
	 */
	int leerEntero(unsigned int inicio);

	/*
	 * Metodo que vacia el contenido almacenado
	 * Pre:
	 * Pos: Devuelve TRUE si pudo vaciarlo, de lo contrario FALSE.
	 */
	bool vaciar();
	void transformarAFrontCoding(string primera, string ruta);
	void sacarElFrontCoding(string palabra, string ruta);
	/*
	 * Getters y setters
	 */
	unsigned int getTamanio() const;

	void setBytes(const string &bytes);


};

#endif /* PERSISTENCIA_H_ */
