#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"

typedef struct
{
  char name [100];
  char tipo[100];
  char marca[100];
  int stock;
  int precio;
}item;

typedef struct
{
  char nombreCarrito[100];
  int cantidadProductos;
  int ValorTotal;
  List *listaProductos;
}DatosCarro;

int is_equal_string(void * , void * );
const char *get_csv_field (char * , int );
void PedirAgregar(Map*,Map*,Map*);
void Agregar(Map*,Map*,Map*,item*);
void BuscarProductosTipo(Map *);
void BuscarProductosMarca(Map *);
void BuscarProductosName(Map *);
void MostrarProductos(Map *);
void EliminarDelCarro(Map *);
void AgregarAlCarro(Map*,Map*,Map*,Map*);
void ConcretarCompra(Map*,Map *); 
void MostrarCarritos(Map*);
int cantidadProductos(Map*,void *);
void ImportarProductos(Map*,Map*,Map*);
void exportar(Map * );