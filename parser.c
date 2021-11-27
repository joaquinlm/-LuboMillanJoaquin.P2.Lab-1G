#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "pelicula.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListFilm LinkedList*
 * \return int
 *
 */
int parser_FilmFromText(FILE *pFile, LinkedList *pArrayListFilm)
{
  int retorno = 0;
  eMovie *auxFilm = NULL;

  char auxId[20];
  char auxNombre[100];
  char auxGenero[100];
  char auxRanking[20];
  printf("hola\n");
  fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxGenero, auxRanking);
  do
  {
    int cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxGenero, auxRanking);
    if (cant < 4)
    {

      break;
    }

    auxFilm = film_newParametros(auxId, auxNombre, auxGenero, auxRanking);
    if (auxFilm != NULL)
    {
      ll_add(pArrayListFilm, auxFilm);
      retorno = 1;
    }

  } while (!feof(pFile));

  return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListFilm LinkedList*
 * \return int
 *
 */
int parser_FilmFromBinary(FILE *pFile, LinkedList *pArrayListFilm)
{

  int retorno = 0;
  eMovie *auxFilm =NULL;

  fread(auxFilm, sizeof(eMovie), 1, pFile); //lectura fantasma
  if (pArrayListFilm != NULL && pFile != NULL)
  {
    do
    {
      auxFilm = film_new();
      int cant = fread(auxFilm , sizeof(eMovie), 1, pFile);
      if (cant != 1)
      {
        break;
      }

      ll_add(pArrayListFilm, auxFilm);
      auxFilm = NULL;

    } while (!feof(pFile));
    retorno = 1;
  }
  return retorno;
}
