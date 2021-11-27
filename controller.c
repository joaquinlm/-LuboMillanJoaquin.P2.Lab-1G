#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "pelicula.h"
#include "parser.h"
#include "Controller.h"
#include "inputsValidados.h"
#include "menus.h"
#include <string.h>
#include <dirent.h>

struct dirent *dir;

/** \brief Carga los datos de los peliculas desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char *path, LinkedList *pArrayListeMovie)
{
  int todoOk = 0;
  char confirma;
  FILE *f;

  f = fopen(path, "r");
  if (f == NULL)
  {
    printf("No se pudo abrir el archivo\n");
    if (pArrayListeMovie == NULL)
    {
      printf("null\n");
      system("pause");
    }
  }
  else
  {

    if (ll_len(pArrayListeMovie) > 0)
    {
      printf("Desea sobreescribir los peliculas cargados?");
      fflush(stdin);
      scanf("%1c", &confirma);
    }
    if (confirma == 's' || ll_len(pArrayListeMovie) == 0)
    {
      ll_clear(pArrayListeMovie);
      if (pArrayListeMovie == NULL)
      {
        printf("No se pudo leer la lista de peliculas\n");
      }
      else if (parser_FilmFromText(f, pArrayListeMovie))
      {
        printf("Datos cargados desde el archivo %s\n", path);
        todoOk = 1;
      }
    }
  }
  fclose(f);
  return todoOk;
}
/** \brief Carga los datos de los peliculas desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char *path, LinkedList *pArrayListeMovie)
{
  int todoOk = 0;
  char confirma;
  FILE *f;

  f = fopen(path, "rb");
  if (f == NULL)
  {
    printf("No se pudo abrir el archivo\n");
  }
  else
  {

    if (ll_len(pArrayListeMovie) > 0)
    {
      printf("Desea sobreescribir los peliculas cargados?");
      fflush(stdin);
      scanf("%1c", &confirma);
    }
    if (confirma == 's' || ll_len(pArrayListeMovie) == 0)
    {
      ll_clear(pArrayListeMovie);
      if (pArrayListeMovie == NULL)
      {
        printf("No se pudo leer la lista de peliculas\n");
      }
      else
      {
        if (parser_FilmFromBinary(f, pArrayListeMovie))
        {
          printf("Datos cargados desde el archivo %s\n", path);
          todoOk = 1;
        }
      }
    }
  }
  fclose(f);
  return todoOk;
}

/** \brief Alta de peliculas
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_addFilms(LinkedList *pArrayListeMovie, int *nextId)
{

  int todoOk = 0;
  eMovie *auxeMovie = NULL;
  char strAuxId[20];
  char auxNombre[20];
  char strAuxGenero[20];
  char strauxRanking[20];
  if (pArrayListeMovie != NULL)
  {
    controller_buscarMayorId(pArrayListeMovie, nextId);
    sprintf(strAuxId, "%d", *nextId);

    printf("           ***ALTA DE Pelicula***\n\n");
    ingresarValidarCadena(auxNombre, 20, "Ingrese el nombre: ", "Error. Reingrese el nombre (solo caracteres alfabeticos o espacios)\n", 3, 20);
    ingresarValidarCadena(strAuxGenero, 20, "Ingrese el genero: ", "Error. Reingrese el nombre (solo caracteres alfabeticos o espacios)\n", 3, 20);
    ingresarEnterosRangoToString("Ingrese el ranking: ", "Error\n", 1, 500000, strauxRanking);

    auxeMovie = film_newParametros(strAuxId, auxNombre, strAuxGenero, strauxRanking);

    if (auxeMovie != NULL)
    {
      ll_add(pArrayListeMovie, auxeMovie);
      todoOk = 1;
    }
    else
    {
      printf("No se pudo dar de alta\n");
    }
  }

  return todoOk;
}

/** \brief Listar peliculas
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_ListFilms(LinkedList *pArrayListeMovie)
{
  int retorno = -1;
  eMovie *auxeMoviePuntero = NULL;
  if (pArrayListeMovie != NULL)
  {
    system("cls");
    printf("           ***Listado de peliculas***\n");
    printf("  ID                               Nombre                 Genero    Ranking \n");
    for (int i = 0; i < ll_len(pArrayListeMovie); i++)
    {
      auxeMoviePuntero = (eMovie *)ll_get(pArrayListeMovie, i);
      mostrarUnFilm(auxeMoviePuntero);
      auxeMoviePuntero = NULL;
    }
    printf("\n");
    retorno = 0;
  }
  return retorno;
}

/** \brief Ordenar peliculas
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_sortFilms(LinkedList *pArrayListeMovie)
{
  int todoOk = 0;

  if (pArrayListeMovie != NULL)
  {

    ll_sort(pArrayListeMovie, compararRanking, 1);

    todoOk = 1;
  }

  return todoOk;
}

/** \brief Guarda los datos de los peliculas en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char *path, LinkedList *pArrayListeMovie)
{
  int todoOk = 0;
  char confirma;
  eMovie *auxeMovie = NULL;
  FILE *f;

  if (pArrayListeMovie != NULL)
  {
    if ((f = fopen(path, "r")))
    {
      fclose(f); // cierro el archivo que se abrio al evaluar en el  if
      printf("El archivo ya existe. Desea sobreescribirlo?\n");
      fflush(stdin);
      scanf("%1c", &confirma);
      printf("%c confirmaste", confirma);
    }

    if (!(f = fopen(path, "r")) || confirma == 's')
    {
      fclose(f); // cierro el archivo que se abrio al evaluar en el  if
      f = fopen(path, "w");
      if (f == NULL)
      {
        printf("No se pudo abrir el archivo\n");
        if (pArrayListeMovie == NULL)
        {
          printf("No se pudo cargar la lista de peliculas\n");
          system("pause");
        }
      }
      else
      {
        fprintf(f, "id,nombre,genero,ranking\n");
        for (int i = 0; i < ll_len(pArrayListeMovie); i++)
        {
          auxeMovie = ll_get(pArrayListeMovie, i);
          if (auxeMovie != NULL)
          {
            fprintf(f, "%d,%s,%s,%f\n", auxeMovie->id, auxeMovie->nombre, auxeMovie->genero, auxeMovie->ranking);
            auxeMovie = NULL;
          }
        }
        printf("Se guardaron los datos en el archivo %s\n", path);
      }
      fclose(f);
      todoOk = 1;
    }
  }
  return todoOk;
}

/** \brief Guarda los datos de los peliculas en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListeMovie LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char *path, LinkedList *pArrayListeMovie)
{
  int todoOk = 0;
  char confirma;
  eMovie *auxeMovie;
  FILE *f;
  if (path != NULL && pArrayListeMovie != NULL)
  {
    if ((f = fopen(path, "rb")))
    {
      fclose(f); // cierro el archivo que se abrio al evaluar en el if
      printf("El archivo ya existe. Desea sobreescribirlo?\n");
      fflush(stdin);
      scanf("%1c", &confirma);
    }

    if (!(f = fopen(path, "rb")) || confirma == 's')
    {
      fclose(f); // cierro el archivo que se abrio al evaluar en el  if
      f = fopen(path, "wb");
      if (f == NULL)
      {
        printf("No se pudo abrir el archivo\n");
        if (pArrayListeMovie == NULL)
        {
          printf("No se pudo cargar la lista de peliculas\n");
          system("pause");
        }
      }
      else
      {
        for (int i = 0; i < ll_len(pArrayListeMovie); i++)
        {
          auxeMovie = ll_get(pArrayListeMovie, i);
          if (auxeMovie != NULL)
          {
            fwrite(auxeMovie, sizeof(eMovie), 1, f);
            auxeMovie = NULL;
          }
          /* code */
        }
        printf("Se guardaron los datos en el archivo %s\n", path);
      }
    }
    fclose(f);
    todoOk = 1;
  }
  return todoOk;
}

