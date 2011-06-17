#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#define ERROR -1
#define OKEY 0
#define BASURA_RLV 33
#define STRING_BUFFER 512
#define STRING_BUFFER_PALABRAS 2000000
#define CUALQUIERA 33000
#define BLOQUE_LLENO 1
#define BLOQUE_NO_LLENO 0
#define REGISTRO_ERRONEO "-1"
#define TIPO_CLAVE_NUMERICA 1

/*********************** TOTAL DOC *************************/
#define PATH_TOTAL_DOCUMENTOS "Total_documentos_Norma.txt"

/***********************Archivo Maestro*********************/
#define PATH_REG_LONG_VARIABLE "ArchivoDeRLV.txt"
#define PATH_ESPACIO_LIBRE_RLV "controlEspaciosLibresRLV.txt"
#define PATH_ARCHIVO_LOG "logBookerio.txt"

/*************Archivo de ocurrencias de terminos***********/
#define PATH_ARCHIVO_OCURRENCIAS "ArchivoOcurrencias.txt"
#define PATH_ESPACIO_LIBRE_OCURRENCIAS "controlEspaciosLibresOcurrencias.txt"

/*************Archivo de Frecuencias ***********************/
#define PATH_ARCHIVO_FREC_GLOB "FrecuenciasGlobales"
#define PATH_ARCHIVO_NORMA "NormasDocumentos"


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
#define CONST_VACIO 0x00
#define PORC_TAMANIO_NODO 50
#define TAM_TOTAL_NODO 256
#define TAM_CONTROL_NODO 24
#define TAM_CONTROL_OVERFLOW 20
#define TAM_EFECTIVO_NODO (TAM_TOTAL_NODO - TAM_CONTROL_NODO)
#define PORCENTAJE_NODO 50
//#define BUFFER_NODOS_LIBRES 256
#define TAM_CONTROL_REGISTRO 10
#define PATH_AUTOR "Autores"
#define PATH_EDITORIAL "Editoriales"
#define PATH_ID_TERMINOS "Terminos"
#define PATH_ID_PESOS "Ids_Pesos_Globales.txt"
#define PATH_IDS "Ids_Terminos.txt"
#define PATH_IDS_BORRAR "No_sirve.txt"

/************************ Hash ************************/
#define TAM_CUBO 4096
#define NOM_TEMP "Temp"

/****************** Hash de Palabra *******************/
#define NOM_TABLA_PALABRA "TablaPalabra"
#define NOM_ESP_LIBRE_PALABRA "EspLibrePalabra"
#define NOM_BLOQUES_PALABRA "BloquesPalabra"
#define NOM_SALIDA_PALABRA "SalidaPalabra"

/****************** Hash de Titulo ********************/
#define NOM_TABLA_TITULO "TablaTitulo"
#define NOM_ESP_LIBRE_TITULO "EspLibreTitulo"
#define NOM_BLOQUES_TITULO "BloquesTitulo"
#define NOM_SALIDA_TITULO "SalidaTitulo"

/******************* Hash de Normas *******************/
#define NOM_BLOQUES_NORMA "BloquesNorma"
#define NOM_ESP_LIBRE_NORMA "EspLibreNorma"
#define NOM_TABLA_NORMA "TablaNorma"
#define NOM_SALIDA_NORMA "SalidaNorma"

/*********************Testing ***************************/
#define PATH_BLOQUES_TITULO_TEST "BloquesTituloTest"
#define PATH_TMP_TITULO_TEST "TempTituloTest"
#define PATH_TABLA_TITULO_TEST "TablaTituloTest"
#define PATH_ESP_LIBRE_TITULO_TEST "EspLibreTituloTest"
#define PATH_TEST_ARBOL "testArbol"

/*******************Consultas *************************/
#define PATH_CONSULTA_EDITORIAL "ConsultaEditorial.txt"
#define PATH_CONSULTA_AUTOR "ConsultaAutor.txt"
#define PATH_CONSULTA_TITULO "ConsultaTitulo.txt"
#define PATH_CONSULTA_PALABRAS "ConsultaPalabras.txt"

#endif /* CONSTANTES_H_ */
