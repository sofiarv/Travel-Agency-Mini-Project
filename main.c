#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    ListV viagens, viagem, aux;
    ListC clientes, cliente_aux;
    ListCptr clt;
    Viagem v;
    int cc;
    int opc;
    int n;

    viagens = NULL;
    clientes = NULL;
    clientes = LoadClientes(clientes, "/home/alex/Documents/FicheirosTexto/Projeto/Clientes");
    viagens = LoadViagens(viagens, clientes, "/home/alex/Documents/FicheirosTexto/Projeto/Viagens");

    do{
        menu();
        scanf("%d", &opc);
        clear_input();
        clear_console();
        printf("Opcao: %d\n\n", opc);
        cliente_aux = NULL;
        clt = NULL;
        viagem = NULL;
        if(opc >= 0 && opc <= 6)
        {
            switch(opc)
            {
                case 0:
                printf("A Terminar...");
                escreveClientes(clientes, "/home/alex/Documents/FicheirosTexto/Projeto/Clientes");
                clientes = destroi_listaC(clientes);
                viagens = destroi_listaV(viagens);
                return 0;

                case 1:
                if(viagens != NULL)
                {
                    imprime_listaV(viagens);
                    printf("Numero da viagem: ");
                    scanf("%d", &n);
                    clear_console();
                    clear_input();
                    viagem = viagem_return(viagens, n);
                    if(viagem != NULL)
                    {
                        imprime_listaC(clientes);
                        printf("cc a adicionar: ");
                        scanf(" %d", &cc);
                        clear_console();
                        cliente_aux = find_cliente(clientes, cc);
                        if(cliente_aux != NULL  && find_clientePtr(viagem->info.lugar, cc) == NULL && find_clientePtr(viagem->info.espera.first, cc) == NULL)
                        {
                            if(listaCptr_tamanho(viagem->info.lugar) < viagem->info.lotac)
                            {
                                viagem->info.lugar = insere_fim_listaCptr(viagem->info.lugar, &cliente_aux->info);
                                printf("Viagem adquirida com sucesso!\n");
                            }
                            else
                            {
                                printf("Lotacao esgotada!\nAdicionar a lista de espera?(Pressione 1 para adicionar)");
                                scanf("%d", &opc);
                                if(opc == 1)
                                {
                                    enqueue(&viagem->info.espera, &cliente_aux->info);
                                    printf("Cliente colocado em lista de espera com sucesso!\n\n");
                                }
                            }

                            escreveViagens(viagens, "/home/alex/Documents/FicheirosTexto/Projeto/Viagens");
                        }
                        else printf("ERRO!!! Cliente nao existe ou ja adquiriu/espera a viagem!\n");
                    }
                    else printf("ERRO!!!Viagem nao existe!\n");
                }
                else printf("ERRO!!! Lista de Viagens vazia!\n");
                break;

                case 2:
                if(viagens != NULL)
                {
                    imprime_listaV(viagens);
                    printf("Numero da viagem: ");
                    scanf("%d", &n);
                    clear_console();
                    clear_input();
                    viagem = viagem_return(viagens, n);
                    if(viagem != NULL)
                    {
                        imprime_listaCptr(viagem->info.lugar);
                        printf("cc a remover: ");
                        scanf(" %d", &cc);
                        clear_console();
                        clt = find_clientePtr(viagem->info.lugar, cc);
                        if(clt != NULL)
                        {
                            viagem->info.lugar = elimina_clientePtr(viagem->info.lugar, *clt->info);
                            printf("Viagem cancelada com sucesso!\n");
                            if(empty_queue(&viagem->info.espera) == 0)
                                viagem->info.lugar = insere_fim_listaCptr(viagem->info.lugar, dequeue(&viagem->info.espera));
                            escreveViagens(viagens, "/home/alex/Documents/FicheirosTexto/Projeto/Viagens");
                        }
                        else printf("ERRO!!!Cliente nao existe!\n");
                    }
                    else printf("ERRO!!!Viagem nao existe!\n");
                }
                else printf("ERRO!!! Lista de Viagens vazia!\n");
                break;

                case 3:
                if(viagens != NULL)
                {
                    imprime_listaV(viagens);
                    printf("Numero da viagem: ");
                    scanf("%d", &n);
                    clear_console();
                    clear_input();
                    viagem = viagem_return(viagens, n);
                    if(viagem != NULL)
                    {
                        imprime_listaEspera(&viagem->info.espera);
                        printf("cc a remover: ");
                        scanf(" %d", &cc);
                        clear_console();
                        clt = find_clientePtr(viagem->info.espera.first, cc);
                        if(clt != NULL)
                        {
                            viagem->info.espera.first = elimina_clientePtr(viagem->info.espera.first, *clt->info);
                            printf("Cliente retirado de fila de espera com sucesso!\n\n");
                            escreveViagens(viagens, "/home/alex/Documents/FicheirosTexto/Projeto/Viagens");
                        }
                        else printf("ERRO!!!Cliente nao existe!\n");

                    }
                    else printf("ERRO!!!Viagem nao existe!\n");
                }
                else printf("ERRO!!! Lista de Viagens vazia!\n");
                break;

                case 4:
                printf("Destino: ");
                fgets(v.destino, MAX_DESTINO, stdin);
                clear_console();
                imprime_viagens_destino(viagens, v.destino);
                break;

                case 5:
                aux = viagens;
                while(aux != NULL)
                {
                    clt = aux->info.lugar;
                    while(clt != NULL)
                    {
                        if(find_cliente(cliente_aux, clt->info->cc) == NULL)
                            cliente_aux = insere_fim_listaC(cliente_aux, *clt->info);
                        clt = clt->next;
                    }
                    clt = aux->info.espera.first;
                    while(clt != NULL)
                    {
                        if(find_cliente(cliente_aux, clt->info->cc) == NULL)
                            cliente_aux = insere_fim_listaC(cliente_aux, *clt->info);
                        clt = clt->next;
                    }
                    aux = aux->next;
                }
                imprime_listaC(cliente_aux);
                destroi_listaC(cliente_aux);
                break;

                case 6:
                imprime_listaC(clientes);
                printf("cc a imprimir: ");
                scanf("%d", &cc);
                imprime_contrario_listaV(viagens, cc);
                break;

                default:
                printf("ERRO! Por favor, selecione uma opcao valida!\n");
            }
        }
    }while(1);


    return 0;
}


