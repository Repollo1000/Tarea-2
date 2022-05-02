#include "funciones.h"
#include "hashmap.h"
#include "list.h"

int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

//Funcion que agrega producto manualmente
void PedirAgregar(Map* MapProductosName,Map* MapProductosMarca, Map* MapProductosTipo)
{  
  
  item * producto = (item *)malloc(sizeof(item));
  printf("Ingrese nombre del producto \n");
  getchar();
  scanf("%100[^\n]s", producto->name);
  getchar();
  printf("Ingrese marca del producto \n");
  scanf("%100[^\n]s", producto->marca);
  getchar();
  printf("Ingrese tipo de producto\n");
  scanf("%100[^\n]s", producto->tipo);
  getchar();
  printf("Ingrese stock del producto\n");
  scanf("%d", &producto->stock);
  getchar();
  printf("Ingrese precio del producto \n");
  scanf("%d", &producto->precio);   
  getchar();
  Agregar( MapProductosName, MapProductosMarca, MapProductosTipo,producto);
}
//Funcion que revisa si se debe agregar el producto a los mapas 
// correspondientes
void Agregar(Map* MapProductosName,Map* MapProductosMarca, Map* MapProductosTipo,item* producto )
{
  item * aux = (item *)malloc(sizeof(item));
  aux = (item*)searchMap(MapProductosName, producto->name);

  if(aux == NULL)
  {
    insertMap(MapProductosName,producto->name,producto);
    
    if(searchMap(MapProductosMarca,producto->marca)!=NULL)
    {
    
      pushBack(searchMap(MapProductosMarca,producto->marca),producto);    
    }
    else
    {
      List * listaMarca = createList();
      pushBack(listaMarca,producto);
      insertMap(MapProductosMarca,producto->marca,listaMarca);  
   
    }
    if(searchMap(MapProductosTipo,producto->tipo)!=NULL)
    {
      pushBack(searchMap(MapProductosTipo,producto->tipo),producto);
    }
    else
    {
      List * listaTipo = createList();
      pushBack(listaTipo,producto);
      insertMap(MapProductosTipo,producto->tipo,listaTipo);    
    }   
  }
  else 
  {
    //Ya existe y es la misma marca sumo stock
    if(strcmp(aux->marca, producto->marca) == 0)
    {
      producto->stock = producto->stock + aux->stock;
      //No sabemos como actualizar el mapa con el stock
       aux->stock = producto->stock;
      
    }    
  }   
}

//Se busca productos por el tipo.
void BuscarProductosTipo(Map *MapProductosTipo)
{
  char tipo[100];
  
  printf("¿Que tipo producto desea buscar?\n");
  getchar();
  scanf("%100[^\n]s", tipo);
  getchar();
  
  item * aux = (item *)malloc(sizeof(item));
  List* listaTipo = (List *)searchMap(MapProductosTipo, tipo);
  if (listaTipo == NULL)
  {
    printf("No existe este tipo\n");
  }
  else
  {
    aux = (item *)firstList(listaTipo);
    while(aux != NULL)
    {
      if (strcmp(aux->tipo,tipo)==0)
      {
        printf("%s %s %s %d %d\n", aux->name,aux->tipo,aux->marca,aux->stock,aux->precio);
      }
      aux = (item *)nextList(listaTipo);
    }
  }
}

//Se busca productos por marca.
void BuscarProductosMarca(Map *MapProductosMarca)
{
  item * aux = (item *)malloc(sizeof(item));
  char marca[100];
  
  printf("¿Que marca desea buscar?\n");
  getchar();
  scanf("%100[^\n]s", marca);
  getchar();

  aux = firstMap(MapProductosMarca);
  
  List* listaMarca = (List *)searchMap(MapProductosMarca, marca);
  
  if (listaMarca == NULL)
  {
    printf("No existe este tipo\n");
  }
  else
  {
    aux = (item *)firstList(listaMarca);
    while(aux != NULL)
    {
      if (strcmp(aux->marca,marca)==0)
      {
        printf("%s %s %s %d %d\n", aux->name,aux->tipo,aux->marca,aux->stock,aux->precio);
      
      }
      aux = (item *)nextList(listaMarca);
    }
  }
}

//Se busca productos por el nombre
void BuscarProductosName(Map *MapProductosName)
{
  char name[100];
  
  printf("¿Que nombre de producto desea buscar?\n");
  getchar();
  scanf("%100[^\n]s", name);
  getchar();

  item * aux = (item *)malloc(sizeof(item));
  aux = (item *)firstMap(MapProductosName);
  
  while(aux != NULL)
  {
    if(strcmp(aux->name, name)==0) 
    {
      printf("%s %s %s %d %d\n", aux->name,aux->tipo,aux->marca,aux->stock,aux->precio);
    }
 
    aux = (item *)nextMap(MapProductosName);
  }
}

