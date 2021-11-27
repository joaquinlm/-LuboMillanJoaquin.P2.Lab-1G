#include "pelicula.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

eMovie *film_new()
{

  eMovie *newFilm = (eMovie *)malloc(sizeof(eMovie));

  if (newFilm != NULL)
  {
    newFilm->id = 0;
    strcpy(newFilm->nombre, "");
    strcpy(newFilm->genero, "");
    newFilm->ranking = 0;
  }
  return newFilm;
}
eMovie *film_newParametros(char *idStr, char *nombreStr, char *generoStr, char *rankingStr)
{

  eMovie *newFilm = film_new();
  if (newFilm != NULL)
  {
    if ( !(film_setId(newFilm, atoi(idStr)) &&
          film_setNombre(newFilm, nombreStr) &&
          film_setGenero(newFilm, generoStr) &&
          film_setRanking(newFilm, atof(rankingStr))))
    {

      newFilm = NULL;
    }
  }
  return newFilm;
}

int film_setId(eMovie *this, int id)
{
  int todoOk = 0;
  if (this != NULL && id > 0)
  {
    this->id = id;
    todoOk = 1;
  }
  return todoOk;
}

int film_setNombre(eMovie *this, char *nombre)
{
  int todoOk = 0;
  if (this != NULL && nombre != NULL && strlen(nombre) > 0 && strlen(nombre) < 60)
  {
    strcpy(this->nombre, nombre);
    todoOk = 1;
  }
  return todoOk;
}

int film_setGenero(eMovie *this, char* genero)
{
  int todoOk = 0;
  if (this != NULL && genero != NULL && strlen(genero) > 0 && strlen(genero) < 60)
  {
    strcpy(this->genero, genero);
    todoOk = 1;
  }
  return todoOk;
}

int film_setRanking(eMovie *this, float ranking)
{
  int todoOk = 0;
  if (this != NULL && ranking >= 0)
  {
    this->ranking = ranking;
    todoOk = 1;
  }
  return todoOk;
}
int film_getId(eMovie *this, int *id)
{
  int todoOk = 0;
  if (this != NULL && id > 0)
  {
    *id = this->id;
    todoOk = 1;
  }
  return todoOk;
}
int film_getNombre(eMovie *this, char *nombre)
{
  int todoOk = 0;
  if (this != NULL && nombre != NULL)
  {
    strcpy(nombre, this->nombre);
    todoOk = 1;
  }
  return todoOk;
}
int film_getGenero(eMovie *this, char *genero)
{
  int todoOk = 0;
  if (this != NULL && genero != NULL)
  {
    strcpy(genero, this->genero);
    todoOk = 1;
  }
  return todoOk;
}
int film_getRanking(eMovie *this, float *ranking)
{
  int todoOk = 0;
  if (this != NULL && ranking > 0)
  {
    *ranking = this->ranking;
    todoOk = 1;
  }
  return todoOk;
}

/** \brief funcion para mostrar un elemento empleado
 * \param this Employee* puntero a Employe
 * \return todoOk = 1 en caso de exito
 *
 */

void mostrarUnFilm(eMovie *this)
{

  int auxId;
  char auxNombre[50];
  char auxGenero[50];
  float auxRanking;

  if (this != NULL)
  {
    if (film_getId(this, &auxId) && film_getNombre(this, auxNombre) && film_getGenero(this, auxGenero) && film_getRanking(this, &auxRanking))
    {
      printf("%4d  %-40s      %-15s     %.2f  \n", auxId, auxNombre, auxGenero, auxRanking);
    }
  }
}

int compararRanking(void *pFilmUno, void *pFilmdos)
{
  if (((eMovie *)pFilmUno)->ranking > ((eMovie *)pFilmdos)->ranking&& strcmp(((eMovie *)pFilmUno)->genero ,((eMovie *)pFilmdos)->genero)!=0)
  {
    return 1;
  }
  if (((eMovie *)pFilmUno)->ranking < ((eMovie *)pFilmdos)->ranking&&strcmp(((eMovie *)pFilmUno)->genero ,((eMovie *)pFilmdos)->genero)!=0)
  {
    return -1;
  }
  return 0;
}



int filterDrama(void * e)
{
  int todoOk = 0;
  eMovie * emp = NULL;
  if(e !=NULL){
    emp = (eMovie*) e;
    if(strcmp(emp->genero ,"drama")==0){
      todoOk = 1;
    }
  }
return todoOk;
}

int filterComedia(void * e)
{
  int todoOk = 0;
  eMovie * emp = NULL;
  if(e !=NULL){
    emp = (eMovie*) e;
    if(strcmp(emp->genero ,"comedia")==0){
      todoOk = 1;
    }
  }
return todoOk;
}

int filterAccion(void * e)
{
  int todoOk = 0;
  eMovie * emp = NULL;
  if(e !=NULL){
    emp = (eMovie*) e;
    if(strcmp(emp->genero ,"accion")==0){
      todoOk = 1;
    }
  }
return todoOk;
}
int filterTerror(void * e)
{
  int todoOk = 0;
  eMovie * emp = NULL;
  if(e !=NULL){
    emp = (eMovie*) e;
    if(strcmp(emp->genero ,"terror")==0){
      todoOk = 1;
    }
  }
return todoOk;
}

int mapRanking(void * e)
{
  int todoOk = 0;
  eMovie * emp = NULL;
  if(e !=NULL){
    emp = (eMovie*) e;
     
    if((emp->ranking = (float) (rand() % (100 - 10 + 1 ) + 10) / 10)){
     
      todoOk = 1;
    }
  }
  return todoOk;
}

int mapGenero(void * e)
{
  int todoOk = 0;
  eMovie * emp = NULL;
  if(e !=NULL){
    emp = (eMovie*) e;
    int genero = (rand() % (4+ 1 - 1) + 1);    
    switch (genero)
    {
    case 1:
       strcpy(emp->genero, "drama");
      break;
    case 2:;
       strcpy(emp->genero, "comedia");
      break;
    case 3:;
       strcpy(emp->genero, "accion");
      break;
    case 4:;
       strcpy(emp->genero, "terror");
      break;    
    }
      todoOk = 1;
    }  
  return todoOk;
}
