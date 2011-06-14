#ifndef CALCULADORDEPESOGLOBAL_H_
#define CALCULADORDEPESOGLOBAL_H_

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "../Comunes/Constantes.h"

class CalculadorDePesoGlobal{
private:
	int cantDeDocs;

public:
	CalculadorDePesoGlobal();
	~CalculadorDePesoGlobal();

	void incrementarCantDeDocs(int diferencial);
	float calcularPesoGlobalTermino(int frecGlobalTermino);
	void decrementarCantDeDocs();

};


#endif /* CALCULADORDEPESOGLOBAL_H_ */
