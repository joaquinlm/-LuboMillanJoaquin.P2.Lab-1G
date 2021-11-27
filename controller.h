#include "pelicula.h"
#include "LinkedList.h"

#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

int controller_loadFromText(char *path, LinkedList *pArrayListFilm);
int controller_loadFromBinary(char *path, LinkedList *pArrayListFilm);
int controller_addFilms(LinkedList *pArrayListFilm, int *nextId);
int controller_editFilms(LinkedList *pArrayListFilm);
int controller_removeFilms(LinkedList *pArrayListFilm);
int controller_ListFilms(LinkedList *pArrayListFilm);
int controller_sortFilms(LinkedList *pArrayListFilm);
int controller_saveAsText(char *path, LinkedList *pArrayListFilm);
int controller_saveAsBinary(char *path, LinkedList *pArrayListFilm);
int controller_buscarMayorId(LinkedList *pArrayListFilm, int *id);
int controller_seleccionarPathCsv(char *pPath);
int controller_seleccionarPathBin(char *pPath);
int controller_findFilmById(LinkedList *pArrayListFilm, int id);
void mostrarCsvsEnDirectorio();
void mostrarBinsEnDirectorio();
LinkedList *controller_filter(LinkedList *pArrayListFilm);
LinkedList *controller_mapRating(LinkedList *pArrayListeMovie);
LinkedList *controller_mapGenre(LinkedList *pArrayListeMovie);
int controller_filterAndSaveBin(LinkedList *pArrayListFilm);
int controller_filterAndSaveTxt(LinkedList *pArrayListFilm);
int controller_ClearLinkedList(LinkedList *pArrayListFilm);

#endif // CONTROLLER_H_INCLUDED
