#include "HandlerNormasAInfinito.h"

HandlerNormasAInfinito::HandlerNormasAInfinito() {
}
HandlerNormasAInfinito::HandlerNormasAInfinito(vector<int> idTerminos){
	this->listaIdTermino = idTerminos;
}

HandlerNormasAInfinito::~HandlerNormasAInfinito() {
}

void HandlerNormasAInfinito::actualizarPesosTerminos (list<int>& IDsTerminos){
	//TODO implementar
	// usar el método HandlerNormasAInfinito::incrementarPesoTermino
}


void HandlerNormasAInfinito::incrementarPesoTermino (int IDTermino){
	int pesoTermino = 0;
	ofstream aNormas;
	string linea;

	int puntero = this->buscarTermino(IDTermino, pesoTermino);
	linea = this->crearStringAInsertar(IDTermino, pesoTermino);

	// Si no existe el ID, agrego el registro al final del archivo
	if (puntero == ERROR){
		aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::app);
		if (!aNormas.is_open()){
			aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::out);
			aNormas.close();
			aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::app);
		}

		aNormas.write(linea.c_str(), linea.length());
		aNormas.close();
	} else {
		//En cambio si existe el ID, solamente limpio las estructuras
		aNormas.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
		if (!aNormas.is_open()){
			aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::out);
			aNormas.close();
			aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
		}
		aNormas.seekp(puntero);
		aNormas.write(linea.c_str(), linea.length());
	    aNormas.close();

	}
}



void HandlerNormasAInfinito::decrementarPesoTermino (int IDTermino){
	//TODO implementar
}

int HandlerNormasAInfinito::buscarPesoTermino(int IDTermino){
	//TODO implementar
	return IDTermino;
}

/*private*/
int HandlerNormasAInfinito::buscarTermino(int IDTermino, int& pesoTermino){
    bool terminoEncontrado = false ;
	char cadena[100];
    string cad;
    int puntero = 0 , IDActual= 0 , pesoTerminoActual = 0;

    fstream aNormas;
	aNormas.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
	if (!aNormas.is_open()){
		aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::out);
		aNormas.close();
		aNormas.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
	}
    aNormas.seekg(0);

	while (!terminoEncontrado && !aNormas.eof() ){
        puntero = aNormas.tellg();
		aNormas.getline (cadena, 100);
        cad = cadena;
        if (cad.length() > 0 ) {
            IDActual= atoi(strtok(cadena,"|"));
            pesoTerminoActual = atoi(strtok(NULL,"\n"));
            if (IDActual == IDTermino){
            	pesoTermino = pesoTerminoActual;
                terminoEncontrado = true;
            }
	    }
    }
	aNormas.close();
	if(!terminoEncontrado){
		puntero = -1;
	}
    return puntero;

}


string HandlerNormasAInfinito::crearStringAInsertar(int IDTermino, int pesoTermino){
   stringstream ss;
   ss <<IDTermino << "|" << pesoTermino<< "\n"  ;
   return ss.str();
}
