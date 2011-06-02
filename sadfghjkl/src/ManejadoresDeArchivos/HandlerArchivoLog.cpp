
#include "HandlerArchivoLog.h"

HandlerArchivoLog::HandlerArchivoLog() {
	// TODO Auto-generated constructor stub
}

HandlerArchivoLog::~HandlerArchivoLog() {
	// TODO Auto-generated destructor stub
}

void HandlerArchivoLog::insertarRegistro(int IDArchivo){

	// Busco en el log si ya existe un registro con el mismo id
	int puntero = buscarRegistro(IDArchivo);
	string linea = crearStringAInsertar(IDArchivo, 0, 0, 0, 0);

	ofstream archivoLog;

	// Si no existe el ID, agrego el registro al final del archivo
	if (puntero == ERROR){
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::app);
		if (!archivoLog.is_open()){
			archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
			archivoLog.close();
			archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::app);
		}
		archivoLog.write(linea.c_str(), linea.length());
		archivoLog.close();
	} else {
		//En cambio si existe el ID, solamente limpio las estructuras
		archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
		if (!archivoLog.is_open()){
			archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
			archivoLog.close();
			archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
		}
		archivoLog.seekp(puntero);
		archivoLog.write(linea.c_str(), linea.length());
	    archivoLog.close();
	}

}


int HandlerArchivoLog::buscarRegistro(int IDArchivo){

    bool registroEncontrado = false ;
	char cadena[100];
    string cad;
    int puntero = 0 , IDActual= 0 ;

    fstream archivoLog;
	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
	if (!archivoLog.is_open()){
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
		archivoLog.close();
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
	}
    archivoLog.seekg(0);

	while (!registroEncontrado && !archivoLog.eof() ){
        puntero = archivoLog.tellg();
		archivoLog.getline (cadena, 100);
        cad = cadena;
        if (cad.length() > 0 ) {
            IDActual= atoi(strtok(cadena,"|"));
            if (IDActual == IDArchivo){
                registroEncontrado = true;
            }
	    }
    }
	archivoLog.close();
	if(!registroEncontrado){
		puntero = -1;
	}
    return puntero;
}

bool HandlerArchivoLog::obtenerIDEstructuras(int IDArchivo, int& a,int& e,int& t,int& p){

	 int puntero = buscarRegistro(IDArchivo);
	 if (puntero == ERROR){
		 return false;
	 }
	 int ID = 0;
	 char cadena[100];
	 string linea;

	 ifstream archivoLog;
	 archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in);
	 if (!archivoLog.is_open()){
		 archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
		 archivoLog.close();
		 archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::in);
	 }
	 archivoLog.seekg(puntero);
	 archivoLog.getline(cadena,100);

	 ID = atoi(strtok(cadena,"|"));
	 a = atoi ( strtok(NULL,"|") );
	 e = atoi ( strtok(NULL,"|") );
	 t = atoi ( strtok(NULL,"|") );
	 p = atoi ( strtok(NULL,"\n") );
	 archivoLog.close();
	 return true;

}
void HandlerArchivoLog::setearIndexado(int IDArchivo, int parametro){
    int puntero = buscarRegistro(IDArchivo);
    int ID= 0, ind1=0 , ind2=0, ind3=0, ind4=0;
	char cadena[100];
    string linea;

    fstream archivoLog;
	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
	if (!archivoLog.is_open()){
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
		archivoLog.close();
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
	}
    archivoLog.seekg(puntero);
    archivoLog.getline(cadena,100);

    ID = atoi(strtok(cadena,"|"));
    ind1 = atoi ( strtok(NULL,"|") );
    ind2 = atoi ( strtok(NULL,"|") );
    ind3 = atoi ( strtok(NULL,"|") );
    ind4 = atoi ( strtok(NULL,"\n") );

    switch (parametro){
        case 'a':{ ind1 = 1; break;}

        case 'e':{ ind2 = 1; break;}

        case 't':{ ind3 = 1; break;}

        case 'p':{ ind4 = 1; break;}

    }
    linea = crearStringAInsertar(IDArchivo, ind1, ind2, ind3, ind4);
    archivoLog.seekp(puntero);
	archivoLog.write(linea.c_str(), linea.length());
    archivoLog.close();

}


void HandlerArchivoLog::obtenerListaIDs(list<int>& listaDeIds){
	fstream archivoLog;
    int IDActual=0 , puntero=0;
	char cadena[100];
    string cad;

	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
	if (!archivoLog.is_open()){
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
		archivoLog.close();
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
	}
	archivoLog.seekg(0);
	while (!archivoLog.eof() ){
        puntero = archivoLog.tellg();
		archivoLog.getline (cadena, 100);
		cad = cadena;
		if (cad.length() > 0){
			IDActual = atoi(strtok(cadena,"|"));
			listaDeIds.push_back(IDActual);
		}
	}
	archivoLog.close();
}


void HandlerArchivoLog::obtenerListaIDsAIndexar (int parametro,list<int>& listaDeIds){
	fstream archivoLog;
    int IDActual = 0, ind1=0 , ind2=0, ind3=0, ind4=0;
    string cad;
	char cadena[100];
	bool indexado = false;
	archivoLog.open(PATH_ARCHIVO_LOG, std::ios_base::in | std::ios_base::out);
	if (!archivoLog.is_open()){
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::out);
		archivoLog.close();
		archivoLog.open(PATH_ARCHIVO_LOG,std::ios_base::in | std::ios_base::out);
	}
	archivoLog.seekg(0);
	while (!archivoLog.eof() ){
		archivoLog.getline (cadena, 100);
		cad = cadena;
		if (cad.length() > 0 ) {
			IDActual = atoi(strtok(cadena,"|"));
		    ind1 = atoi ( strtok(NULL,"|") );
		    ind2 = atoi ( strtok(NULL,"|") );
		    ind3 = atoi ( strtok(NULL,"|") );
		    ind4 = atoi ( strtok(NULL,"\n") );
		    switch (parametro){
		        case 'a':{
		        	if (ind1 == 1)
		        		indexado = true;
		        	break;}
		        case 'e':{
		        	if (ind2 == 1)
		        		indexado = true;
		        	break;}
		        case 't':{
		        	if (ind3 == 1)
		        		indexado = true;
		        	break;}
		        case 'p':{
		        	if (ind4 == 1)
		        		indexado = true;
		        	break;}
		    }
			if (!indexado){
				listaDeIds.push_back(IDActual);
			}

		}
		indexado = false;
	}
	archivoLog.close();
}

string HandlerArchivoLog::crearStringAInsertar(int numero, int ind1, int ind2, int ind3, int ind4){
   stringstream ss;
   ss << numero  << "|" << ind1 << "|" << ind2 << "|" << ind3 << "|" << ind4 << "\n"  ;
   return ss.str();
}
