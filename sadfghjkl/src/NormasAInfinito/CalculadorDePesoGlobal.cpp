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
	this->cantDeDocs = cantDeDocs + diferencial;
}

void CalculadorDePesoGlobal::decrementarCantDeDocs(){
	int aux = (this->cantDeDocs);
	--aux;
	this->cantDeDocs = aux;
}
