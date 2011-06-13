#include "HandlerComandos.h"

HandlerComandos::HandlerComandos() {
	this-> handler 			= new HandlerArchivoRLV();
	this-> parser 			= new ParserDeLibros();
	this-> log 				= new HandlerArchivoLog();
	this->handlerOcurrencias = new HandlerArchivoOcurrencias();
}

HandlerComandos::~HandlerComandos() {
	delete this-> parser;
	delete this-> handler;
	delete this-> log;
	delete this->handlerOcurrencias;
	//delete this-> arbol;
}

void HandlerComandos::guardarLibroEnArchivoMaestro(const string& path_nuevo_libro){
	int ID_Archivo =  0;
	ID_Archivo = this->handler->insertarRegistro(path_nuevo_libro);
	if ( ID_Archivo != ERROR){
		this-> log->insertarRegistro(ID_Archivo);
		printf("Bookerio: Libro guardado con éxito. \n");
		printf("		  ID Libro: %d \n", ID_Archivo);
	}else{
		printf("Bookerio: Libro no pudo ser guardado con éxito. \n");
	}
}
//
void HandlerComandos::indexar(int parametro){

	// Lista de IDs de libros a Indexar
	list<int> listaDeIds;
	this->log->obtenerListaIDsAIndexar(parametro,listaDeIds); // Obtengo todos los offsets
	list<int>::iterator it = listaDeIds.begin();
	// Para cada offset segun que parametro recibi inserto.
	while ( it != listaDeIds.end()){
		switch (parametro){
		case 'a':{
			this->arbol = new ArbolBMas(PATH_AUTOR,2);
			insertarEnArbol (1, (*it));
			this->log->setearIndexado(*it,'a');break;}

		case 'e':{
			this->arbol = new ArbolBMas(PATH_EDITORIAL,2);
			insertarEnArbol (2, (*it));
			this->log->setearIndexado(*it,'e'); break;}

		case 't': {
			this->insertar_en_hash_titulo(*it);
			this->log->setearIndexado(*it,'t');
			break;
		}

		case 'p': {
			this->insertar_en_hash_palabra(*it);
			this->log->setearIndexado(*it,'p');
			break;
		}
		}
		++ it;
	}
}
//
void HandlerComandos::listarLibrosIngresados(){
	list<int> listaDeIds;
	this->log->obtenerListaIDs(listaDeIds);
	list<int>::iterator it = listaDeIds.begin();
	printf("Bookerio: Total Libros Ingresados: %d \n" , listaDeIds.size());
	printf("Bookerio: Libros Ingresados:\n");
	while ( it != listaDeIds.end()){
		printf("%d \n", *it);
		it++;
	}
	printf("Bookerio: Fin de libros Ingresados:\n");
}
//
void HandlerComandos::obtenerLibro(int IDArchivo){
	char* libro = this->handler->buscarRegistro(IDArchivo);
	printf("Bookerio: Libro %d \n", IDArchivo);
	printf("%s", libro);
	printf("Bookerio: Fin de libro %d \n", IDArchivo);
}
//
void HandlerComandos::quitarLibro(int IDArchivo) {
	//Borrar libro de todos los índices
	int a = 0, e = 0, t= 0, p = 0;
	if (this->log->obtenerIDEstructuras(IDArchivo, a,e,t,p)){
		if (a == 1){
			if (!eliminarEnArbol(1, IDArchivo)){
				printf("Bookerio: Libro ID  %d : No pudo borrarse del indice por autor. \n", IDArchivo);;
			}
		}
		if (e == 1){
			if (!eliminarEnArbol(2, IDArchivo)){
				printf("Bookerio: Libro ID  %d : No pudo borrarse del indice por editorial. \n", IDArchivo);;
			}
		}
		if (t == 1){
			this->eliminar_de_hash_titulo(IDArchivo);
		}
		if (p == 1){
			this->eliminar_de_hash_palabra(IDArchivo);
		}
		//Borrar libro del archivo maestro
		this->handler->quitarRegistro(IDArchivo);
		printf("Bookerio: Libro ID  %d : Borrado procesado. \n", IDArchivo);
	}else{
		printf("Bookerio: Libro ID  %d : Error: No existe. \n", IDArchivo);
	}
}
//
void HandlerComandos::verEstructura(int parametro){

	switch (parametro) {
	case 'a': {
		printf("Viendo estructura del árbol de autores. \n");
		this->arbol = new ArbolBMas(PATH_AUTOR,2);
		arbol->mostrar();
		//delete arbol;
		break; }
	case 'e': {
		printf("Viendo estructura del árbol de editoriales. \n");
		this->arbol = new ArbolBMas(PATH_EDITORIAL,2);
		//ArbolBMas* arbol = new ArbolBMas(2, PATH_NODOS);
		arbol->mostrar();
		delete arbol;
		break; }

	case 't': {
		printf("Viendo estructura del hash de títulos. \n");
		HashTitulo hash(NOM_BLOQUES_TITULO, NOM_ESP_LIBRE_TITULO, NOM_TABLA_TITULO);
		hash.mostrar(NOM_SALIDA_TITULO);
		break; }
	case 'p': {
		printf("Viendo estructura del hash de palabras. \n");
		HashPalabra hash(NOM_BLOQUES_PALABRA, NOM_ESP_LIBRE_PALABRA, NOM_TABLA_PALABRA);
		hash.mostrar(NOM_SALIDA_PALABRA);
		break; }

	}
}
/*
int HandlerComandos::funcion_hash_titulo(const string& str) {

	int size = str.size();
	char* cadena = (char*) malloc (sizeof(char) * (size + 1));
	str.copy(cadena, size);
	cadena[size] = '\0';

	list < string >::iterator it;
	bool filtrar =  true;
	list < string > palabras = this->parser->obtenerDatos(cadena,filtrar);
	int clave = 0;
	for (it = palabras.begin(); it != palabras.end(); ++ it)
		for (unsigned int i = 0; i < (*it).size(); ++ i)
			clave += ((int)(*it)[i]) * i;

	free(cadena);
	return clave;
}
*/
void HandlerComandos::insertar_en_hash_titulo(int offset) {
	RegistroLibro reg;
	this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset), reg);
	if (reg.getAutor() != REGISTRO_ERRONEO){
		HashTitulo hash(NOM_BLOQUES_TITULO, NOM_ESP_LIBRE_TITULO, NOM_TABLA_TITULO);
		hash.alta(reg.getTitulo(), offset);
		cout<<"ID:"<<offset<<".Libro indexado por titulo.\n"<<endl;
	}else{
		cout<<"ID:"<<offset<<"No pudo ser insertado en el hash de titulo.\n"<<endl;
	}
}
//
void HandlerComandos::eliminar_de_hash_titulo(int offset) {

	RegistroLibro reg;
	this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset), reg);
	if (reg.getAutor() != REGISTRO_ERRONEO){
		HashTitulo hash(NOM_BLOQUES_TITULO, NOM_ESP_LIBRE_TITULO, NOM_TABLA_TITULO);
		hash.baja(reg.getTitulo());
	}else{
		cout<<"ID:"<<offset<<"No pudo ser insertado en el hash de titulo.\n"<<endl;
	}
