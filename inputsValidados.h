#ifndef INPUTSVALIDADOS_H_INCLUDED
#define INPUTSVALIDADOS_H_INCLUDED

int imprimirMenu();

int ingresarEnterosRango(char *mensaje, char *mensajeError, int lInf, int lSup);
int ingresarValidarCadena(char *vec, int tam, char mensaje[], char mensajeError[], int minLen, int maxLen);
void ingresarFlotantesRango(float *pInput, char mensaje[], char mensajeError[], float lInf, float lSup);
int checkNum(char vec[]);
void ingresarEnterosRangoToString(char mensaje[], char mensajeError[], int lInf, int lSup, char pChar[]);


#endif // INPUTSVALIDADOS_H_INCLUDED
