#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

int parser_FilmFromText(FILE* pFile , LinkedList* pArrayListFilm);
int parser_FilmFromBinary(FILE* pFile , LinkedList* pArrayListFilm);

#endif // PARSER_H_INCLUDED
