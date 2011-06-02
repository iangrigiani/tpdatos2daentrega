#ifndef OCURRENCIA_H_
#define OCURRENCIA_H_

#include <list>
#include <string>
using namespace std;

class Ocurrencia{

private:
		string palabra;
		int idPalabra;
		int idDocumento;
		list <int> posiciones;

public:

		Ocurrencia();
		~Ocurrencia(){}
		int getIdPalabra();
		void setIdPalabra(int idPalabra);
		string getPalabra();
		void setPalabra(string palabra);
		int getIdDocumento();
		void setIdDocumento(int idDocumento);
		list<int> getPosiciones();
		void setPosiciones(list<int>  posiciones);
		void agregarPosicion(int  posicion);
		void agregarPosiciones(list < int > & posiciones);


};

#endif /* APARICION_H_ */
