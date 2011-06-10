
#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "../Persistencia/Serializable.h"

class Bloque : public Serializable {

protected:

	int tam_disp;

public:

	Bloque(int tam_disp = 1);
	virtual ~Bloque() {};

	int get_tam_disp() const { return this->tam_disp; }

	void duplicar_tam_disp();
	void truncar_tam_disp();

};

#endif /* BLOQUE_H_ */
