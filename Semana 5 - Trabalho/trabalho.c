//Hyhickle Ryozo Umetsubo Gonçalves - AED1
//Semana 5 - Trabalho

//Condição 1: Nenhuma variável pode ser declarada em todo o programa, somente ponteiros.
//Condição 2: Todos os dados do programa devem ser guardados dentro do pBuffer.
//Condição 3: Imprimir de forma ordenada usando uma fila ordenada.
//Condição 4: O usuário escolhe um parâmetro de ordenação e uma fila ordenada é criada.
//Condição 5: Implementar a base de dados da agenda usando lista duplamente ligada.

//---------------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cadastro
{
    char nome[50];
    int idade;
    int telefone;
} Cadastro;

typedef struct variaveis
{
    int escolha_menu;
    int indice_remover_pessoa;
    int contador, tam;
    int escolha_listar;
    Cadastro pessoas;
    Cadastro *fila;
} Variaveis;

typedef struct vars *Lista;

typedef struct vars
{
    struct vars *last;
    struct vars *next;
    Cadastro pessoas;
} elem;

//Declaração do pbuffer Global
void *pbuffer;

//Declaração das Funções utilizadas no código
void Libera_Lista(Lista *list);
void Adicionar_Pessoa(Lista *list);
void Listar_Pessoas(Lista *list);
void Fila_Ordenada(Lista *list);
void Remover_Pessoa(Lista *list);
void Buscar_Pessoa(Lista *list);
void Menu_Inicial(Lista *list);

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função de Limpar a Lista
void Libera_Lista(Lista *list)
{
    if (list != NULL)
    {
        elem *caixa;
        while ((*list) != NULL)
        {
            caixa = *list;
            *list = (*list)->next;
            free(caixa);
        }
        free(list);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função de Incluir uma Pessoa
void Adicionar_Pessoa(Lista *list)
{
    Variaveis *novo;
    novo = pbuffer;

    printf("Insira um Nome: ");
    scanf("%s", (*novo).pessoas.nome);
    printf("Insira uma Idade: ");
    scanf("%d", &(*novo).pessoas.idade);
    printf("Insira um Telefone: ");
    scanf("%d", &(*novo).pessoas.telefone);

    if (list == NULL)
    {
        printf("Erro");
        exit(1);
    }

    elem *caixa = (elem *)malloc(sizeof(elem));

    if (caixa == NULL)
    {
        printf("Erro");
        exit(1);
    }

    //Cadastro recebe a caixa
    caixa->pessoas = novo->pessoas;
    //Caixa aponta para proxima caixa
    caixa->next = (*list);
    //O anterior se torna o ultimo
    caixa->last = NULL;

    if ((*list) != NULL)
    {
        //Se a lista não estiver vazia, o topo aponta para a nova caixa
        (*list)->last = caixa;
    }
    //Conteudo da caixa é inserido na lista
    *list = caixa;
    novo->tam++;

    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função de Listar as Pessoas
void Listar_Pessoas(Lista *list)
{
    Variaveis *p;
    p = pbuffer;

    elem *n;
    n = *list;

    p->contador = 0;
    printf("1 - Alfabetica Crescente\n2 - Alfabetica Decrescente\n");
    printf("Digite sua Escolha: ");

    do
    {
        scanf("%d", &p->escolha_listar);
    } while (p->escolha_listar > 2 || p->escolha_listar < 0);

    //Chamo a função que cria a Fila Ordenada
    Fila_Ordenada(list);
    p->fila = (Cadastro *)malloc(p->tam * sizeof(Cadastro));

    if (p->fila == NULL)
    {
        printf("Erro");
        exit(1);
    }

    while (n != NULL)
    {
        p->fila[p->contador] = n->pessoas;
        p->contador++;
        n = n->next;
    }

    //Listo de Forma Alfabetica Crescente
    if (p->escolha_listar == 1)
    {
        p->contador = 0;
        while (p->contador < p->tam)
        {
            printf("\n-----PESSOA:%d-----\n", p->contador);
            printf("Nome: %s\n", p->fila[p->contador].nome);
            printf("Idade: %d\n", p->fila[p->contador].idade);
            printf("Telefone: %d\n", p->fila[p->contador].telefone);
            p->contador++;
        }
    }
    else
    //Listo de Forma Alfabetica Decrescente
    {
        p->contador = p->tam - 1;
        while (p->contador >= 0)
        {
            printf("\n-----PESSOA:%d-----\n", p->contador);
            printf("Nome: %s\n", p->fila[p->contador].nome);
            printf("Idade: %d\n", p->fila[p->contador].idade);
            printf("Telefone: %d\n", p->fila[p->contador].telefone);
            p->contador--;
        }
    }
    //Dou um Free na fila ordenada criada
    free(p->fila);
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função que Organiza as Pessoas
void Fila_Ordenada(Lista *list)
{
    Variaveis *p;
    p = pbuffer;
    elem *n, *i;
    n = *list;
    i = *list;

    while (n != NULL)
    { //Percorro a lista
        i = n->next;
        while (i != NULL)
        { //Passo uma outra lista para comparar os nomes
            if (strcmp(n->pessoas.nome, i->pessoas.nome) > 0)
            {
                //Caso seja maior
                strcpy(p->pessoas.nome, n->pessoas.nome);
                p->pessoas.idade = n->pessoas.idade;
                p->pessoas.telefone = n->pessoas.telefone;
                //Passo o nome maior para frente
                strcpy(n->pessoas.nome, i->pessoas.nome);
                n->pessoas.idade = i->pessoas.idade;
                n->pessoas.telefone = i->pessoas.telefone;
                //Passo o nome menor para tras
                strcpy(i->pessoas.nome, p->pessoas.nome);
                i->pessoas.idade = p->pessoas.idade;
                i->pessoas.telefone = p->pessoas.telefone;
            }
            i = i->next;
        }
        n = n->next;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função de Apagar Pessoa
void Remover_Pessoa(Lista *list)
{
    if (list == NULL)
        return;
    if (*list == NULL)
        return;

    Variaveis *p;
    p = pbuffer;
    p->contador = 0;
    elem *caixa;
    caixa = *list;
    
    printf("Qual indice deseja remover: ");
    scanf("%d", &p->indice_remover_pessoa);

    while (caixa != NULL && p->contador != p->indice_remover_pessoa)
    {
        caixa = caixa->next;
        p->contador++;
    }
    if (caixa == NULL)
        return;
    if (caixa->last == NULL)
        *list = caixa->next;
    else
        //A ligacao do ultimo recebe o proximo daquele que vou excluir
        caixa->last->next = caixa->next;
    if (caixa->next != NULL)
        //O nome anterior do próximo nome do que vou excluir recebe o nome anterior do que vou excluir
        caixa->next->last = caixa->last;
    free(caixa);

    p->tam--;
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função de Buscar Pessoa
void Buscar_Pessoa(Lista *list)
{
    Variaveis *p;
    elem *caixa;
    p = pbuffer;
    p->contador = 0;
    caixa = *list;

    printf("Qual nome deseja buscar: ");
    scanf("%s", p->pessoas.nome);

    while (caixa != NULL)
    {
        if (strcmp(p->pessoas.nome, caixa->pessoas.nome) == 0)
        {
            printf("[Nome na lista]\n->Posicao: %d", p->contador);
            return;
        }
        caixa = caixa->next;
        p->contador++;
    }
    printf("Nome nao encontrado");
}

//---------------------------------------------------------------------------------------------------------------------------------------------
//Função que chama o Menu Inicial
void Menu_Inicial(Lista *list)
{
    Variaveis *p;
    p = pbuffer;

    for (;;)
    {
        printf("\n\n----------AGENDA----------\n\n");
        printf("1-Incluir Pessoa: \n");
        printf("2-Apagar Pessoa: \n");
        printf("3-Buscar Pessoa: \n");
        printf("4-Listar\n");
        printf("5-Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &p->escolha_menu);
        switch (p->escolha_menu)
        {
        case 1:
            Adicionar_Pessoa(list);
            break;
        case 2:
            Remover_Pessoa(list);
            break;
        case 3:
            Buscar_Pessoa(list);
            break;
        case 4:
            Listar_Pessoas(list);
            break;
        case 5:
            Libera_Lista(list);
            free(pbuffer);
            return 0;
        default:
            printf("\n-----Opcao Invalida-----\n");
            break;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    pbuffer = (Variaveis *)malloc(sizeof(Variaveis));
    if(pbuffer==NULL){
        printf("Erro");
        exit(1);
    }
    Variaveis *p;
    p = pbuffer;
    p->contador = 0;
    p->tam = 0;

    Lista *list = (Lista *)malloc(sizeof(Lista));
    if (list != NULL)
    {
        *list = NULL;
    }

    Menu_Inicial(list);
}