void MostrarProductos(Map *MapProductosName)
{
  item * aux = (item *)malloc(sizeof(item));
  aux = (item *)firstMap(MapProductosName);
  
  while(aux != NULL)
  {
    printf("%s %s %s %d %d\n", aux->name,aux->tipo,aux->marca,aux->stock,aux->precio);
    
    aux = nextMap(MapProductosName);
  }
}
//zona de carritos
void AgregarAlCarro(Map * MapCarritos,Map *  MapProductosName, Map * MapProductosMarca, Map * MapProductosTipo)
{
  int res = 0;
  char nombreCarrito[100];
  List * aux = createList();
  item * producto = (item *)malloc(sizeof(item));
  item * nuevoProd = (item *)malloc(sizeof(item));
  int cantidad;
  
  while(res != 1)
  {
    char name[100];
    
    printf("Ingrese el nombre de su producto\n");
    getchar();
    scanf("%100[^\n]s", name);
    getchar();   
    producto = (item*)searchMap(MapProductosName,name);  
    
    if (searchMap(MapProductosName,name) != NULL)
    {
        
        printf("El producto se encuentra disponible, ¿cuantos desea agregar?\n");
      
        scanf("%d", &cantidad);
        getchar();
      //si la cantidad que desea agregar esta disponible
        if(producto->stock >= cantidad)
        {
          printf("Ingrese el nombre de su carrito\n");
          scanf("%100[^\n]s", nombreCarrito);
          
          //agregar si el carro ya existe
          if(searchMap(MapCarritos,nombreCarrito) != NULL)
          {
            //se traspasan los datos del producto para insertarlo en la 
            // lista del carro
            strcpy(nuevoProd->name, producto->name);
            strcpy(nuevoProd->marca, producto->marca);
            nuevoProd->precio = producto->precio;
            nuevoProd->stock = cantidad;
            pushBack((searchMap(MapCarritos,nombreCarrito)),nuevoProd);
          }
          else
          {
            //si no existe el carro, se crea y  se traspasan los datos //del producto para insertarlo en este.
            List * listaCarrito = createList();
            
            strcpy(nuevoProd->name, producto->name);
            strcpy(nuevoProd->marca, producto->marca);
            nuevoProd->precio = producto->precio;
            nuevoProd->stock = cantidad;
            pushBack(listaCarrito,nuevoProd);
            insertMap(MapCarritos,strdup(nombreCarrito),listaCarrito);  
           
          }
        }
        else
        {
          printf("Excede el stock disponible\n");
          return;
        
        }
        break;
    }
    else
    {
      printf("Su producto no se encuentra disponible\n");
      
      return;
    }
  }
  
}
  
void MostrarCarritos(Map* MapCarritos)
{   
  char clave[100];
  int totalProductos = 0;
  bool sig = true; 
  int cont = 0;
  List * aux = createList();
  strcpy(clave, firstMapExtension(MapCarritos));
  aux = (List *)firstMap(MapCarritos);
  while(aux != NULL)
  {
    cont++;
    aux = nextMap(MapCarritos);
  }
  
  aux = (List *)firstMap(MapCarritos);
  
  while(sig == true )
  {
    printf("CARRITO : %s\n", clave);
    totalProductos = cantidadProductos(MapCarritos,clave);
    printf("total productos : %d\n", totalProductos);
    if(cont == 1) return;
    if(aux == NULL)
    {
      sig = false;
      break;
    } 
    strcpy(clave, ((char*)nextMapExtension(MapCarritos)));
    aux = nextMap(MapCarritos);
  }
}

//se cuentan la cantidad de productos en el carro
int cantidadProductos(Map* MapCarritos,void *clave)
{
  int cantidad = 0 ;
  item * producto = (item *)malloc(sizeof(item));
  List * ListaNueva = createList();
  ListaNueva  = searchMap(MapCarritos, clave);
  producto = firstList(ListaNueva);
  
  while (producto != NULL)
    {
      cantidad = cantidad + producto->stock;
      producto = nextList(ListaNueva);
    }
  
  return cantidad;
}


