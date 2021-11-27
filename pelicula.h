#ifndef PELICULA_H_INCLUDED
#define PELICULA_H_INCLUDED

typedef struct
{
    int id;
    char nombre[128];
    char genero[128];
    float ranking;
}eMovie;

eMovie* film_new();
eMovie* film_newParametros(char* idStr,char* nombreStr,char* generoStr, char* rankingStr);
void film_delete();

int film_setId(eMovie* this,int id);
int film_getId(eMovie* this,int* id);

int film_setNombre(eMovie* this,char* nombre);
int film_getNombre(eMovie* this,char* nombre);

int film_setGenero(eMovie* this,char*genero);
int film_getGenero(eMovie* this,char* genero);

int film_setRanking(eMovie* this,float ranking);
int film_getRanking(eMovie* this,float* ranking);

void mostrarUnFilm(eMovie* this);

int compararRanking(void *pFilmUno, void *pFilmdos);



int filterDrama(void * e);
int filterComedia(void * e);
int filterAccion(void * e);
int filterTerror(void * e);

int mapRanking(void * e);
int mapGenero(void * e);

#endif // PELICULA_H_INCLUDED
