
#include "Elementos.h"
//#include "Utilitarios.h"

Elementos::Elementos()
{
	/* La clave se incializa vacia, por lo que luego
	 * habra que aditar su valor.
	 */
	this->clave = new Clave("");
	this->datos = new CadenaBytes;
	this->ID = new CadenaBytes;
}

Elementos::Elementos(Clave* clave, CadenaBytes* datos, CadenaBytes* id)
{
	this->clave = clave;
	this->datos = datos;
	this->ID = id;
}


CadenaBytes Elementos::Serializar()
{
	CadenaBytes cadena;
	int tamanio = getTamanio();
	cadena.agregarAlFinal(&tamanio,sizeof(int));
	cadena.agregarAlFinal(clave->Serializar());
	cadena.agregarAlFinal(*datos);
	cadena.agregarAlFinal(*ID);
	return cadena;
}


bool Elementos::Hidratar(CadenaBytes &cadena){
	bool exito;
	//el tamaño debe ser al menos el tamaño de la longitud del registro y la clave
	if (cadena.getTamanio() < (TAM_LONG_REGISTRO + TAM_LONG_CLAVE))  {
		exito = false;
	}else{
		if (this->datos) {
			delete (this->datos);
			this->datos = new CadenaBytes;
		}
		int tamanioRegistro = cadena.leerEntero(0);
		char tamanioClave;
		cadena.leer(&tamanioClave,TAM_LONG_REGISTRO,TAM_LONG_CLAVE);
		CadenaBytes cadenaClave = cadena.leer(TAM_LONG_REGISTRO,TAM_LONG_CLAVE + int(tamanioClave));
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
	return new Elementos(clave->Clonar(),new CadenaBytes(*datos), new CadenaBytes(*ID));
}

CadenaBytes* Elementos::getID(){
	return this->ID;
}
void Elementos::setID (CadenaBytes* id){
	this->ID = id;
}
/*
 * Getters y setters
 */
Clave *Elementos::getClave() const
{
    return clave;
}

CadenaBytes* Elementos::getDatos() const
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

void Elementos::setDatos(CadenaBytes* datos)
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
	cadena += clave->toString();
	cadena += " | ";
	cadena += datos->toString();
	return cadena;
}