int cliente_compare(int cc1, int cc2)
{
    if(cc1 == cc2)
        return 1;
    return 0;
}

void imprime_cliente(Cliente c)
{
    printf("Nome: %scc: %d\n", c.nome, c.cc);
}

void imprime_listaC(ListC lista)
{
    ListC p;
    p = lista;
    while(p != NULL)
    {
        imprime_cliente(p->info);
        p = p->next;
    }
    printf("\n");
}

ListC destroi_listaC(ListC lista)
{
    ListC p;
    if(lista != NULL)
    {
        while(lista->next != NULL)
        {
            p = lista;
            lista = lista->next;
            free(p);
        }
        free(lista);
    }
    return NULL;
}

void cliente_valor(Cliente *c1, Cliente *c2)
{
    strcpy(c1->nome, c2->nome);
    c1->cc = c2->cc;
}

int verifica_Clientelista(ListC lista, Cliente c)
{
    ListC aux;
    aux = lista;
    while(aux != NULL && aux->info.cc != c.cc)
        aux = aux->next;
    if(aux == NULL)
        return 0;
    else return 1;
}

ListC insere_fim_listaC(ListC lista, Cliente c)
{
    ListC p, aux;
    if(verifica_Clientelista(lista, c) == 1)
        return lista;
    p = (ListC)malloc(sizeof(clt_node));
    aux = lista;
    if(p != NULL)
    {
        cliente_valor(&p->info, &c);
        p->next = NULL;
        if(aux == NULL)
            return p;
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = p;
    }
    return lista;
}

ListCptr find_clientePtr(ListCptr lista, int cc)
{
    ListCptr aux;
    aux = lista;

    while(aux != NULL && cliente_compare(cc, aux->info->cc) != 1)
        aux = aux->next;
    if(aux != NULL)
        return aux;
    return NULL;
}

ListC find_cliente(ListC lista, int cc)
{
    ListC aux;
    aux = lista;

    while(aux != NULL && cliente_compare(cc, aux->info.cc) != 1)
        aux = aux->next;
    if(aux != NULL)
        return aux;
    return NULL;
}


