#ifndef PROCESADORPRENORMA_H_
#define PROCESADORPRENORMA_H_

#include <list>
#include "../Handlers/HandlerNormasAInfinito.h"
using namespace std;

class ProcesadorPreNorma  {
public:
	/*----- Constructor y Destructor ------*/
	ProcesadorPreNorma();
	virtual ~ProcesadorPreNorma() {};

	/* Arma la Lista de IDs que se le pasan a HandlerNormasAInfinito
	 * PRE: Recibe el ID de una términos y si no está en la lista de IDs recibidos
	 * 		lo agrega a la misma.
	 * POS: Si el ID no estaba en la lista, devuelve el ID.
	 * 		Si ya estaba en la lista devuelve -1
	 */
	int procesarIDPalabra(int IDPalabra);


	list<int> obtenerListaIDsRecibidos()
		const { return this->listaIDsRecibidos; };

	/* Método que se encarga de pasarle al HandlerNormasAInfinito la orden y la lista
	 * de términos cuyo peso global se debe incrementar.
	 * PRE: -
	 * POS: Archivo de normas a actualizado.
	 */
	void actualizarNormasAInfinito();

private:
	list<int> listaIDsRecibidos;

};
#endif /* PROCESADORPRENORMA_H_ */
