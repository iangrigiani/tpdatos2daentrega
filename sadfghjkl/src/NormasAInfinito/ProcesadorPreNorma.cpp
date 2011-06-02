#include "ProcesadorPreNorma.h"
#include "HandlerNormasAInfinito.h"

ProcesadorPreNorma::ProcesadorPreNorma(){
}


int ProcesadorPreNorma::procesarIDPalabra(int IDPalabra){
	list<int>::iterator it = this->listaIDsRecibidos.begin();
	while ( it != this->listaIDsRecibidos.end()){
		if( (*it) != IDPalabra){
			this->listaIDsRecibidos.push_back(IDPalabra);
			return IDPalabra;
		}
	}
	return -1;
}

/*No sé si eso queda bien ahí.. por ahora ahí se queda*/
void ProcesadorPreNorma::actualizarNormasAInfinito(){
	HandlerNormasAInfinito* aNormas = new HandlerNormasAInfinito();
	aNormas->actualizarPesosTerminos(this->listaIDsRecibidos);
	delete aNormas;
}
