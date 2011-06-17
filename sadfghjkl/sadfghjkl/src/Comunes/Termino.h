#ifndef TERMINO_H_
#define TERMINO_H_

class Termino {
private:
	int IdTermino;
	std::string termino;
public:
	Termino(){

	}
	Termino(std::string termino, int IdTermino){
		this->termino = termino;
		this->IdTermino = IdTermino;
	}
	int getIdTermino () const {
		return this->IdTermino;
	}
	std::string getTermino () const {
		return this->termino;
	}

	void setTermino(std::string termino){
		this->termino = termino;
	}

	void setIdTermino(int termino){
		this->IdTermino = termino;
	}
	virtual ~Termino(){

	}
};

#endif /* TERMINO_H_ */