/* retorna -1 se a primeira data for menor do que a segunda, 1 se a primeira for maior do que a segunda ou 0 se forem iguais */
int data_compare(Data d1, Data d2)
{
    if(d1.ano < d2.ano)
        return -1;
    else if(d1.ano > d2.ano)
        return 1;
    else
    {
        if(d1.mes < d2.mes)
            return -1;
        else if(d1.mes > d2.mes)
            return 1;
        else
        {
            if(d1.dia < d2.dia)
                return -1;
            else if(d1.dia > d2.dia)
                return 1;
            else
            {
                if(d1.hora < d2.hora)
                    return -1;
                else if(d1.hora > d2.hora)
                    return 1;
                else
                {
                    if(d1.minu < d2.minu)
                        return -1;
                    else if(d1.minu > d2.minu)
                        return 1;
                    else
                        return 0;
                }
            }
        }
    }
}

ListV find_viagem(ListV viagens, Viagem v)
{
    ListV aux;
    aux = viagens;

    while(aux != NULL)
    {
        if(data_compare(v.data, aux->info.data) == 0 && strcmp(aux->info.destino, v.destino) == 0)
            return aux;
        aux = aux->next;
    }
    return NULL;
}

void data_scan(Data *p)
{
    scanf(" %d %d %d %d %d", &p->hora, &p->minu, &(p->dia), &(p->mes), &(p->ano));
}

void viagem_scan(Viagem *v)
{
    printf("Destino: ");
    fgets(v->destino, MAX_DESTINO, stdin);
    printf("Data: ");
    data_scan(&(v->data));
    clear_input();
}

ListV viagem_return(ListV viagens, int n)
{
    ListV aux; int i;
    i = 1;
    aux = viagens;
    while(aux != NULL && i < n)
    {
        aux = aux->next;
        i++;
    }
    if(n == i)
        return aux;
    else
        return NULL;

}


/* copia os valores de uma struct Data para outra */
void atribui_valor_data(Data *d1, Data *d2)
{
    d1->ano = d2->ano;
    d1->mes = d2->mes;
    d1->dia = d2->dia;
    d1->hora = d2->hora;
    d1->minu = d2->minu;
}

void imprime_data(Data p)
{
    printf("%.2d:%.2d-%.2d/%.2d/%d\n", p.hora, p.minu, p.dia, p.mes, p.ano);
}

/* copia os valores de uma struct Viagem para outra */
void atribui_valor_viag(Viagem *v1, Viagem *v2)
{
    strcpy(v1->destino, v2->destino);
    atribui_valor_data(&(v1->data), &(v2->data));
    v1->lotac = v2->lotac;
    v1->lugar = v2->lugar;
    v1->espera = v2->espera;
}

void imprime_viagem(Viagem v)
{
    printf("----------------------\nDestino: %sData: ", v.destino);
    imprime_data(v.data);
    printf("Lotacao: %d\n\n", v.lotac);
    printf("Lugares: \n");
    imprime_listaCptr(v.lugar);
    printf("Espera: \n");
    imprime_listaEspera(&v.espera);
}

void imprime_listaV(ListV lista)
{
    ListV p;
    int i;
    i = 1;
    p = lista;
    while(p != NULL)
    {
        printf("-------Viagem %d------\n", i++);
        imprime_viagem(p->info);
        p = p->next;
        printf("\n");
    }
}

void imprime_contrario_listaV(ListV lista, int cc)
{
    ListV aux;
    ListCptr clt;
    int flag;
    flag = 0;
    aux = lista;
    if(aux != NULL)
    {
        while(aux->next != NULL)
            aux = aux->next;
        while(aux != NULL)
        {
            clt = find_clientePtr(aux->info.lugar, cc);
            if(clt != NULL)
            {
                flag = 1;
                imprime_viagem(aux->info);
            }
            clt = find_clientePtr(aux->info.espera.first, cc);
            if(clt != NULL)
            {
                flag = 1;
                imprime_viagem(aux->info);
            }
            aux = aux->prev;
        }
        printf("\n");
        if(flag == 0)
            printf("Este cliente nao tem viagens adquiridas nem em espera.\n\n");
    }
}

/* devolve o endereço do primeiro no de uma lista duplamente ligadas */
ListV devolve_inicioV(ListV lista)
{
    if(lista != NULL)
        while(lista->prev != NULL)
            lista = lista->prev;
    return lista;
}

