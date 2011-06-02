#ifndef REGISTRO_H_
#define REGISTRO_H_
#include "Clave.h"
#include <string>
using namespace std;
using std::string;

class Elementos : public Serializable {

private:
	Clave* clave;
	CadenaBytes* datos;
	CadenaBytes* ID;
public:
	/*
	 * Constructor vacio
	 */
	Elementos();

	/*
	 * Constructor
	 */
	Elementos(Clave* clave, CadenaBytes* datos, CadenaBytes* ID);

	/*
	 * Clone
	 */
	Elementos* Clonar();

	/*
	 * Serializar
	 */
	CadenaBytes Serializar();

	/*
	 * Metodo que hidrata un registro.
	 * Pre: la cadena debe representar a un registro
	 * Pos: queda hidratado el registro
	 */
	bool Hidratar(CadenaBytes &cadena);

	/*
	 * Getters y setters
	 */
	Clave *getClave() const;
    CadenaBytes* getDatos() const;

    /* El getTamanio calcula la suma de los sizeof de:
     * 		datos
     * 		clave
     * 		int
     */
    int getTamanio() const;
    CadenaBytes* getID();
    void setClave(Clave *clave);
    void setDatos(CadenaBytes* datos);
	void setID (CadenaBytes* id);
    string toString();

	/*
	 * Destructor
	 * Pos: libera la memoria de clave y de los datos
	 * 		si estos existian.
	 */
	virtual ~Elementos();

};

#endif /* REGISTRO_H_ */
