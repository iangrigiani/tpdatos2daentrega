
#include "Elementos.h"
//#include "Utilitarios.h"

Elementos::Elementos()
{
	/* La clave se incializa vacia, por lo que luego
	 * habra que aditar su valor.
	 */
	this->clave = new Clave("");
	this->datos = new Persistencia;
	this->ID = new Persistencia;
}

Elementos::Elementos(Clave* clave, Persistencia* datos, Persistencia* id)
{
	this->clave = clave;
	this->datos = datos;
	this->ID = id;
}


Persistencia Elementos::Serializar()
{
	Persistencia cadena;
	int tamanio = getTamanio();
	cadena.agregarAlFinal(&tamanio,sizeof(int));
	cadena.agregarAlFinal(clave->Serializar());
	cadena.agregarAlFinal(*datos);
	cadena.agregarAlFinal(*ID);
	return cadena;
}


bool Elementos::Hidratar(Persistencia &cadena){
	bool exito;
	//el tamaño debe ser al menos el tamaño de la longitud del registro y la clave
	if (cadena.getTamanio() < (TAM_LONG_REGISTRO + TAM_LONG_CLAVE))  {
		exito = false;
	}else{
		if (this->datos) {
			delete (this->datos);
			this->datos = new Persistencia;
		}
		int tamanioRegistro = cadena.leerEntero(0);
		char tamanioClave;
		cadena.leer(&tamanioClave,TAM_LONG_REGISTRO,TAM_LONG_CLAVE);
		Persistencia cadenaClave = cadena.leer(TAM_LONG_REGISTRO,TAM_LONG_CLAVE + int(tamanioClave));
		this->clave->Hidratar(cadenaClave);
		unsigned int posicionComienzoDatos = (TAM_LONG_REGISTRO + TAM_LONG_CLAVE + int(tamanioClave));
		this->datos->agregarAlFinal(cadena.leer(posicionComienzoDatos,tamanioRegistro - posicionComienzoDatos));
		unsigned int posicionComienzoID = (TAM_LONG_REGISTRO + TAM_LONG_CLAVE + int(tamanioClave) + datos->getTamanio());
		this->ID->agregarAlFinal(cadena.leer(posicionComienzoID,tamanioRegistro - posicionComienzoID));
		exito = true;
	}
	return exito;
}


Elementos* Elementos::Clonar()
{
	return new Elementos(clave->Clonar(),new Persistencia(*datos), new Persistencia(*ID));
}

Persistencia* Elementos::getID(){
	return this->ID;
}
void Elementos::setID (Persistencia* id){
	this->ID = id;
}
/*
 * Getters y setters
 */
Clave *Elementos::getClave() const
{
    return clave;
}

Persistencia* Elementos::getDatos() const
{
    return datos;
}

int Elementos::getTamanio() const
{
    return (TAM_LONG_CLAVE + TAM_LONG_REGISTRO + clave->getTamanio() + datos->getTamanio() + ID->getTamanio());
}

void Elementos::setClave(Clave *clave)
{
	if(this->clave) delete this->clave;
    this->clave = clave;
}

void Elementos::setDatos(Persistencia* datos)
{
	if (this->datos) delete (this->datos);
    this->datos = datos;
}


/*
 * Destructor
 */
Elementos::~Elementos() {

	if (this->clave) delete (this->clave);
	if (this->datos) delete (this->datos);
	if (this->ID) delete (this->ID);
}

string Elementos::toString(){
	string cadena;
	cadena += "Clave: ";
	cadena += clave->toString();
	cadena += " | ";
	cadena += "Dato : ";
	cadena += datos->toString();
	cadena += " | ";
	cadena += "Id de Elemento: ";
	cadena += ID->toString();
	return cadena;
}

