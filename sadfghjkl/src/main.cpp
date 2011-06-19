#include "Handlers//HandlerComandos.h"
#include "Procesadores/ProcesadorConsulta.h"
#include "Comunes/Aparicion.h"
#include "Comunes/Palabra.h"

using namespace std;

int main (int argc , char *argv[]){
	HandlerComandos* handlerComandos = new HandlerComandos();
	string path;

	int opcion1, opcion2;
	if ((argc!= 2) && (argc!=3)) {
		stringstream ss;
		for ( int i = 2 ; i < argc; ++i) {
			if (i == (argc - 1))
				ss << argv[i];
			else ss << argv[i] << " ";
		}
		path = ss.str();
	}else{
		if (argv[2])
			path = argv[2];
	}
	opcion1 = getopt(argc,argv, "ieatploqvhc?:");
	switch (opcion1) {
	case 'i':   {
		if (argv[2]) {
			handlerComandos->guardarLibroEnArchivoMaestro(path);
			printf("Bookerio: Libro guardado. \n");
		}else printf("Bookerio: No se puede procesar la orden: falta ruta de archivo.\n");
		break;}

	case 'e':   {
		printf("Bookerio: Indexando por Editorial los libros agregados recientemente...\n");
		handlerComandos->indexar('e');
		cout << endl;
		printf("Bookerio: Fin de indexado por Editorial.\n");
		break;}

	case 'a':   {
		printf("Bookerio: Indexando por Autor los libros agregados recientemente...\n");
		handlerComandos->indexar('a');
		cout << endl;
		printf("Bookerio: Fin de indexado por Autor.\n");
		break;}

	case 't':   {
		printf("Bookerio: Indexando por Título los libros agregados recientemente...\n");
		handlerComandos->indexar('t');
		cout << endl;
		printf("Bookerio: Fin de indexado por Título.\n");
		break;}

	case 'p':   {
		printf("Bookerio: Indexando por Palabras los libros agregados recientemente...\n");
		handlerComandos->indexar('p');
		cout << endl;
		printf("Bookerio: Fin de indexado por Palabras.\n");
		break;}

	case 'l':   {
		printf("Bookerio: Listando todos los archivos tomados recientemente...\n");
		handlerComandos->listarLibrosIngresados();
		printf("Bookerio: Fin de listado de libros tomados recientemente.\n");
		break;}

	case 'o':   {
		if (argv[2]) {
			printf("Bookerio: Obtener Libro %s \n", path.c_str());
			handlerComandos->obtenerLibro(atoi(argv[2]));
			printf("Bookerio: Obtener Libro %s \n", path.c_str());
		}else printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");
		break;}

	case 'q':   {
		if (argv[2]) {
			printf("-q <ID> Eliminar un archivo por ID. \n");
			handlerComandos->quitarLibro(atoi(path.c_str()));
		}else printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");
		break;}

	case 'c':   {
		printf("-c -archivo     Consultar un archivo de índice. \n");
		if (argv[2]) {
			opcion2 = getopt(argc, argv, "eatp?:");
			switch (opcion2) {
				case 'a':   {
					printf("-c -a <Autor> Consulta puntual por <Autor>.\n");
					stringstream ss;
					for (int i = 3; i < argc; ++ i) {
						if (i == (argc - 1))
							ss << argv[i];
						else ss << argv[i] << " ";
					}
					handlerComandos->consultarAutor(ss.str());
					break;}

				case 'e':   {
					printf("-c -e <Editorial> Consulta puntual por <Editorial>.\n");
					stringstream ss;
					for (int i = 3; i < argc; ++ i) {
						if (i == (argc - 1))
							ss << argv[i];
						else ss << argv[i] << " ";
					}
					handlerComandos->consultarEditorial(ss.str());
					break;}

				case 't':   {
					printf("-c -t <Título> Consulta puntual por <Título>.\n");
					stringstream ss;
					for (int i = 3; i < argc; ++ i) {
						if (i == (argc - 1))
							ss << argv[i];
						else ss << argv[i] << " ";
					}
					handlerComandos->consultarTitulo(ss.str());
					break;}

				case 'p':   {
					printf("-c -p <Palabra> Consulta puntual por <Palabra>.\n");
					string s;
					list < string > palabras;
					for (int i = 3; i < argc; ++ i) {
						s = argv[i];
						palabras.push_back(s);
					}
					handlerComandos->consultarPalabras(palabras);
					break;}

				case '?':   {
					printf("Bookerio: Parámetro inválido. \n");
					printf("Bookerio: Ingrese el parámetro -r para ver la referencia de parámetros.\n");
					break;}
			}
		}
		else printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");
		break;
	}

	case 'v':   {
		printf("-v -archivo     Ver un archivo de índice. \n");
		if (argv[2]){
			opcion2 = getopt(argc,argv, "eatpron?:");
			switch (opcion2){
			case 'e':   {
				printf("Bookerio: Ver estructura de árbol de Editoriales.\n");
				handlerComandos->verEstructura('e');
				break;}

			case 'a':   {
				printf("Bookerio: Ver estructura de árbol de Autores.\n");
				handlerComandos->verEstructura('a');
				break;}

			case 't':   {
				printf("Bookerio: Ver estructura de hash de Títulos.\n");
				handlerComandos->verEstructura('t');
				break;}

			case 'p':   {
				printf("Bookerio: Ver estructura de hash de Palabras.\n");
				handlerComandos->verEstructura('p');
				break;}

			case 'r':   {
				printf("Bookerio: Ver estructura de árbol de términos.\n");
				handlerComandos->verEstructura('r');
				break;}

			case 'o':   {
				printf("Bookerio: Ver estructura de archivo de ocurrencias.\n");
				handlerComandos->verEstructura('o');
				break;}

			case 'n':   {
				printf("Bookerio: Ver estructura de hash de normas.\n");
				handlerComandos->verEstructura('n');
				break;}

			case '?':   {
				printf("Bookerio: Parámetro inválido. \n");
				printf(" Bookerio: Ingrese el parámetro -h para ver la referencia de parámetros.\n");
				break;}
			}
		}else printf("Bookerio: No se puede procesar la orden: falta un parámetro.\n");
		break;
	}
	case 'h':   {
		printf("Parámetros válidos: \n");

		printf("-i <ruta>   	Guardar el libro indicado en la ruta. \n");

		printf("-e              Indexar por Editorial los libros agregados recientemente. \n");

		printf("-a              Indexar por Autor los libros agregados recientemente. \n");

		printf("-t              Indexar por Título los libros agregados recientemente. \n");

		printf("-p              Indexar por Palabra los libros agregados recientemente. \n");

		printf("-l              Listar todos los archivos guardados recientemente. \n");

		printf("-o <ID>         Obtener un libro por ID. \n");

		printf("-q <ID>         Eliminar un libro por ID. \n");

		printf("-c -archivo    Consultar un archivo de índice, donde -archivo puede ser: \n");
		printf("   -e          Para consultar el árbol de Editoriales. \n");
		printf("   -a          Para consultar el árbol de Autores. \n");
		printf("   -t          Para consultar el hash de Títulos. \n");
		printf("   -p          Para consultar el hash de Palabras. \n");

		printf("-v -archivo    Ver un archivo de índice, donde -archivo puede ser: \n");
		printf("   -e          Para ver el árbol de Editoriales. \n");
		printf("   -a          Para ver el árbol de Autores. \n");
		printf("   -t          Para ver el hash de Títulos. \n");
		printf("   -p          Para ver el hash de Palabras. \n");
		printf("   -r          Para ver el árbol de términos. \n");
		printf("   -o          Para ver el archivo de ocurrencias. \n");
		printf("   -n          Para ver el hash de normas. \n");

		break;}

	case '?':
		printf("Bookerio: Parámetro inválido. \nBookerio: Ingrese el parámetro -h(help) para ver la referencia de parámetros. \n");
		break;
	}

	delete handlerComandos;

	return EXIT_SUCCESS;
}