/** \brief Busca el id mas alto
 *
 * \param pArrayListeMovie LinkedList*
 * \param id int*
 * \return int
 *
 */
int controller_buscarMayorId(LinkedList *pArrayListeMovie, int *id)
{
  int retorno = -1;
  eMovie *auxeMoviePuntero = NULL;
  int idMayor = *id;
  if (pArrayListeMovie != NULL)
  {
    if (ll_len(pArrayListeMovie) == 0)
    {
      *id = *id;
    }
    else
    {
      for (int i = 0; i < ll_len(pArrayListeMovie); i++)
      {

        auxeMoviePuntero = (eMovie *)ll_get(pArrayListeMovie, i);
        if (auxeMoviePuntero->id > idMayor)
        {
          idMayor = auxeMoviePuntero->id;
        }
      }
      *id = idMayor + 1;
    }
    retorno = 1;
  }
  return retorno;
}
/** \brief funcion para cargar la cadena que se pasa como parametro a las funciones de apertura de archivo.
 * Verifica que la extension de archivo solo pueda ser .csv
 * \param pPath char*
 * \return todoOk = 1 en caso de exito
 *
 */

int controller_seleccionarPathCsv(char *pPath)
{
  int todoOk = 0;

  if (pPath != NULL)
  {
    char auxExt[4];
    mostrarCsvsEnDirectorio();
    printf("Ingrese el nombre de archivo: ");
    fflush(stdin);
    scanf("%20[a-zA-Z0-9]%[.csv]", pPath, auxExt);
    if (strcmp(auxExt, ".csv") != 0)
    {
      printf("extension de archivo incorrecta. Solo se admiten archivos .csv\n");
    }
    else
    {
      strcat(pPath, auxExt);
      todoOk = 1;
    }
  }
  return todoOk;
}
/** \brief funcion para cargar la cadena que se pasa como parametro a las funciones de apertura de archivo.
 * Verifica que la extension de archivo solo pueda ser .bin
 * \param pPath char*
 * \return todoOk = 1 en caso de exito
 *
 */

