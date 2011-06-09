#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#define ERROR -1
#define OKEY 0
#define BASURA_RLV 33
#define TAMANIO_BUFFER 4096
#define TAM_BLOQUE 4096
#define TAM_BUFFER 4096
#define STRING_BUFFER 4096
#define STRING_BUFFER_PALABRAS 2000000
#define CUALQUIERA 33000
#define BLOQUE_LLENO 1
#define BLOQUE_NO_LLENO 0
#define REGISTRO_ERRONEO "-1"
#define TIPO_CLAVE_NUMERICA 1

/***********************Archivo Maestro*********************/
#define PATH_REG_LONG_VARIABLE "ArchivoDeRLV.txt"
#define PATH_ESPACIO_LIBRE_RLV "controlEspaciosLibresRLV.txt"
#define PATH_ARCHIVO_LOG "logBookerio.txt"

/*************Archivo de ocurrencias de terminos***********/
#define PATH_ARCHIVO_OCURRENCIAS "ArchivoOcurrencias.txt"
#define PATH_ESPACIO_LIBRE_OCURRENCIAS "controlEspaciosLibresOcurrencias.txt"

/*************Archivo de Normas a Infinito *****************/
#define PATH_ARCHIVO_NORMA "ArchivoNormas.txt"
#define PATH_ESPACIO_LIBRE_ARCHIVO_NORMA "controlEspLibresArchivoNormas.txt"

/***********************Parser******************************/
#define EDITORIAL "Grupo17"
#define PATH_STOPWORDS "stopWords.txt"

/*******************Listas Invertidas***********************/
#define PATH_LISTAS_INVERTIDAS "listasInvertidas.txt"
#define PATH_INDICE_INVERTIDO "IndiceInvertido.txt"

/**********************Arbol B+ ***************************/
#define POTENCIA 0
#define TAM_LONG_REGISTRO sizeof(int)
#define TAM_LONG_CLAVE sizeof(char)
#define TAM_LONG_DATO sizeof(int)
#define BASE_TAMANIO 4096
#define CONST_VACIO 0x00
#define PORC_TAMANIO_NODO 50
#define TAM_TOTAL_NODO 4096
#define TAM_CONTROL_NODO 12
#define TAM_CONTROL_OVERFLOW 20
#define TAM_EFECTIVO_NODO (TAM_TOTAL_NODO - TAM_CONTROL_NODO)
#define PORCENTAJE_NODO 50
#define BUFFER_NODOS_LIBRES 4096
#define TAM_CONTROL_REGISTRO 5
#define PATH_AUTOR "Autores"
#define PATH_EDITORIAL "Editoriales"
#define PATH_ID_TERMINOS "Ids_Terminos.txt"

/************* Hash de Término & Palabra ****************/
#define TAM_CUBO 4096

/***************** Hash de Término **********************/
#define PATH_TMP_TERMINO "TempTermino.txt"
#define PATH_TABLA_TERMINO "TablaTermino.txt"
#define PATH_ESP_LIBRE_TERMINO "EspLibreTermino.txt"
#define PATH_BLOQUES_TERMINO "BloquesTermino.txt"
#define PATH_ID "ID.txt"
#define PATH_HASH_TERMINO "Terminos.txt"

/****************** Hash de Palabra *********************/
#define PATH_TMP_PALABRA "TempPalabra.txt"
#define PATH_TABLA_PALABRA "TablaPalabra.txt"
#define PATH_ESP_LIBRE_PALABRA "EspLibrePalabra.txt"
#define PATH_BLOQUES_PALABRA "BloquesPalabra.txt"
#define PATH_HASH_PALABRAS "Palabras.txt"

/****************** Hash de Título *********************/
#define TAM_RANURA 64

#define OCUPADA 1
#define VACIA 0

#define PATH_TMP_TITULO "TempTitulo.txt"
#define PATH_TABLA_TITULO "TablaTitulo.txt"
#define PATH_ESP_LIBRE_TITULO "EspLibreTitulo.txt"
#define PATH_BLOQUES_TITULO "BloquesTitulo.txt"
#define PATH_HASH_TITULO "Titulos.txt"

/*********************Testing ***************************/
#define PATH_BLOQUES_TITULO_TEST "BloquesTituloTest"
#define PATH_TMP_TITULO_TEST "TempTituloTest"
#define PATH_TABLA_TITULO_TEST "TablaTituloTest"
#define PATH_ESP_LIBRE_TITULO_TEST "EspLibreTituloTest"
#define PATH_TEST_ARBOL "testArbol"

#endif /* CONSTANTES_H_ */