//	hash.mostrar();
}
//
list < int > HandlerComandos::eliminar_repeticion(list < int > & palabras) {

	list < int > filtrados;
	list < int > ::iterator it_1;
	list < int > ::iterator it_2;

	for (it_1 = palabras.begin(); it_1 != palabras.end(); ++ it_1) {
		it_2 = filtrados.begin();
		while ((*it_2) != (*it_1) && it_2 != filtrados.end())
			++ it_2;
		if ((*it_2) != (*it_1) && it_2 == filtrados.end())
			filtrados.push_back(*it_1);
	}
	return filtrados;
}
//
int HandlerComandos::funcion_hash_palabra(const string& str) {

	int clave = 0;
	for (unsigned int i = 0; i < str.size(); ++ i)
		clave += ((int)str[i]) * (str.size() - i);

	return clave;
}
//
void HandlerComandos::insertar_en_hash_palabra(int offset) {

	list<string> palabras = this->parser->obtenerPalabrasDeLibro(this->handler->buscarRegistro(offset));

	if (palabras.size() > 0){

		HashPalabra hash(NOM_BLOQUES_PALABRA, NOM_ESP_LIBRE_PALABRA, NOM_TABLA_PALABRA);

		ProcesadorOcurrencia procesador;
		list<Ocurrencia> ocurrencias = procesador.obtenerOcurrencias(palabras);

		list<Ocurrencia> :: iterator itOcurrencias;

		for(itOcurrencias = ocurrencias.begin(); itOcurrencias != ocurrencias.end();++itOcurrencias)
		{

			Ocurrencia ocurrenciaActual = *itOcurrencias;
			int offsetOcurrencia = this->handlerOcurrencias->insertarOcurrencia(ocurrenciaActual,offset);
			int clave = ocurrenciaActual.getIdPalabra();
			cout << "Indexando" << clave << endl;
			hash.alta(clave, offsetOcurrencia);

		}


			/*
			for (it_1 = palabras.begin(); it_1 != palabras.end(); ++ it_1) {
				str = *it_1;
				clave = this->funcion_hash_palabra(str);
				str.clear();
				claves.push_back(clave);
			}

			list < int > filtrados = this->eliminar_repeticion(claves);
			int t = 0;
			for (it_2 = filtrados.begin(); it_2 != filtrados.end(); ++ it_2) {
				offsets.push_back(offset);
				hash.insercion((*it_2), offsets);
				offsets.clear();
				cout << "Processando palabras Libro de ID " << offset << " ..." << (int) ((t * 100 / filtrados.size())+1) << "%\r";
				++t;
			}*/

	}else{
		cout<<"ID:"<<offset<<"No pudo ser insertado en el hash de palabra.\n"<<endl;
	}


}
//
void HandlerComandos::eliminar_de_hash_palabra(int offset) {

	RegistroLibro reg;
	this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset), reg);
	if (reg.getAutor() != REGISTRO_ERRONEO){
		HashPalabra hash(NOM_BLOQUES_PALABRA, NOM_ESP_LIBRE_PALABRA, NOM_TABLA_PALABRA);

		int clave;
		list < string > palabras = reg.getPalabras();
		list < string > ::iterator it;
		for (it = palabras.begin(); it != palabras.end(); ++ it) {
			clave = this->funcion_hash_palabra(*it);
			hash.baja(clave, offset);
		}
	}else{
		cout<<"ID:"<<offset<<"No pudo ser borrado en el hash de palabra.\n"<<endl;
	}
}
//
void HandlerComandos::insertarEnArbol (int tipoArbol, int offset){
	//	ArbolBMas* arbol = new ArbolBMas(tipoArbol, PATH_NODOS);
	char * puntero = this->handler->buscarRegistro(offset);
	if (puntero){
		RegistroLibro reg;
		this->parser->obtenerRegistroDeLibro(puntero, reg);

		if (tipoArbol == 1){
			stringstream ss;
			ss << offset;
			Elementos* elemento = new Elementos(new Clave(reg.getAutor()), new CadenaBytes(reg.getAutor()), new CadenaBytes(ss.str()));
			if(elemento->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
				cout<<"Elemento demasiado grande.\n"<<endl;
			}else{
				if(arbol->insertar(elemento))
					cout<<"ID:"<<offset<<".Libro indexado por autor.\n"<<endl;
			}
			delete elemento;
		}else{
			stringstream ss;
			ss << offset;
			Elementos* elemento2 = new Elementos(new Clave(reg.getEditorial()), new CadenaBytes(reg.getEditorial()), new CadenaBytes(ss.str()));
			if(elemento2->getTamanio() > (TAM_EFECTIVO_NODO * PORC_TAMANIO_NODO / 100) ){
				cout<<"Elemento demasiado grande.\n"<<endl;
			}else{
				if(arbol->insertar(elemento2))
					cout<<"ID:"<<offset<<".Libro indexado por editorial.\n"<<endl;
				delete elemento2;
			}
			//	delete arbol;
		}
	}else{
		cout<<"ID:"<<offset<<"No pudo ser indexado como autor.\n"<<endl;
	}
}
//
bool HandlerComandos::eliminarEnArbol(int tipoArbol, int offset) {
	RegistroLibro reg;
	this->parser->obtenerRegistroDeLibro(this->handler->buscarRegistro(offset), reg);
	bool retorno = false;
	if (reg.getAutor() != REGISTRO_ERRONEO){
		if (tipoArbol == 1){
			this->arbol = new ArbolBMas(PATH_AUTOR,2);
			stringstream ss;
			ss << offset;
			Elementos* elemento = new Elementos(new Clave(reg.getAutor()), new CadenaBytes(reg.getAutor()), new CadenaBytes(ss.str()));
			retorno = arbol->borrar(elemento);
			delete elemento;
			delete arbol;
		}else{
			this->arbol = new ArbolBMas(PATH_EDITORIAL,2);
			stringstream ss;
			ss << offset;
			Elementos* elemento = new Elementos(new Clave(reg.getEditorial()), new CadenaBytes(reg.getEditorial()), new CadenaBytes(ss.str()));
			retorno = arbol->borrar(elemento);
			delete elemento;
			delete arbol;
		}
	}else{
		retorno = false;
	}
	return retorno;
	//	delete arbol;
}