int controller_seleccionarPathBin(char *pPath)
{
  int todoOk = 0;
  mostrarBinsEnDirectorio();
  if (pPath != NULL)
  {
    printf("Ingrese el nombre de archivo: ");
    fflush(stdin);
    char auxExt[4];
    scanf("%20[a-zA-Z0-9]%[.bin]", pPath, auxExt);
    if (strcmp(auxExt, ".bin") != 0)
    {
      printf("extension de archivo incorrecta. Solo se admiten archivos .bin\n");
    }
    else
    {
      strcat(pPath, auxExt);
      todoOk = 1;
    }
  }
  return todoOk;
}

/** \brief busca un nodo de la linked list usando como criterio de busqueda el Id
 *
 * \param id id
 * \param pArrayListeMovie LinkedList*
 * \return index int indice del nodo que coincide con la busqueda en el caso de encontrarlo o -1 en caso
 *  contrario
 *
 */
int controller_findFilmById(LinkedList *pArrayListeMovie, int id)
{
  int index = -1;
  int idCheck;
  eMovie *auxeMovie = NULL;
  if (pArrayListeMovie != NULL)
  {

    for (int i = 0; i < ll_len(pArrayListeMovie); i++)
    {
      auxeMovie = ll_get(pArrayListeMovie, i);
      film_getId(auxeMovie, &idCheck);

      if (auxeMovie != NULL && idCheck == id)
      {
        index = i;
        break;
      }
    }
    if (index == -1)
    {
      printf("No se encontro el ID\n");
    }
  }
  return index;
}

void mostrarCsvsEnDirectorio()
{
  char pPath[100];
  char auxExt[20];
  DIR *dr = opendir(".");

  if (dr == NULL)
  {
    printf("No se pudo leer la carpeta\n");
  }
  int contador = 0;
  while ((dir = readdir(dr)) != NULL)
  {
    sscanf(dir->d_name, "%[a-zA-Z0-9]%[.csv]", pPath, auxExt);
    if (strcmp(auxExt, ".csv") == 0)
    {
      printf("%s\n", dir->d_name);
      contador++;
    }
  }
  if (!contador)
  {
    printf("No se encontraron archivos de ese tipo en la carpeta\n");
  }
  closedir(dr);
}

void mostrarBinsEnDirectorio()

{

  char pPath[100];
  char auxExt[20];
  DIR *dr = opendir(".");

  if (dr == NULL)
  {
    printf("No se pudo leer la carpeta\n");
  }
  int contador = 0;
  while ((dir = readdir(dr)) != NULL)
  {
    sscanf(dir->d_name, "%[a-zA-Z0-9]%[.bin]", pPath, auxExt);
    if (strcmp(auxExt, ".bin") == 0)
    {
      printf("%s\n", dir->d_name);
      contador++;
    }
  }
  if (!contador)
  {
    printf("No se encontraron archivos de ese tipo en la carpeta\n");
  }
  closedir(dr);
}



int controller_filterAndSaveTxt(LinkedList *pArrayListeMovie)
{
  int todoOk = 0;
  LinkedList *aux = NULL;
  aux = ll_clone(pArrayListeMovie);
  int opcion = imprimirMenuFiltrosTxt();
  if (pArrayListeMovie != NULL && aux != NULL)
  {
    if (opcion != 7)
    {
      switch (opcion)
      {

      case 1:
        aux = ll_filter(pArrayListeMovie, filterDrama);
        controller_saveAsText("drama.csv", aux);
        break;

      case 2:
        aux = ll_filter(pArrayListeMovie, filterComedia);
        controller_saveAsText("comedia.csv", aux);
        break;

      case 3:
        aux = ll_filter(pArrayListeMovie, filterAccion);
        controller_saveAsText("accion.csv", aux);
        break;

      case 4:
        aux = ll_filter(pArrayListeMovie, filterTerror);
        controller_saveAsText("terror.csv", aux);
        break;
      
      }
    }
    todoOk = 1;
    ll_deleteLinkedList(aux);
  }
  return todoOk;
}

int controller_ClearLinkedList(LinkedList *pArrayListeMovie)
{
  int todoOk = 0;
  char confirma;

  if (pArrayListeMovie != NULL)

  {
    printf("Se borraran todos los datos de la lista, esta operacion no se puede deshacer. Confirma?\n");
    fflush(stdin);
    scanf("%1c", &confirma);
    if (confirma == 's')
    {
      todoOk = ll_clear(pArrayListeMovie);
    }
  }

  return todoOk;
}

LinkedList *controller_mapRating(LinkedList *pArrayListeMovie)
{
  LinkedList *aux = NULL;

  if (pArrayListeMovie != NULL)
  {
    aux = ll_map(pArrayListeMovie, (void *)mapRanking);
    controller_ListFilms(pArrayListeMovie);
  }
  return aux;
}
LinkedList *controller_mapGenre(LinkedList *pArrayListeMovie)
{
  LinkedList *aux = NULL;

  if (pArrayListeMovie != NULL)
  {
    aux = ll_map(pArrayListeMovie, (void *)mapGenero);
    controller_ListFilms(pArrayListeMovie);
  }
  return aux;
}
