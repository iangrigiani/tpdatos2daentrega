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

	std::string modificacion;
	std::fstream archivoId;
	char  cadenaDeDatos[50];

	archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);

	if (archivoId.is_open()){
		archivoId.seekg(0);
		archivoId.get(cadenaDeDatos,50);
		modificacion = cadenaDeDatos;
//		archivoId.close();
	}else{
		archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::out);
		archivoId.close();
		archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
		modificacion  = "0";
//		archivoId.close();
	}

	std::stringstream ss;
	ss << modificacion;
//	archivoId.open(PATH_ID_TERMINOS, std::ios_base::out);
//	archivoId.close();
//	archivoId.open(PATH_ID_TERMINOS, std::ios_base::in | std::ios_base::out);
	archivoId.clear();
	archivoId.seekg(0);
	archivoId.write(ss.str().c_str(), ss.str().length());
	archivoId.close();

	this->cantDeDocs = atoi(modificacion.c_str());

	//	std::fstream off;
	//	off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
	//	if ( !off.is_open()){
	//		off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::out);
	//		std::stringstream ss;
	//		int p = 0;
	//		ss << p << "\n";
	//		off.seekg(0, std::ios_base::beg);
	//		off.write(ss.str().c_str(), ss.str().length());
	//		off.flush();
	//		off.close();
	//	}
	//
	//	std::ifstream iff;
	//	iff.open(PATH_TOTAL_DOCUMENTOS);
	//	char buffer[100];
	//	iff.seekg(0, std::ios_base::beg);
	//	iff.get(buffer, 100);
	//	std::stringstream ss;
	//	ss << buffer;
	//	iff.close();
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

	std::string modificacion;
	std::fstream archivoId;
	char  cadenaDeDatos[50];

	archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);

	if (archivoId.is_open()){
		archivoId.seekg(0);
		archivoId.get(cadenaDeDatos,50);
		modificacion = cadenaDeDatos;
		archivoId.close();
	}else{
		archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::out);
		archivoId.close();
		archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
		modificacion  = "0";
//		archivoId.close();
	}

	//	cadenaRetorno.setBytes(modificacion);
	int valor = atoi(modificacion.c_str());
	++valor;
	std::stringstream ss;
	ss << valor;
//	archivoId.open(PATH_ID_TERMINOS, std::ios_base::out);
//	archivoId.close();
//	archivoId.open(PATH_ID_TERMINOS, std::ios_base::in | std::ios_base::out);
	archivoId.clear();
	archivoId.seekg(0);
	archivoId.write(ss.str().c_str(), ss.str().length());
	archivoId.flush();
	archivoId.close();
	//	std::ifstream iff;
	//	iff.open(PATH_TOTAL_DOCUMENTOS);
	////	off.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
	//	char buffer[100];
	//	iff.seekg(0, std::ios_base::beg);
	//	iff.get(buffer, 100);
	//	std::stringstream ss;
	//	ss << buffer;
	//	int valor =  atoi(ss.str().c_str());
	//	iff.close();
	//	valor += diferencial;
	//	ss.clear();
	//	ss << valor << "\n";
	//
	//	std::ofstream off;
	//	off.open(PATH_TOTAL_DOCUMENTOS);
	//	off.seekp(0, std::ios_base::beg);
	//	off.clear();
	//	off.seekp(0, std::ios_base::beg);
	//	off.write(ss.str().c_str(), ss.str().length());
	//	off.flush();
	//	off.close();

}

void CalculadorDePesoGlobal::decrementarCantDeDocs(){

	std::string modificacion;
	std::fstream archivoId;
	char  cadenaDeDatos[50];

	archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);

	if (archivoId.is_open()){
		archivoId.seekg(0);
		archivoId.get(cadenaDeDatos,50);
		modificacion = cadenaDeDatos;
		archivoId.close();
	}else{
		archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::out);
		archivoId.close();
		archivoId.open(PATH_TOTAL_DOCUMENTOS, std::ios_base::in | std::ios_base::out);
		modificacion  = "0";
		archivoId.close();
	}

	//	cadenaRetorno.setBytes(modificacion);
	int valor = atoi(modificacion.c_str());
	if (valor > 0){
		--valor;
		std::stringstream ss;
		ss << valor;
//		archivoId.open(PATH_ID_TERMINOS, std::ios_base::out);
//		archivoId.close();
		archivoId.open(PATH_ID_TERMINOS, std::ios_base::in | std::ios_base::out);
		archivoId.clear();
		archivoId.seekg(0);
		archivoId.write(ss.str().c_str(), ss.str().length());
		archivoId.flush();
		archivoId.close();
	}
	//	std::ifstream iff;
	//	iff.open(PATH_TOTAL_DOCUMENTOS);//, std::ios_base::in | std::ios_base::out);
	//	char buffer[100];
	//	iff.seekg(0, std::ios_base::beg);
	//	iff.get(buffer, 100);
	//	std::stringstream ss;
	//	ss << buffer;
	//	int valor =  atoi(ss.str().c_str());
	//	iff.close();
	//
	//
	//	if (valor > 0){
	//		std::ofstream off;
	//		off.open(PATH_TOTAL_DOCUMENTOS);//, std::ios_base::in | std::ios_base::out);
	//
	//		-- valor;
	//		ss.clear();
	//		ss << valor << "\n";
	//
	//		off.seekp(0, std::ios_base::beg);
	//		off.clear();
	//		off.seekp(0, std::ios_base::beg);
	//		off.write(ss.str().c_str(), ss.str().length());
	//		off.flush();
	//		off.close();
	//
	//	}


	//	int aux = (this->cantDeDocs);
	//	--aux;
	//	this->cantDeDocs = aux;
}