void HandlerComandos::consultarEditorial(string editorial){
	this->parser->downCase(editorial);
	ProcesadorConsulta procesador;
	list<int> listaDocumentos = procesador.consultaEditorial(editorial);
	if (listaDocumentos.size() > 0){
		cout << "Se recuperaron " << listaDocumentos.size() << " libros, cuya Editorial es ->" <<
				editorial << "<-. Se genero un archivo en el directorio con el resultado ( Path: Consulta Editorial )" << endl;
		fstream off;
		off.open(PATH_CONSULTA_EDITORIAL, ios_base::out);
		off.close();
		off.open(PATH_CONSULTA_EDITORIAL, ios_base::in | ios_base::out);
		list<int>::iterator it = listaDocumentos.begin();
		while ( it != listaDocumentos.end()){
			stringstream ss;
			ss << this->handler->buscarRegistro((*it));
			off.seekg(0, ios_base::end);
			off.write(ss.str().c_str(), ss.str().length());
			off.flush();
			++it;
		}
		off.close();
	}else{
		cout << "No se recuperaron documentos para esta consulta" << endl;
	}
}
void HandlerComandos::consultarAutor(string autor){
	this->parser->downCase(autor);
	ProcesadorConsulta procesador;
	list<int> listaDocumentos = procesador.consultaAutor(autor);
	if (listaDocumentos.size() > 0){
		cout << "Se recuperaron " << listaDocumentos.size() << " libros, cuyo autor es ->" <<
				autor << "<-. Se genero un archivo en el directorio con el resultado ( Path: Consulta autor )" << endl;
		fstream off;
		off.open(PATH_CONSULTA_AUTOR, ios_base::out);
		off.close();
		off.open(PATH_CONSULTA_AUTOR, ios_base::in | ios_base::out);
		list<int>::iterator it = listaDocumentos.begin();
		while ( it != listaDocumentos.end()){
			stringstream ss;
			ss << this->handler->buscarRegistro((*it));
			off.seekg(0, ios_base::end);
			off.write(ss.str().c_str(), ss.str().length());
			off.flush();
			++it;
		}
		off.close();
	}else{
		cout << "No se recuperaron documentos para esta consulta" << endl;
	}
}
void HandlerComandos::consultarTitulo(string titulo) {
	ProcesadorConsulta procesador;

	ParserDeLibros parser;
	parser.downCase(titulo);

	int documento = procesador.consultaTitulo(titulo);
	if (documento != ERROR) {
		cout << "Se recuperó el libro cuyo título es: " << titulo << endl;
		cout << "Se generó un archivo en el directorio con el resultado ( Path: Consulta titulo )" << endl;
		fstream off;
		off.open(PATH_CONSULTA_TITULO, ios_base::out);
		off.close();
		off.open(PATH_CONSULTA_TITULO, ios_base::in | ios_base::out);
		stringstream ss;
		ss << this->handler->buscarRegistro(documento);
		off.seekg(0, ios_base::end);
		off.write(ss.str().c_str(), ss.str().length());
		off.flush();
		off.close();
	}
	else cout << "No se recuperaron documentos para esta consulta." << endl;
}

void HandlerComandos::consultarPalabras(list<string> palabras){
	ProcesadorConsulta procesador;
	string busqueda;
	list<string>::iterator it = palabras.begin();
	while( it != palabras.end()){
		busqueda += (*it);
		++it;
	}
	list<int> listaDocumentos = procesador.consultaPalabras(palabras);
	if (listaDocumentos.size() > 0){
		cout << "Se recuperaron " << listaDocumentos.size() << " libros, para esta busqueda: ->" <<
				busqueda << "<-. Se genero un archivo en el directorio con el resultado ( Path: Consulta Palabras )" << endl;
		fstream off;
		off.open(PATH_CONSULTA_PALABRAS, ios_base::out);
		off.close();
		off.open(PATH_CONSULTA_PALABRAS, ios_base::in | ios_base::out);
		list<int>::iterator it = listaDocumentos.begin();
		while ( it != listaDocumentos.end()){
			stringstream ss;
			ss << this->handler->buscarRegistro((*it));
			off.seekg(0, ios_base::end);
			off.write(ss.str().c_str(), ss.str().length());
			off.flush();
			++it;
		}
		off.close();
	}else{
		cout << "No se recuperaron documentos para esta consulta" << endl;
	}
}