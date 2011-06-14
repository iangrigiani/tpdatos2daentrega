/*
 * Peso global: Responde a esta heurística: "La importancia global de un
 * término es grande cuando un término aparece en pocos documentos"
 * pg(ti) = log10 (n / f ti) , donde
 * 		n = el número total de documentos
 * 		f ti = frecuencia global del termino
 * 			(o cantidad de documentos donde aparece el término )
 *TODO Más adelante, poner en documentación...
 */

#include "CalculadorDePesoGlobal.h"
#include <math.h>

CalculadorDePesoGlobal::CalculadorDePesoGlobal(){

	std::fstream off;
	off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
	if ( !off.is_open()){
		off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::out);
		std::string s = "0";
		off.seekg(0, std::ios_base::beg);
		off.write(s.c_str(), s.length());
		off.flush();
		off.close();
		off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
	}
	char buffer[100];
	off.seekg(0, std::ios_base::beg);
	off.get(buffer, 100);
	std::stringstream ss;
	ss << buffer;
	this->cantDeDocs = atoi(ss.str().c_str());
	off.close();
}

CalculadorDePesoGlobal::~CalculadorDePesoGlobal(){
}

float CalculadorDePesoGlobal::calcularPesoGlobalTermino(int frecGlobalTermino){
	float pesoGlobal = 0 ;
	float cociente = 0;
	cociente = (this->cantDeDocs) / frecGlobalTermino;
	pesoGlobal = log10(cociente);
	return pesoGlobal;
}

void CalculadorDePesoGlobal::incrementarCantDeDocs(int diferencial){

	std::fstream off;
	off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
	char buffer[100];
	off.seekg(0, std::ios_base::beg);
	off.get(buffer, 100);
	std::stringstream ss;
	ss << buffer;
	int valor =  atoi(ss.str().c_str());

	valor += diferencial;
	ss.clear();
	ss << valor;

	off.seekg(0, std::ios_base::beg);
	off.write(ss.str().c_str(), ss.str().length());
	off.flush();
	off.close();


//	this->cantDeDocs = cantDeDocs + diferencial;
//	ss << this->cantDeDocs;

}

void CalculadorDePesoGlobal::decrementarCantDeDocs(){

	std::fstream off;
	off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
	char buffer[100];
	off.seekg(0, std::ios_base::beg);
	off.get(buffer, 100);
	std::stringstream ss;
	ss << buffer;
	int valor =  atoi(ss.str().c_str());

	if (valor > 0){

		-- valor;
		ss.clear();
		ss << valor;

		off.seekg(0, std::ios_base::beg);
		off.write(ss.str().c_str(), ss.str().length());
		off.flush();

	}

	off.close();

//	int aux = (this->cantDeDocs);
//	--aux;
//	this->cantDeDocs = aux;
}
