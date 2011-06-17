#ifndef CALCULADORDEPESOGLOBAL_H_
#define CALCULADORDEPESOGLOBAL_H_

#include <fstream>
#include <sstream>
#include <math.h>

#include "../Comunes/Constantes.h"

using namespace std;

class CalculadorDePesoGlobal {
private:
	int cantDeDocs;
	void consultar_archivo();
public:
	CalculadorDePesoGlobal();
	~CalculadorDePesoGlobal() {};

	void incrementarCantDeDocs();
	float calcularPesoGlobalTermino(int frecGlobalTermino);
	bool decrementarCantDeDocs();

};


#endif /* CALCULADORDEPESOGLOBAL_H_ */