void ConcretarCompra(Map *MapCarritos, Map *MapProductosName)
{
  List * aux = createList();
  item * prod = (item *)malloc(sizeof(item));
  item * prod2 = (item *)malloc(sizeof(item));
  int totalApagar = 0;
  char nombreCarrito[100];
  int resp;
  printf("¿En que carro desea concretar su compra?\n");
  getchar();
  scanf("%100[^\n]s", nombreCarrito);//aqui pedir carro
  getchar();
  
  //getchar();
 
  aux = (List* )searchMap(MapCarritos,nombreCarrito);
  if(aux == NULL)
  {
    printf("Lo sentimos, este carro no fue encontrado\n");
    return;
  }
  
  prod = (item *)firstList(aux);
  
  while (prod != NULL)
  {
    totalApagar = totalApagar +  (prod->precio * prod->stock);
    prod = nextList(aux);  
  }
  printf("Su total a pagar es: %d \n", totalApagar);
  printf("¿Desea cancelar el total de su compra?\n");
  printf(" 1 -> SI | 2 -> NO : ");
  scanf("%d",&resp);

  
  if(resp == 2) return;
  if(resp == 1)
  {
    printf("Compra Finalizada\n");
    printf("\nProductos del carro : \n\n");
    prod = (item *)firstList(aux);
  
    
    while (prod != NULL)
    {
      prod2 = searchMap(MapProductosName, prod->name);
      printf("%s %s, valor = %d\n", prod->name, prod->marca, prod->precio);
      //si la compra se lleva a cabo, se elimina de el stock la //cantidad ingresada
      prod2->stock = prod2->stock - prod->stock;
      prod = nextList(aux);  
    }
    printf("Valor total = %d\n", totalApagar);
    //Luego de finalizada la compra, se elimina el carro.
    eraseMap(MapCarritos, nombreCarrito);
    
  }
 
}
void EliminarDelCarro(Map * MapCarritos)
{
  List *aux = createList();
  char nombreCarrito[100];
  char prodEliminar[100];
  item * prod = (item *)malloc(sizeof(item));
  printf("¿En que carro desea eliminar su producto?\n");
  getchar();
  scanf("%100[^\n]s", nombreCarrito);
  getchar();
  aux = (List* )searchMap(MapCarritos,nombreCarrito);
  popBack(aux);
 
}

//importar y exportar
const char *get_csv_field (char * tmp, int k) 
{
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
      ret[i-ini_i] = 0;
      return ret;
    }
    return NULL;
}


void ImportarProductos(Map* MapProductosName,Map* MapProductosMarca, Map* MapProductosTipo)
{
  item * producto = (item *)malloc(sizeof(item));
  item * aux = (item *)malloc(sizeof(item));
  int cont = 0 ;
  int cont2 = 0;
  
  // Se abre el archivo de mundos csv en modo lectura "r"
  FILE *fp = fopen ("Archivo_100productos.csv", "r");

  // Cadena para guardar la linea completa del archivo csv
  char linea[200];
  int i = 0 ;
  bool flag = true;

  //DatosCancion * datos = NULL;
  int k = 0;
  while (fgets (linea, 200, fp) != NULL) // Se lee la linea
  { 
    item * producto = (item *)malloc(sizeof(item));
        while(flag != false)
        { 
          const char* aux = get_csv_field(linea, i); // Se obtiene el nombre
          if (aux == NULL) 
          {
            for(i = 0; i < cont; i++)
            {
              aux = get_csv_field(linea, i); // Se obtiene el nombre
              cont2++;
              switch(cont2)
              {
              
                case 1: strcpy(producto->name,aux);
                case 2: strcpy(producto->marca,aux);
                case 3: strcpy(producto->tipo,aux);
                case 4: producto->stock = atoi(aux);//de cadena a numero
                case 5: producto->precio = atoi(aux);
              }

            }
            Agregar( MapProductosName, MapProductosMarca, MapProductosTipo,producto );
  
            cont2 = 0;
            break;
          }
        i++;
        cont++;
          
        }
    cont = 0;
    i = 0;
    flag = true;
    k++; if(k==100) break;
  }
}

void exportar(Map * MapProductosName)
{
  
  item *aux = (item*) malloc (sizeof(item));
  aux = firstMap(MapProductosName);
  
  char linea[1000];
  
  // Se abre el archivo de mundos csv en modo lectura "r"
  FILE *exportar = fopen ("Productos(2).csv", "w");

  // Cadena para guardar la linea completa del archivo csv
  if(exportar == NULL)
  {
    printf("ERROR\n");
  }
  else
  {
    while(aux != NULL)
    {
      fprintf(exportar,"%s,%s,%s,%d,%d", aux->name,aux->marca,aux->tipo,aux->stock,aux->precio);
      fprintf(exportar,"\n");
      aux = nextMap(MapProductosName);
    }
    
  }
  fclose(exportar);
}

