#include "ParserDeLibros.h"

ParserDeLibros::ParserDeLibros() {
	obtenerListaStopWords();
}
ParserDeLibros::~ParserDeLibros() {
        delete this->libroActual;
}

char * ParserDeLibros::obtenerAutor(){
        char AutorPatron[] = "Autor:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, AutorPatron, STRING_BUFFER);
}

char * ParserDeLibros::obtenerTitulo(){
        char TituloPatron[] = "Titulo:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, TituloPatron, STRING_BUFFER);
}

char * ParserDeLibros::obtenerEditorial(){
        char EditorialPatron[] = "Editorial:\\s*([^\n\r\t]*)";
        return obtenerPrimerMatch(this->libroActual, EditorialPatron, STRING_BUFFER);
}

char * ParserDeLibros::obtenerPalabras(){
        char PalabrasPatron[] = "Palabras:\\s*([^|]*)";
        return obtenerPrimerMatch(this->libroActual, PalabrasPatron, STRING_BUFFER_PALABRAS);
}

char * ParserDeLibros::obtenerPrimerMatch(char * string, char *patronDeFiltro, int size) {
    regex_t preg;
    regmatch_t pmatch[2];
    /* it's possible something won't compile like  ./regexp '*' abc */
    regcomp (&preg, patronDeFiltro, REG_EXTENDED);
    char * pom = NULL;

    if ( regexec (&preg, string, 2, pmatch, 0) == REG_NOMATCH ){
    	return pom;
    }

	pom = (char*)calloc(size, sizeof(char));
	strncpy (pom, string + pmatch[1].rm_so,
					pmatch[1].rm_eo - pmatch[1].rm_so);
	pom[pmatch[1].rm_eo - pmatch[1].rm_so] = '\0';
	regfree (&preg);

    return pom;
}

list < string > ParserDeLibros::obtenerDatos(char* cadena, bool filtrar) {
	list < string > elementos;
	char* pch = strtok(cadena, "*¿?¡!:;.,()- \n\t\r");
	string str;

	while (pch != NULL) {
		str = pch;
		this->downCase(str);
		if (filtrar){
			if (!this->esStopWords(pch)) {
				elementos.push_back(str);
			}
		}else{
			elementos.push_back(str);
		}
		str.clear();
		pch = strtok(NULL, "¿?¡!:;., \n\t\r");
	}
	return elementos;
}
/*
list < string > ParserDeLibros::obtenerDatos(char* cadena, bool filtrar) {
	list < string > elementos;
	char* pch = strtok(cadena, "¿?¡!:;.,()- \n\t\r");
	string str;

	while (pch != NULL) {
		str = pch;
		this->downCase(str);
		if (filtrar){
			if (!this->esStopWords(pch)) {
				elementos.push_back(str);
			}
		}else{
			elementos.push_back(str);
		}
		str.clear();
		pch = strtok(NULL, "¿?¡!:;., \n\t\r");
	}
	return elementos;
}
*/
list<string> ParserDeLibros::obtenerPalabrasDeLibro(char* libro){
	this->libroActual = libro;
	list < string > palabras;
	if (this->libroActual){
		//Palabras
		char * palabrasChar = this->obtenerPalabras();
		bool filtrar = false;
		palabras = this->obtenerDatos(palabrasChar, filtrar);
		delete palabrasChar;
	}
	return palabras;
}
void ParserDeLibros::obtenerRegistroDeLibro(char* libro, RegistroLibro& registro) {

	this->libroActual = libro;
	if (this->libroActual){
		string aux;
		//Autor
		aux.clear();
		aux = this->obtenerAutor();
		downCase(aux);
		registro.setAutor(aux);

		//Editorial
		char * editorial = this->obtenerEditorial();
		if (editorial){
			aux.clear();
			aux = editorial;
			downCase(aux);
			registro.setEditorial(aux);
		}else{
			aux.clear();
			aux = EDITORIAL;
			downCase(aux);
			registro.setEditorial(aux);
		}

		//Tittulo
		aux.clear();
		aux = this->obtenerTitulo();
		downCase(aux);
		registro.setTitulo(aux);


		//Palabras
		char * palabrasChar = this->obtenerPalabras();
		 bool filtrar = true;
		list < string > palabras = this->obtenerDatos(palabrasChar, filtrar);
		delete palabrasChar;
		registro.setPalabras(palabras);
	}else{
		registro.setAutor(REGISTRO_ERRONEO);
	}
}

void ParserDeLibros::downCase(string& str) {
	char c;
	for (unsigned int i = 0; i < str.size(); ++ i) {
		if (isalnum(str[i])) {
			if (!islower(str[i])) {
				c = tolower(str[i]);
				str[i] = c;
			}
		}
		else str[i] = 'z';
	}
}

