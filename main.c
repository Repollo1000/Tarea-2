#include "list.h"
#include "hashmap.h"
#include "funciones.h"

//Estructura con los datos


int main() 
{
  bool flag = false;
  
  
  Map * MapProductosName = createMap(is_equal_string);
  Map * MapProductosMarca = createMap(is_equal_string);  
  Map * MapProductosTipo = createMap(is_equal_string); 

  Map * MapCarritos = createMap(is_equal_string);
  
  
  int op;
  
  printf("----------MENU----------\n");
  printf("1. Importar productos \n");
  printf("2. Exportar productos \n");
  printf("3. Agregar productos \n");
  printf("4. Buscar productos por tipo \n");
  printf("5. Buscar productos por marca \n");
  printf("6. Buscar productos por nombre  \n");
  printf("7. Mostrar todos los productos \n");
  printf("8. Agregar al carrito  \n");
  printf("9. Eliminar del carrito\n");
  printf("10. Concretar compra \n");
  printf("11. Mostrar carritos de compra \n");
  printf("\n¿Que operación desea realizar?\n");
  scanf("%d", &op);
  
  
  
  while(op > 0 && op < 11)
  {
    
    switch(op)
    {
      case 1 : 
      {
        printf("\nImportar productos\n\n");
        ImportarProductos(MapProductosName, MapProductosMarca, MapProductosTipo);
        break;
      }
      case 2 : 
      {
        printf("Exportar productos\n");
        exportar(MapProductosName);
        break;
      }
      case 3 :
      {
        printf("Agregar Productos\n");
        flag = true;
        PedirAgregar(MapProductosName,MapProductosMarca,MapProductosTipo);
        break;
          
      }
      case 4 :
      {
        printf("Buscar Productos por tipo\n");
        BuscarProductosTipo(MapProductosTipo);
        break;
          
      }
      case 5 :
      {
        printf("Buscar Productos por marca\n");
        BuscarProductosMarca(MapProductosMarca);
        break;
      }
      case 6 :
      {
        printf("Buscar Productos por nombre\n");
        BuscarProductosName(MapProductosName);
        break;
          
      } 
      case 7 :
      {
        printf("Mostrar todos los productos \n");
        MostrarProductos(MapProductosName);
        break;
        
      }
      case 8 : 
      {
        printf("Agregar al Carrito\n");
        AgregarAlCarro(MapCarritos, MapProductosName, MapProductosMarca,MapProductosTipo);
        break;
          
      }
      case 9 : 
      {
        printf("Eliminar de Carrito\n");
        EliminarDelCarro(MapCarritos);   
        break;
      }
      case 10 : 
      {
        printf("Concretar Compra\n");
        ConcretarCompra(MapCarritos,MapProductosName); 
        
        break;
      }
      case 11:
      {
        printf("Mostrar todos los carritos\n");
        MostrarCarritos(MapCarritos);
        break;
      }
    }
    printf("¿Desea realizar otra operación?\n");
    printf("1 -> SI | 2 -> NO\n");
    int rep;
    scanf("%d", &rep);
  
    while(rep != 1 && rep != 2)
    {
      printf("¿Desea realizar otra operación?\n");
      scanf("%d", &rep);  
    }
    
    if(rep == 2) return 0;  
    printf("\n¿Qué operación desea realizar?\n");
    scanf("%d", &op);
  }
}

