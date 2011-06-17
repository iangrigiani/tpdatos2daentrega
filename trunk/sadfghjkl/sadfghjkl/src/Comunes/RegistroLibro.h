#ifndef REGISTROLIBRO_H_
#define REGISTROLIBRO_H_
#include <string.h>
#include <list>
using namespace std;

class RegistroLibro {
private:
	string autor;
	string editorial;
	string titulo;
	list<string> palabras;
public:
	RegistroLibro(){

	}
	virtual ~RegistroLibro(){

	}
    string getAutor() const
    {
        return autor;
    }

    string getEditorial() const
    {
        return editorial;
    }

    list<string> getPalabras() const
    {
        return palabras;
    }

    string getTitulo() const
    {
        return titulo;
    }

    void setAutor(string autor)
    {
        this->autor = autor;
    }

    void setEditorial(string editorial)
    {
        this->editorial = editorial;
    }

    void setPalabras(list<string> palabras)
    {
        this->palabras = palabras;
    }

    void setTitulo(string titulo)
    {
        this->titulo = titulo;
    }

};

#endif /* REGISTROLIBRO_H_ */
