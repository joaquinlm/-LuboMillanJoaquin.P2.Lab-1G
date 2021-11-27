#include <stdlib.h>
#include <stdio.h>
#include "inputsValidados.h"
#include "menus.h"

int imprimirMenuPrincipal()
{
  system("cls");
  int opcion;
  printf("                         ****MENU PRINCIPAL****                             \n\n");
  printf("1. Cargar los datos de los films desde un archivo .csv (modo texto).\n");
  printf("2. Imprimir lista.\n");
  printf("3. Asignar  rating\n");
  printf("4. Asignar genero\n");
  printf("5. Filtrar  por  genero y guardar el subset en un archivo .csv (modo texto)\n");
  printf("6. Ordenar peliculas\n");
  printf("7. Guardar películas\n\n");
  printf("8. Salir\n\n");
  
  opcion = ingresarEnterosRango("Seleccione una opcion\n", "Error. El rango valido de opciones es: 1-15\n", 1, 15);

  return opcion;
}






int imprimirMenuFiltrosTxt()
{
  system("cls");
  printf("                         ****Filtrar y guardar .csv****                             \n\n");
  printf("1-filtrar por genero drama y guardar .csv\n");
  printf("2-filtrar por genero comedia y guardar .csv\n");
  printf("3-filtrar por accion y guardar .csv\n");
  printf("4-filtrar por terror y guardar .csv\n\n");

  printf("5-Cancelar\n");
  int opcion = ingresarEnterosRango("Seleccione una opcion\n", "Error. El rango valido de opciones es: 1-5\n", 1, 5);

  return opcion;
}
