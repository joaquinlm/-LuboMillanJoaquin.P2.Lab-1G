#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "pelicula.h"
#include "menus.h"
#include "parser.h"
// test
/****************************************************
    Menu:
     1. Cargar los datos de los films desde el archivo data.csv (modo texto).
     2. Cargar los datos de los films desde el archivo data.csv (modo binario).
     3. Alta de film
     4. Modificar datos de film
     5. Baja de film
     6. Listar films
     7. Ordenar films
     8. Guardar los datos de los films en el archivo data.csv (modo texto).
     9. Guardar los datos de los films en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/
int main()
{

  srand(time(NULL));
  // int numero = rand() % (max - min +1) +min;

  char path[50];
  char sigue = 's';
  LinkedList *listaFilms = ll_newLinkedList();

  if (listaFilms == NULL)
  {
    printf("No se pudo inicializar correctamente el programa (ll == NULL)");
    system("pause");
    exit(1);
  }
  do
  {
    int option = imprimirMenuPrincipal();
    switch (option)
    {
    case 1:
      if (controller_seleccionarPathCsv(path))
      {
        controller_loadFromText(path, listaFilms);
        //   controller_buscarMayorId(listaFilms, &nextId);
      }
      break;

    case 2:
      if (ll_len(listaFilms) == 0)
      {
        printf("No hay peliculas para mostrar\n");
      }
      else if (listaFilms != NULL)
      {
        controller_ListFilms(listaFilms);
      }
      break;

    case 3:
      if (ll_len(listaFilms) == 0)
      {
        printf("No hay peliculas para setear\n");
      }
      else if (listaFilms != NULL)
      {
        controller_mapRating(listaFilms);
      }
      break;
    case 4:
      if (ll_len(listaFilms) == 0)
      {
        printf("No hay peliculas para setear\n");
      }
      else if (listaFilms != NULL)
      {
        controller_mapGenre(listaFilms);
      }
      break;
    case 5:
      if (ll_len(listaFilms) < 2)
      {
        printf("No hay suficientes films para filtrar\n");
      }
      else
      {
        controller_filterAndSaveTxt(listaFilms);
      }
      break;

    case 6:
      if (ll_len(listaFilms) < 2)
      {
        printf("No hay suficientes films para ordenar\n");
      }
      else
      {
        controller_sortFilms(listaFilms);
      }
      break;

    case 7:

      if (controller_seleccionarPathCsv(path))
      {
        controller_saveAsText(path, listaFilms);
      }
      break;

    case 8:;
      char sale;
      printf("Se perderan los cambios no guardados. Confirma que desea salir? s/n\n");
      fflush(stdin);
      scanf("%c", &sale);
      if (sale != 's')
      {
        printf("Cierre cancelado\n");

        break;
      }
      else
      {
        printf("Ha seleccionado salir.\n");
        sigue = 'n';
        break;
      }
    default:
      printf("Opcion incorrecta\n");

      break;
    }
    fflush(stdin);
    system("pause");
  } while (sigue == 's');

  return 0;
}