ListV insere_ordem_listaV(ListV lista, Viagem x)
{
    ListV p, atual, ant;
    p = (ListV)malloc(sizeof(viag_node));

    if(p != NULL)
    {
        atribui_valor_viag(&(p->info), &x);
        p->next = NULL;
        p->prev = NULL;
        if(lista == NULL)
            return p;
        atual = lista;
        ant = NULL;
        while(atual != NULL && data_compare(x.data, atual->info.data) == 1) /* função para comparar datas */
        {
            ant = atual;
            atual = atual->next;
        }
        p->prev = ant;
        p->next = atual;
        if(atual != NULL)
                atual->prev = p;
        if(ant != NULL)
            ant->next = p;
    }
    return devolve_inicioV(lista);
}

ListV destroi_listaV(ListV lista)
{
    ListV p;
    if(lista != NULL)
    {
        while(lista->next != NULL)
        {
            p = lista;
            lista = lista->next;
            destroy_queue(&p->info.espera);
            destroi_listaCptr(p->info.lugar);
            free(p);
        }
        destroy_queue(&lista->info.espera);
        destroi_listaCptr(lista->info.lugar);
        free(lista);
    }
    return NULL;
}

int listaCptr_tamanho(ListCptr lista)
{
    ListCptr aux;
    int i;
    i = 0;
    aux = lista;
    while(aux != NULL)
    {
        i++;
        aux = aux->next;
    }
    return i;
}

ListCptr destroi_listaCptr(ListCptr lista)
{
    ListCptr p;
    if(lista != NULL)
    {
        while(lista->next != NULL)
        {
            p = lista;
            lista = lista->next;
            free(p);
        }
        free(lista);
    }
    return NULL;
}

ListCptr insere_fim_listaCptr(ListCptr lista, Cliente *c)
{
    ListCptr p, aux;
    p = (ListCptr)malloc(sizeof(cptr_node));
    aux = lista;
    if(p != NULL)
    {
        p->info = c;
        p->next = NULL;
        if(aux == NULL)
            return p;
        while(aux->next != NULL)
            aux = aux->next;
        aux->next = p;
    }
    return lista;
}

void imprime_listaCptr(ListCptr lista)
{
    ListCptr p;
    p = lista;
    while(p != NULL)
    {
        imprime_cliente(*p->info);
        p = p->next;
    }
    printf("\n");
}

ListCptr elimina_clientePtr(ListCptr lista, Cliente c)
{
    ListCptr aux, ant;
    aux = lista;
    ant = NULL;
    while(aux != NULL && cliente_compare(c.cc, aux->info->cc) != 1)
    {
        ant = aux;
        aux = aux->next;
    }
    if(aux != NULL && lista == aux)
    {
        ant = aux->next;
        free(aux);
        return ant;
    }
    else if(aux != NULL && ant != NULL)
    {
        ant->next = aux->next;
        free(aux);
    }
    return lista;
}

/* função para limpar o stdin (input) equivalente a fflush(stdin) */
void clear_input()
{
    char c;
    do{
        scanf("%c", &c);
    }while (c != '\n' && c != EOF);
}

void clear_console()
{
    system("clear"); /* comando para limpar a consola */
}

void menu()
{
    printf("Por favor, escolha uma opcao (0-6): ");
    printf("\n 1 -> Adquirir uma viagem\n");
    printf(" 2 -> Cancelar uma viagem\n");
    printf(" 3 -> Cancelar pedido de viagem\n");
    printf(" 4 -> Visualizar todas as viagens de um determinado destino\n");
    printf(" 5 -> Visualizar todos os clientes com viagens adquiridas ou em espera\n");
    printf(" 6 -> Visualizar todas as viagens de um determinado cliente\n");
    printf(" 0 -> SAIR\n");
}

ListV LoadViagens(ListV Viagens, ListC clientes, char *ficheiro)
{
    FILE *f;
    Viagem v;
    ListC clt;
    char temp[MAX_DESTINO];
    int cc;
    f = fopen(ficheiro, "r");
    if(f != NULL)
    {
        while(fgets(temp, MAX_DESTINO, f) != NULL)
        {
            if(strcmp(temp, "VIAGEM\n") == 0)
            {
                fgets(v.destino, MAX_DESTINO, f);
                fscanf(f, "%d:%d-%d/%d/%d*%d\n", &v.data.hora, &v.data.minu, &v.data.dia, &v.data.mes, &v.data.ano, &v.lotac);
                fgets(temp, MAX_DESTINO, f);
                v.lugar = NULL;
                do{
                    fgets(temp, MAX_DESTINO, f);
                    cc = atoi(temp);
                    clt = find_cliente(clientes, cc);
                    if(clt != NULL)
                        v.lugar = insere_fim_listaCptr(v.lugar, &clt->info);
                }while(cc != 0);
                create_queue(&v.espera);

                do{
                    fgets(temp, MAX_DESTINO, f);
                    cc = atoi(temp);
                    clt = find_cliente(clientes, cc);
                    if(clt != NULL)
                        enqueue(&v.espera, &clt->info);
                }while(cc != 0);

                Viagens = insere_ordem_listaV(Viagens, v);
            }
        }
        fclose(f);
    }
    return Viagens;
}

