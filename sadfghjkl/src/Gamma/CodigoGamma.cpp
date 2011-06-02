#include "CodigoGamma.h"

CodigoGamma::CodigoGamma() {
	this->numAConvertir = 0;
}
CodigoGamma::CodigoGamma(int numeroAConvertir){
	this->numAConvertir = numeroAConvertir;
}
CodigoGamma::~CodigoGamma() {
}

std::string CodigoGamma::aplicarConversion(){

	std::string retorno;
	retorno.clear();
	// Obtengo primera parte del numero
	std::string unario = obtenerUnario(this->numAConvertir);
	// Obtengo segunda parte del numero
	std::string representacionBinaria = conversionRepresentacion(this->numAConvertir);

	// Obtengo la conversion en Gamma
	retorno = unario + representacionBinaria;
	return retorno;

}

std::string CodigoGamma::obtenerUnario(int numAConvertir){

	std::string retorno;
	std::stringstream ss;
	retorno.clear();
	// Obtengo el logaritmo en base 10 del numero
	double logaritmo = (log10(numAConvertir) / log10(2));
	// Le aplico la funcion piso
	int valor = (int)floor(logaritmo);
	// Le sumo 1
	++valor;

	// Hago el unario
	for (int i = valor; i > 0 ; --i)
		ss << "1";
	ss << "0";

	retorno = ss.str();
	return retorno;
}

std::string CodigoGamma::conversionRepresentacion(int numAConvertir){

	std::string retorno;
	retorno.clear();
	// Obtengo el logaritmo en base 10 del numero
	double logaritmo = (log10(numAConvertir) / log10(2));
	// Le aplico la funcion piso
	int cantidadBits = (int)floor(logaritmo);

	// Obtengo la expresion a convertir en binario en "cantidadBits" de bits
	int valorConversion = numAConvertir - (int)pow(2,cantidadBits);

	retorno = obtenerBinarioDeNBits(valorConversion, cantidadBits);
	return retorno;
}

std::string CodigoGamma::obtenerBinarioDeNBits(int valorConversion, int cantidadBits){

	std::stringstream ss;
	ss.clear();
	int i,j,num2,res;
	int * x = new int[cantidadBits+1];

	num2 = valorConversion;

	for (int i = 1; i <= cantidadBits ; i++)
		x[i] = 0;

	switch (valorConversion) {
	case 0:
		break;
	case 1:
		x[1] = 1;
		break;
	default:
		for(i = 1 ; i <= valorConversion ; i++){
			// Determina (i) las divisiones que se harán
			num2 = num2 / 2;
			if(num2 == 1)
				break;
		}

		x[i+1] = 1;
		for(j = 1 ; j <= i; j++){
			// Realiza las operaciones para la conversión
			res = valorConversion % 2;
			if(res == 1)
				x[j] = 1;
			else if(res == 0)
				x[j] = 0;
			valorConversion = valorConversion / 2;
		}
		break;
	}

	// obtengo el valor final
	for(j = cantidadBits ; j > 0 ; j--)
		ss << x[j];

	delete x;
	return (ss.str());
}

int CodigoGamma::interpretarConversion(std::string conversion){
	bool cero = false;
	std::string uno = "1";
	std::string binarioAInterpretar;
	std::stringstream ss;
	int numeroUnario = 0;
	int retorno = 0;

	// Leo el primer numero en unario
	for (int i = 0 ; ((unsigned int)i < conversion.length()) && (!cero); ++i){
		if (conversion[i] == uno[0]){
			++numeroUnario;
		}else{
			cero = true;
		}
	}

	// Leo la segunda parte que esta en binario
	ss.clear();
	binarioAInterpretar.clear();
	for (int i = numeroUnario+1; (unsigned int)i < conversion.length(); ++i){
		ss << conversion[i];
	}
	binarioAInterpretar = ss.str();

	// obtengo el numero interpretado
	retorno = (int)pow(2,(numeroUnario-1)) + interpretarBinario(binarioAInterpretar);

	return retorno;
}

int CodigoGamma::interpretarBinario(std::string binarioAInterpretar){
	int retorno;
	long binario,p,c;
	binario = atoi(binarioAInterpretar.c_str());
	c=1;
	retorno=0;
	while(binario>0){
		p=0;
		p=c*(binario%10);
		retorno+=p;
		c*=2;
		binario/=10;
	}

	return retorno;
}

std::string CodigoGamma::comprimirLista(std::list<int> listaInvertida, int primero){
	std::list<int>::iterator it = listaInvertida.begin();
	int aux = primero;
//	this->numAConvertir = primero;
	std::stringstream ss;
//	ss << this->aplicarConversion();
//	++it;
	while ( it != listaInvertida.end()){
		if ((*it) <=  primero){
			primero = primero -(*it);
		}else{
			primero = (*it) - primero;
		}
		this->numAConvertir = primero;
		ss << this->aplicarConversion();
		++it;
		primero = aux;
	}
	return (ss.str());
}
