#include "Handlers//HandlerComandos.h"
#include "Procesadores/ProcesadorConsulta.h"
#include "Comunes/Aparicion.h"
#include "Comunes/Palabra.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <unistd.h>

using namespace std;

int main (int argc , char *argv[]){

	/* TODO cambiar printfs por métodos de HandlerComandos*/
	HandlerComandos* handlerComandos = new HandlerComandos();
	string path;

	int opcion1, opcion2;
	if ((argc!= 2) && (argc!=3) ) {
		stringstream ss;
		for ( int i = 2 ; i < argc; ++i){
			if (i == (argc - 1)){
				ss << argv[i];
			}else{
				ss << argv[i] << " ";
			}
		}
		path = ss.str();
		//    	printf("Bookerio: Cantidad errónea de parámetros. Sólo puede pasar un parámetro o ");
		//        printf("dos en caso de -v(er) o de -i(ngresar). \n");
		//        printf("Bookerio: Ingrese el parámetro -h(elp) para ver la referencia de parámetros. \n");
	}else{
		if (argv[2])
			path = argv[2];
	}
	(opcion1 = getopt(argc,argv, "ieatploqvhwxyz?:")) ;
	switch ( opcion1 ) {
	case 'i':   {
		if (argv[2]) {
			handlerComandos->guardarLibroEnArchivoMaestro(path);
			printf("Bookerio: Libro guardado. \n");
		}else{
			printf("Bookerio: No se puede procesar la orden: falta ruta de archivo.\n");}
		break;}

	case 'e':   {
		printf("Bookerio: Indexando por Editorial los libros agregados recientemente \n");
		handlerComandos->indexar('e');
		printf("Bookerio: Fin de indexado por Editorial.\n");
		break;}

	case 'a':   {
		printf("Bookerio: Indexando por Autor los libros agregados recientemente \n");
		handlerComandos->indexar('a');
		printf("Bookerio: Fin de indexado por Autor.\n");
		break;}

	case 't':   {
		printf("Bookerio: Indexando por Título los libros agregados recientemente \n");
		handlerComandos->indexar('t');
		printf("Bookerio: Fin de indexado por Título.\n");
		break;}

	case 'p':   {
		printf("Bookerio: Indexando por Palabras los libros agregados recientemente \n");
		handlerComandos->indexar('p');
		printf("Bookerio: Fin de indexado por Palabras.\n");
		break;}

	case 'l':   {
		printf("Bookerio: Listando todos los archivos tomados recientemente \n");
		handlerComandos->listarLibrosIngresados();
		printf("Bookerio: Fin de listado de libros tomados recientemente.\n");
		break;}

	case 'o':   {
		if (argv[2]) {
			printf("Bookerio: Obtener Libro %s \n", path.c_str());
			handlerComandos->obtenerLibro(atoi(argv[2]));
			printf("Bookerio: Obtener Libro %s \n", path.c_str());
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;}

	case 'q':   {
		if (argv[2]) {
			printf("-q <ID> Quita un archivo por ID \n");
			handlerComandos->quitarLibro(atoi(path.c_str()));
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;}

	case 'w':   {
		if (argv[2]) {
			printf("-qa <Autor> Consulta puntual por <Autor> \n");
			handlerComandos->consultarAutor(argv[2]);
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;}

	case 'x':   {
		if (argv[2]) {
			printf("-qe <Editorial> Consulta puntual por <Editorial> \n \n");
			handlerComandos->consultarEditorial(argv[2]);
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;}

	case 'y':   {
		if (argv[2]) {
			printf("-qt <Título> Consulta puntual por <Título> \n");
			handlerComandos->consultarTitulo(argv[2]);
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;}

	case 'z':   {
		if (argv[2]) {
			printf("-qp <Palabra/s> Consulta por cercanía y Ranqueada por <Palabra/s> \n");
			list<string> listaPalabras;
			for ( int i = 2; i < argc; ++i)
				listaPalabras.push_back(argv[i]);
			handlerComandos->consultarPalabras(listaPalabras);
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;}

	case 'v':   {
		printf("-v -archivo         Ver archivos de índice\n");
		if (argv[2]){
			opcion2 = getopt(argc,argv, "eatp?:");
			switch (opcion2){
			case 'e': {
				printf("Bookerio: Viendo estructura de árbol de Editoriales.\n");
				handlerComandos->verEstructura('e');
				printf("Bookerio: Fin de estructura de árbol de Editoriales.\n");
				break;}

			case 'a': {
				printf("Bookerio: Viendo estructura de árbol de Autores.\n");
				handlerComandos->verEstructura('a');
				printf("Bookerio: Fin de estructura de árbol de Autores.\n");
				break;}

			case 't': {
				printf("Bookerio: Viendo estructura de hash de Títulos.\n");
				handlerComandos->verEstructura('t');
				printf("Bookerio: Fin de estructura de hash de Títulos.\n");
				break;}

			case 'p': {
				printf("Bookerio: Viendo estructura de hash de Palabras.\n");
				handlerComandos->verEstructura('p');
				printf("Bookerio: Fin de estructura de hash de Palabras.\n");
				break;}

			case '?': {
				printf("Bookerio: Parámetro inválido. \n");
				printf(" Bookerio: Ingrese el parámetro -r para ver la referencia de parámetros.\n");
				break;}
			}
		}else{
			printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");}
		break;
	}
	case 'h': {
		printf("Parámetros válidos: \n");
		printf("-i <ruta>   Tomar texto de un archivo\n");
		printf("-e              Indexar por Editorial los libros agregados recientemente \n");
		printf("-a              Indexar por Autor los libros agregados recientemente \n");
		printf("-t              Indexar por Título los libros agregados recientemente \n");
		printf("-p              Indexar por Palabras los libros agregados recientemente \n");
		printf("-l              Listar todos los archivos tomados recientemente \n");
		printf("-o <ID>         Obtener archivo por ID \n");
		printf("-q <ID>         Quita un archivo por ID \n");
		printf("-v -archivo         Ver archivos de índice, donde -archivo puede ser: \n");
		printf("    -e          Ver árbol de Editorial\n");
		printf("    -a          Ver árbol de Autor\n");
		printf("    -t          Ver hash de Título\n");
		printf("    -p          Ver hash de Palabras\n");
		break;}

	case '?':   printf("Bookerio: Parámetro inválido. \nBookerio: Ingrese el parámetro -h(help) para ver la referencia de parámetros. \n"); break;
	}

	delete handlerComandos;
	return EXIT_SUCCESS;
}

//list<int> offsetQuiero;
//	list<int> offsetMucho;
//
//	offsetQuiero.push_back(27);
//	offsetQuiero.push_back(172);
//
//	offsetMucho.push_back(18);
//	offsetMucho.push_back(143);
//
//	HandlerArchivoOcurrencias handler;
//
//	Palabra palabraQuiero = handler.obtenerPalabra(offsetQuiero);
//	Palabra palabraMucho = handler.obtenerPalabra(offsetMucho);
//
//	list<Palabra> palabras;
//
//	palabras.push_back(palabraQuiero);
//	palabras.push_back(palabraMucho);
//
//	ProcesadorConsulta procesador;
//
//	Palabra palabraCoincidente = procesador.procesarApariciones(palabras);
//	list<int> documentos;
//
//	//Si obtengo mas de un documento es porque primero debo filtrar por proximidad
//	if (palabraCoincidente.obtenerDocumentos().size() > 1)
//	{
//		documentos = procesador.filtrarProximidad(palabraCoincidente);
//	}
//	else
//		documentos = palabraCoincidente.obtenerDocumentos();
//
//	list<int> :: iterator itDocumentos = documentos.begin();
//
//	while(itDocumentos != documentos.end())
//	{
//		cout<<"Documento: "<< *itDocumentos<<endl;
//		++itDocumentos;
//	}
//
//	if(palabraCoincidente.obtenerDocumentos().size() == 0)
//	{
//		cout<<"No hay coincidencias"<<endl;
//	}
//
//
//
//
//	ProcesadorConsulta procesador;
//
//	list<Palabra> palabras;
//
//	Palabra palabra1;
//	Palabra palabra2;
//	Palabra palabra3;
//
//	palabra1.setPalabra("hola");
//	palabra2.setPalabra("como");
//	palabra3.setPalabra("estas");
//
//	list<int> posiciones1;
//	list<int> posiciones2;
//	list<int> posiciones3;
//	list<int> posiciones4;
//	list<int> posiciones5;
//	list<int> posiciones6;
//	list<int> posiciones7;
//	list<int> posiciones8;
//	list<int> posiciones9;
//	list<int> posiciones10;
//
//	//Para la palabra HOLA
//	posiciones1.push_back(50);
//	posiciones2.push_back(50);
//	posiciones3.push_back(45);
//
//
//	//Para la palabra COMO
//	posiciones4.push_back(30);
//	posiciones5.push_back(30);
//	posiciones6.push_back(40);
//
//
//	//Para la palabra ESTAS
//	posiciones8.push_back(10);
//	posiciones9.push_back(10);
//	posiciones10.push_back(50);
//
//	Aparicion aparicion1;
//	Aparicion aparicion2;
//	Aparicion aparicion3;
//	Aparicion aparicion4;
//	Aparicion aparicion5;
//	Aparicion aparicion6;
//	Aparicion aparicion7;
//	Aparicion aparicion8;
//	Aparicion aparicion9;
//	Aparicion aparicion10;
//
//
//	aparicion1.setIdDocumento(1);
//	aparicion2.setIdDocumento(7);
//	aparicion3.setIdDocumento(10);
//
//	aparicion1.agregarPosiciones(posiciones1,"hola");
//	aparicion2.agregarPosiciones(posiciones2,"hola");
//	aparicion3.agregarPosiciones(posiciones3,"hola");
//
//
//
//	//Agrego las apariciones para la palabra HOLA
//	palabra1.agregarAparicion(aparicion1);
//	palabra1.agregarAparicion(aparicion2);
//	palabra1.agregarAparicion(aparicion3);
//
//
//	aparicion4.setIdDocumento(1);
//	aparicion5.setIdDocumento(7);
//	aparicion6.setIdDocumento(10);
//
//	aparicion4.agregarPosiciones(posiciones4,"como");
//	aparicion5.agregarPosiciones(posiciones5,"como");
//	aparicion6.agregarPosiciones(posiciones6,"como");
//
//
//	//Agrego las apariciones para la palabra COMO
//	palabra2.agregarAparicion(aparicion4);
//	palabra2.agregarAparicion(aparicion5);
//	palabra2.agregarAparicion(aparicion6);
//
//
//	aparicion8.setIdDocumento(1);
//	aparicion9.setIdDocumento(7);
//	aparicion10.setIdDocumento(10);
//
//	aparicion8.agregarPosiciones(posiciones8,"estas");
//	aparicion9.agregarPosiciones(posiciones9,"estas");
//	aparicion10.agregarPosiciones(posiciones10,"estas");
//
//	//Agrego las apariciones para la palabra ESTAS
//	palabra3.agregarAparicion(aparicion8);
//	palabra3.agregarAparicion(aparicion9);
//	palabra3.agregarAparicion(aparicion10);
//
//	palabras.push_back(palabra1);
//	palabras.push_back(palabra2);
//	palabras.push_back(palabra3);
//
//	documentos3.push_back(3);
//	documentos3.push_back(4);
//	documentos3.push_back(7);
//
//	aparicion1.setDocumentos(documentos1);
//
//	aparicion2.setDocumentos(documentos2);
//
//	aparicion3.setDocumentos(documentos3);
//
//	apariciones.push_back(aparicion1);
//	apariciones.push_back(aparicion2);
//	apariciones.push_back(aparicion3);
//
//	//Palabra palabraCoincidente = procesador.procesarApariciones(palabras);
//	//list<int> documentos;
//
//	//Si obtengo mas de un documento es porque primero debo filtrar por proximidad
//	if (palabraCoincidente.obtenerDocumentos().size() > 1)
//	{
//			documentos = procesador.filtrarProximidad(palabraCoincidente);
//	}
//	else
//		documentos = palabraCoincidente.obtenerDocumentos();
//
//	list<int> :: iterator itDocumentos = documentos.begin();
//
//	while(itDocumentos != documentos.end())
//	{
//		cout<<"Documento: "<< *itDocumentos<<endl;
//		++itDocumentos;
//	}
//
//	if(palabraCoincidente.obtenerDocumentos().size() == 0)
//	{
//		cout<<"No hay coincidencias"<<endl;
//
//	}
//
//
//	cout<<"Palabra : "<<palabraCoincidente.getPalabra()<<endl;
//
//	list<Aparicion> apariciones = palabraCoincidente.getApariciones();
//
//	list<Aparicion> :: iterator itApariciones = apariciones.begin();
//
//	while(itApariciones != apariciones.end())
//	{
//		cout<<"Documento :"<<(*itApariciones).getIdDocumento()<<endl;
//
//		Aparicion aparicionActual = *itApariciones;
//
//		list<Posicion> posiciones = aparicionActual.getPosiciones();
//
//		list<Posicion> :: iterator itPosiciones = posiciones.begin();
//
//		while(itPosiciones != posiciones.end())
//		{
//			cout<<"Posicion palabra :"<<(*itPosiciones).getPalabra()<<endl;
//
//			Posicion posicionActual = *itPosiciones;
//
//			list<int> pos = posicionActual.getPosiciones();
//			list<int> :: iterator itPos = pos.begin();
//
//			while(itPos != pos.end())
//			{
//				cout<<"Posicion actual :"<< *itPos <<endl;
//				++itPos;
//
//			}
//
//			++itPosiciones;
//		}
//
//		++itApariciones;
//	}


////============================================================================
//// Name        : arbol.cpp
//// Author      : Lucas Uccello
//// Version     :
//// Copyright   :
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <iostream>
//using namespace std;
//#include "Arbol/ArbolBMas.h"
//
//int main() {
//	int i = 0;
//
//
//	while ( i < 10){
//		stringstream ss;
//		ss << i;
//		string s = ss.str();
//		ArbolBMas* arbol = new ArbolBMas("Editorial", 2);
//		string pepe = "Lucas";
//		arbol->insertar(new Elementos(new Clave(pepe), new CadenaBytes(pepe), new CadenaBytes(s)));
//		++i;
//		cout << "Inserte Elemento: " << i << endl;
//		delete arbol;
//	}


//	ArbolBMas* arbol = new ArbolBMas("Editorial", 2);
//	arbol->mostrar();
//	Elementos* elemento = new Elementos(new Clave("Lucas"), new CadenaBytes("Lucas"), new CadenaBytes("5"));
//	arbol->borrar(elemento);
//	delete elemento;
//	arbol->mostrar();
//	delete arbol;
//	return 0;
//}