ListC LoadClientes(ListC clientes, char *ficheiro)
{
    FILE *f;
    Cliente c;
    f = fopen(ficheiro, "r");
    if(f != NULL)
    {
        while(fgets(c.nome, MAX_NOME, f) != NULL)
        {
            fscanf(f, "%d", &c.cc);
            clientes = insere_fim_listaC(clientes, c);
        }
        fclose(f);
    }
    return clientes;
}

void create_queue(FILA *q)
{
    q->first = NULL;
    q->rear = NULL;
}

int empty_queue (FILA *q)
{
    return (q->first == NULL ? 1 : 0);
}

void destroy_queue(FILA *q)
{
    ListCptr temp;
    while(empty_queue(q) == 0)
    {
        temp = q->first;
        q->first = q->first->next;
        free(temp);
    }
    q->rear = NULL;
}

void enqueue(FILA *q, Cliente *c)
{
    ListCptr temp;
    temp = (ListCptr)malloc(sizeof(cptr_node));
    if (temp != NULL)
    {
        temp->info = c;
        temp->next = NULL;
        if (empty_queue(q) == 1)
            q->first = temp;
        else q->rear->next = temp;
        q->rear = temp;
    }
}

Cliente* dequeue(FILA *q)
{
    ListCptr temp_ptr;
    Cliente *c;
    if (empty_queue(q) == 0)
    {
        temp_ptr = q->first;
        c = temp_ptr->info;
        q->first = q->first->next;
        if (empty_queue(q) == 1)
            q->rear = NULL;
        free(temp_ptr);
        return c;
    }
    return NULL;
}

void imprime_listaEspera(FILA *q)
{
    ListCptr temp;
    temp = q->first;
    while(temp != NULL)
    {
        imprime_cliente(*temp->info);
        temp = temp->next;
    }
    printf("\n");
}

void imprime_viagens_destino(ListV viagens, char *destino)
{
    ListV aux;
    int flag;
    aux = viagens;
    flag = 0;
    while(aux != NULL)
    {
        if(strcmp(aux->info.destino, destino) == 0)
        {
            imprime_data(aux->info.data);
            printf("Lotacao: %d\n\n", aux->info.lotac);
            printf("Lugares: \n");
            imprime_listaCptr(aux->info.lugar);
            printf("Espera: \n");
            imprime_listaEspera(&aux->info.espera);
            flag = 1;
        }
        aux = aux->next;
    }
    if(flag == 0)
        printf("Nao existem viagens para este destino.\n\n");
}

void escreveViagens(ListV viagens, char *ficheiro)
{
    ListV aux;
    ListCptr clt;
    FILE *f;
    aux = viagens;
    f = fopen(ficheiro, "w");
    if(f != NULL)
    {
        while(aux != NULL)
        {
            fprintf(f, "VIAGEM\n%s%.2d:%.2d-%.2d/%.2d/%d*%d\n", aux->info.destino, aux->info.data.hora, aux->info.data.minu, aux->info.data.dia, aux->info.data.mes, aux->info.data.ano, aux->info.lotac);
            clt = aux->info.lugar;
            fprintf(f, "LUGARES\n");
            while(clt != NULL)
            {
                fprintf(f, "%d\n", clt->info->cc);
                clt = clt->next;
            }
            fprintf(f, "ESPERA\n");
            clt = aux->info.espera.first;
            while(clt != NULL)
            {
                fprintf(f, "%d\n", clt->info->cc);
                clt = clt->next;
            }
            fprintf(f, "END\n");
            aux = aux->next;
        }
        fclose(f);
    }
}

void escreveClientes(ListC clientes, char *ficheiro)
{

    FILE *f;
    ListC aux;
    f = fopen(ficheiro, "w");
    if(f != NULL)
    {
        aux = clientes;
        while(aux != NULL)
        {
            fprintf(f, "%s%d\n", aux->info.nome, aux->info.cc);
            aux = aux->next;
        }
        fclose(f);
    }
}

