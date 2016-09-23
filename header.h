#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define MAX_NOME 51
#define MAX_DESTINO 31

/* estrutura de uma data */
typedef struct
{
    int ano, mes, dia, hora, minu;
}Data;

/* Ponteiro para lista de viagens */
typedef struct Vnode *ListV;

/* Ponteiro para lista de clientes */
typedef struct Cltnode *ListC;

/* Ponteiro para lista de ponteiros para clientes  */
typedef struct Cptrnode *ListCptr;

/* estrutura de um cliente */
typedef struct
{
    int cc;
    char nome[MAX_NOME];
}Cliente;

/* lista simples ligada de Clientes */
typedef struct Cltnode
{
    ListC next;
    Cliente info;
}clt_node;

/* Lista simples de apontadores para clientes */
typedef struct Cptrnode
{
    Cliente *info;
    ListCptr next;
}cptr_node;

/* fila de espera */
typedef struct
{
    ListCptr rear;
    ListCptr first;
} FILA;

/* estrutura de uma viagem */
typedef struct
{
    char destino[MAX_DESTINO];
    Data data;
    int lotac;
    ListCptr lugar;
    FILA espera;
}Viagem;

/* lista duplamente ligada de viagens */
typedef struct Vnode
{
    ListV next;
    ListV prev;
    Viagem info;
}viag_node;

int cliente_compare(int cc1, int cc2);
void Cliente_scan(Cliente *c);
void imprime_cliente(Cliente c);
void imprime_listaC(ListC lista);
ListC destroi_listaC(ListC lista);
void cliente_valor(Cliente *c1, Cliente *c2);
int verifica_Clientelista(ListC lista, Cliente c);
ListC insere_inicio_listaC(ListC lista, Cliente c);
ListC insere_fim_listaC(ListC lista, Cliente c);
ListC find_cliente(ListC lista, int cc);

int data_compare(Data d1, Data d2);
void data_scan(Data *p);
void viagem_scan(Viagem *v);
ListV viagem_return(ListV viagens, int n);
void atribui_valor_data(Data *d1, Data *d2);
void data_print(Data *p);
void atribui_valor_viag(Viagem *v1, Viagem *v2);
void imprime_viagem(Viagem v);
void imprime_listaV(ListV lista);
void imprime_contrario_listaV(ListV lista, int cc);
ListV devolve_inicioV(ListV lista);
ListV insere_ordem_listaV(ListV lista, Viagem x);
ListV destroi_listaV(ListV lista);
ListV find_viagem(ListV viagens, Viagem v);
void imprime_viagens_destino(ListV viagens, char *destino);

ListCptr find_clientePtr(ListCptr lista, int cc);
ListCptr destroi_listaCptr(ListCptr lista);
ListCptr insere_fim_listaCptr(ListCptr lista, Cliente *c);
void imprime_listaCptr(ListCptr lista);
ListCptr elimina_clientePtr(ListCptr lista, Cliente c);
int listaCptr_tamanho(ListCptr lista);

void create_queue(FILA *q);
int empty_queue (FILA *q);
void destroy_queue(FILA *q);
void enqueue(FILA *q, Cliente *c);
Cliente* dequeue(FILA *q);
void imprime_listaEspera(FILA *q);

ListV LoadViagens(ListV Viagens, ListC clientes, char *ficheiro);
ListC LoadClientes(ListC clientes, char *ficheiro);

void escreveViagens(ListV viagens, char *ficheiro);
void escreveClientes(ListC clientes, char *ficheiro);

void clear_input();
void clear_console();
void menu();

#endif
