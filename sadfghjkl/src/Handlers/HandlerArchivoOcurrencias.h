
#ifndef HANDLERARCHIVOOCURRENCIAS_H_
#define HANDLERARCHIVOOCURRENCIAS_H_


#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Comunes/Ocurrencia.h"
#include "../Comunes/Constantes.h"
#include "../Gamma/CodigoGamma.h"
#include "../Comunes/Palabra.h"
#include "../Comunes/Aparicion.h"

class HandlerArchivoOcurrencias{

private:

			int offsetAAEL; // Offset al archivo de espacios libres

			void crearArchivoVacio();

			int buscarOffsetArchivoEspaciosLibres(int tamanioOcurrencia);

			int obtenerTamanioMaestro();

			int obtenerTamanioOcurrencia(Ocurrencia ocurrencia);

			void procesarCadenaDeDatos(char * cadena, Ocurrencia& ocurrencia);

			void actualizarEspaciosLibres(int offset,int espacioLibre);

			void borrarOffsetArchivoDeEspaciosLibres();


public:

		HandlerArchivoOcurrencias();

		virtual ~HandlerArchivoOcurrencias(){}

		/*
		 * Metodo que inserta una ocurrencia en el
		 * archivo de ocurrencias posicional de terminos.
		 */
		int insertarOcurrencia(Ocurrencia ocurrencia,int idDocumento);


		/*
		 * Metodo que busca una ocurrencia en el archivo de ocurrencias.
		 */
		Ocurrencia buscarOcurrencia(int offset);


		/*
		 * Metodo que elimina una ocurrencia del archivo de ocurrencias.
		 */
		void eliminarOcurrencia(int offset);

		/*
		 * Método que obtiene la lista de documentos para un termino.
		 * pre: recibe la lista de offset al archivo de ocurrencias donde aparece ese termino.
		 * post: devuelve la lista de documentos
		 */
		list<int> obtenerListaDocumentos(list<int>);


		/*
		 * Método que obtiene palabra correspondientes a un termino
		 * pre: recibe la lista de offset al archivo de ocurrencias donde aparece ese termino.
		 * post: devuelve palabra.
		 */
		Palabra obtenerPalabra(list<int> offsets, string nombrePalabra);
};

#endif /* HANDLERARCHIVOOCURRENCIAS_H_ */
