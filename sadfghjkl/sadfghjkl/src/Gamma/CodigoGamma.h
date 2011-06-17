#ifndef CODIGOGAMMA_H_
#define CODIGOGAMMA_H_
#include <string>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <list>

class CodigoGamma {

private:
	int numAConvertir;
	/*
	 * Método que me forma la primer parte de la conversion correspondiente al unario
	 * pre: -
	 * pos: Obtengo en un string el unario correspondiente
	 */
	std::string obtenerUnario(int numAConvertir);
	/*
	 * Método que me forma la segunda parte de la conversion correspondiente al binario
	 * pre: -
	 * pos: Obtengo en un string el binario correspondiente
	 */
	std::string conversionRepresentacion(int numAConvertir);

	/*
	 * Método que me pasa a binario un numero en "cantidadBits" de  bits
	 * pre: -
	 * pos: Obtengo en un string el binario correspondiente
	 */
	std::string obtenerBinarioDeNBits(int valorConversion, int cantidadBits);

	/*
	 * Método que me pasa un binario a un numero entero
	 * pre: -
	 * pos: Obtengo el entero correspondiente al binario pasado por parametro
	 */
	int interpretarBinario(std::string binarioAInterpretar);
public:
/*------------ Constructores y destructor --------------*/
	CodigoGamma();
	CodigoGamma(int numeroAConvertir);
	virtual ~CodigoGamma();

/*-----Método de conversion y de interpretacion Gamma-----*/
	/*
	 * Metodo que realiza la compresión a Gamma
	 * pre:-
	 * pos: Conversion realizada y devuelta en un string
	 */
	std::string aplicarConversion();

	/*
	 * Metodo que realiza la conversion de Gamma a un numero
	 * pre: Le paso una conversion hecha en gamma
	 * pos: Obtengo el numero que representa esa conversion
	 */
	int interpretarConversion(std::string conversion);

	/*
	 * Metodo que realiza la compresion de una lista en codigos gamma
	 * pre: Le paso la lista a comprimir
	 * pos: Obtengo la tira de bits en un string
	 */
	std::string comprimirLista(std::list<int> listaInvertida, int primero);
/*------------ GETTERS AND SETTERS --------------*/
	void setNumAConvertir (int num){
		this->numAConvertir = num;
	}
	int getNumAConvertir() const{
		return this->numAConvertir;
	}

};

#endif /* CODIGOGAMMA_H_ */
