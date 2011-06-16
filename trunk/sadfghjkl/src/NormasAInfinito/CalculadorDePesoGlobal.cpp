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

void CalculadorDePesoGlobal::consultar_archivo() {
	ifstream arch;

	arch.open(PATH_TOTAL_DOCUMENTOS);
	string s;
	getline(arch, s);
	arch.close();

	stringstream ss;
	ss << s;
	ss >> this->cantDeDocs;
}

CalculadorDePesoGlobal::CalculadorDePesoGlobal() {
	fstream arch;

	arch.open(PATH_TOTAL_DOCUMENTOS, fstream::app);
	if (arch.tellg() == 0) {
		arch.close();

		arch.open(PATH_TOTAL_DOCUMENTOS, fstream::out);
		arch << "0";
		arch.close();

		this->cantDeDocs = 0;
	}
	else {
		arch.close();

		this->consultar_archivo();
	}
}

float CalculadorDePesoGlobal::calcularPesoGlobalTermino(int frecGlobalTermino) {
	float pesoGlobal = 0;
	float cociente = 0;
	cociente = (this->cantDeDocs) / frecGlobalTermino;
	pesoGlobal = log10(cociente);
	return pesoGlobal;
}

void CalculadorDePesoGlobal::incrementarCantDeDocs() {
	fstream arch;

	arch.open(PATH_TOTAL_DOCUMENTOS, fstream::app);
	if (arch.tellg() == 0) {
		arch.close();

		this->cantDeDocs = 1;
	}
	else {
		arch.close();

		this->consultar_archivo();
		++ this->cantDeDocs;
	}

	arch.open(PATH_TOTAL_DOCUMENTOS, fstream::in | fstream::out);
	arch << this->cantDeDocs << endl;
	arch.close();
}

bool CalculadorDePesoGlobal::decrementarCantDeDocs() {
	fstream arch;

	arch.open(PATH_TOTAL_DOCUMENTOS, fstream::app);
	if (arch.tellg() == 0) {
		arch.close();

		this->cantDeDocs = 0;
		return ERROR;
	}
	else {
		arch.close();

		this->consultar_archivo();

		if (this->cantDeDocs > 0)
			-- this->cantDeDocs;
		else return ERROR;
	}

	arch.open(PATH_TOTAL_DOCUMENTOS, fstream::in | fstream::out);
	arch << this->cantDeDocs << endl;
	arch.close();
	return OKEY;
}
