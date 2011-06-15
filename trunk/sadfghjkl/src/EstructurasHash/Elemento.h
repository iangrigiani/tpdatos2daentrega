
#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include <list>
#include "../Persistencia/Serializable.h"

class Elemento : public Serializable {

private:

	string termino;
	int ID;

public:

	Elemento();
	Elemento(const string& termino, int ID);
	virtual ~Elemento() {};

	void set_termino(const string& termino);
	void set_ID(int ID);

	const string& get_termino() const { return this->termino; }
	int get_ID() const { return this->ID; }

	int get_tam();

	Persistencia Serializar();
	bool Hidratar(Persistencia& cadena);

	void toString(ostream& os);

};

#endif /* ELEMENTO_H_ */
