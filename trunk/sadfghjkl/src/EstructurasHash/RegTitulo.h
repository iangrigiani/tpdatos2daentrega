
#ifndef REGTITULO_H_
#define REGTITULO_H_

#include <fstream>
#include <stdio.h>
#include <string>
#include "Reg.h"

using namespace std;

class RegTitulo : public Reg {

private:

	int offset;

public:

	RegTitulo() : Reg(), offset(-1) {}
	RegTitulo(int clave, int offset) : Reg(clave), offset(offset) {}
	virtual ~RegTitulo() {};

	int get_tam() const;

	int get_clave() const { return this->clave; }
	int get_offset() const { return this->offset; }

	void serializar(char* buffer, unsigned int& offset);
	void hidratar(char* buffer, unsigned int& offset);

	void toString(ofstream& fo);

};

#endif /* REGTITULO_H_ */
