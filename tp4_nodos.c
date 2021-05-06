#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Nodo Nodo;

typedef struct Tarea 
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo{
    struct Tarea T;
    struct Nodo *Siguiente;
} Nodo;

typedef struct Nodo Nodo;

char descrip [6][50] =
{
    "Controlar vencimiento de productos lacteos",
    "Reponer mercaderia en gondola central",
    "Actualizar lista de clientes",
    "Controlar stock de bebidas",
    "Limpiar deposito",
    "Imprimir folletos publicitarios"
};

void CrearListaVacia(Nodo **Lista);
void EstaVacia(Nodo *Lista);
Tarea cargarTarea(int id);
Nodo *crearNodo(Tarea Tarea);
void insertarNodoALista(Nodo **Lista, Nodo *n);
void mostrarTareas (Nodo *Lista);
void *revisarTareasPendientes(Nodo **Lista,Nodo **Lista2);
Nodo * quitarNodoDeLista (Nodo **Lista);



int main ()
{
    srand(time(NULL));
    Nodo *TareasPendientes; CrearListaVacia(&TareasPendientes);
    Nodo *TareasRealizadas; CrearListaVacia(&TareasRealizadas);
    int cantTareasACargar;
    Tarea TAREA;
    //EstaVacia(TareasPendientes);//verificar si la lista esta vacia

    printf("Ingrese cuantas tareas desea cargar: ");
    scanf("%d",&cantTareasACargar);

    for (int i=0;i<cantTareasACargar;i++)
    {
        TAREA = cargarTarea(i+1);
        Nodo *nuevaTarea = crearNodo(TAREA);
        insertarNodoALista(&TareasPendientes,nuevaTarea);
    }
    printf("\nLISTA DE TAREAS: \n");
    //mostrarTareas(TareasPendientes);  
    revisarTareasPendientes(&TareasPendientes,&TareasRealizadas);
    mostrarTareas(TareasRealizadas);



    getchar();
    return 0;
}

void CrearListaVacia(Nodo **Lista)
{
    *Lista = NULL;
}

void EstaVacia(Nodo *Lista)
{
    if(Lista == NULL)
    {
        printf("\nLa lista esta vacia");
    } else {        
        ("\nLa lista no esta vacia");
    }                
}

Tarea cargarTarea(int id)
{
    Tarea T;
    int posicion = rand()%6;
    T.TareaID = id;

    T.Descripcion = (char *)malloc(sizeof(char)*strlen(descrip[posicion]));
    strcpy(T.Descripcion,descrip[posicion]);

    T.Duracion = 10 + rand()%(100+1-10);

    return T;
}

Nodo *crearNodo(Tarea Tarea)
{
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T = Tarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void insertarNodoALista(Nodo **Lista, Nodo *n)
{
    n->Siguiente = *Lista;
    *Lista = n; 
}

void mostrarTareas (Nodo *Lista)
{
    Nodo * nAux = Lista;
    if(nAux != NULL)
    {
        while(nAux != NULL)
        {
            printf("\nTarea ID: %d", Lista->T.TareaID);
            printf("\nDescripcion: %s", Lista->T.Descripcion);
            printf("\nDuracion: %d minutos\n", Lista->T.Duracion);
            nAux = nAux->Siguiente;
        }
    }
}

void *revisarTareasPendientes(Nodo **Lista,Nodo **Lista2)
{
    Nodo * nAux = *Lista;
    char pregunta;
    if(nAux != NULL)
    {
        while(nAux != NULL)
        {
            printf("\nTarea ID: %d", nAux->T.TareaID);
            printf("\nDescripcion: %s", nAux->T.Descripcion);
            printf("\nDuracion: %d minutos\n", nAux->T.Duracion);
            
            printf("Se realizo la tarea correctamente?: ");
            fflush(stdin);
            scanf("%s",pregunta);
            fflush(stdin);

            if (pregunta == 's' || pregunta == 'S'){
                Nodo *nodoRealizado = quitarNodoDeLista(Lista);
                insertarNodoALista(Lista2,nodoRealizado);
            }

            nAux = nAux->Siguiente;
        }
    }    
}

Nodo * quitarNodoDeLista (Nodo **Lista)
{
    Nodo *nAux = *Lista;
    *Lista = (*Lista)->Siguiente;
    nAux->Siguiente = NULL;

    return nAux;    
}