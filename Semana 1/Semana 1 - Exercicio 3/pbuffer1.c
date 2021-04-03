//Hyhickle Ryozo Umetsubo Gonçalves - AED1
//Semana 1 - Exercício 3

//Condição 1 - Faça uma agenda capaz de incluir, apagar, buscar e listar quantas pessoas o usuário desejar.
//Condição 2 - Toda informação incluída na agenda deve ficar num único lugar chamado:“void *pBuffer”.
//Condição 3 - Não pergunte para o usuário quantas pessoas ele vai incluir.
//Condição 4 - Não alocar espaço para mais pessoas do que o necessário.
//Condição 5 - Cada pessoa tem nome[10], idade e telefone.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaração das funções utilizadas
int incluir_nome(int numero_nomes);
int apagar_nome(int numero_nomes);
void buscar_nome(int numero_nomes);
void listar_nome(int numero_nomes);

//meu void *pbuffer global
void *pbuffer;

typedef struct pessoas
{
    char nome[10];
    int idade;
    int telefone;
} Pessoas;

//-----------------------------------------------------------------------------------------------------------------------
int main()
{
    int escolha_menu;
    int numero_nomes = 0;

    for (;;)
    {
        printf("\n\n----------AGENDA----------\n\n");
        printf("1-Incluir Pessoa: \n");
        printf("2-Apagar Pessoa: \n");
        printf("3-Buscar Pessoa: \n");
        printf("4-Listar Pessoas: \n");
        printf("5-Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha_menu);

        switch (escolha_menu)
        {
        case 1:
            numero_nomes = incluir_nome(numero_nomes);
            break;
        case 2:
            numero_nomes = apagar_nome(numero_nomes);
            break;
        case 3:
            buscar_nome(numero_nomes);
            break;
        case 4:
            listar_nome(numero_nomes);
            break;
        case 5:
            free(pbuffer);
            return 0;
        default:
            printf("\n---OPCAO INVALIDA---\n");
            break;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de Incluir nomes
int incluir_nome(int numero_nomes)
{
    Pessoas *p;

    pbuffer = (Pessoas *)realloc(pbuffer, (sizeof(Pessoas) * (numero_nomes + 1)));
    if (pbuffer == NULL)
    {
        printf("\n---Erro, falta de memoria---\n");
        exit(1);
    }
    p = pbuffer + (sizeof(Pessoas) * (numero_nomes));
    printf("\nInsira um nome: ");
    scanf("%s", p->nome);
    fflush(stdin);
    printf("\nInsira a idade: ");
    scanf("%d", &p->idade);
    fflush(stdin);
    printf("\nInsira o telefone: ");
    scanf("%d", &p->telefone);
    fflush(stdin);
    printf("\n---NOME ADICIONADO---\n");
    numero_nomes = numero_nomes + 1;
    return numero_nomes;
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de Apagar Nomes
int apagar_nome(int numero_nomes)
{
    Pessoas *p;
    int indice_pessoa_apagar;
    Pessoas *p1;

    printf("\nQual indice voce deseja apagar: ");
    scanf("%d", &indice_pessoa_apagar);

    if (indice_pessoa_apagar > numero_nomes)
    {
        printf("\n---Nenhuma pessoa cadastrada---\n");
        return numero_nomes;
    }

    if (indice_pessoa_apagar == numero_nomes)
    {
        pbuffer = (Pessoas *)realloc(pbuffer, (sizeof(Pessoas) * (numero_nomes)));
        numero_nomes--;
        return numero_nomes;
    }
    p = pbuffer + (sizeof(Pessoas) * (indice_pessoa_apagar - 1));
    p1 = pbuffer + (sizeof(Pessoas) * (indice_pessoa_apagar));
    memcpy(p, p1, (sizeof(Pessoas) * (numero_nomes)) - (sizeof(Pessoas) * indice_pessoa_apagar));
    numero_nomes--;
    return numero_nomes;
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de Buscar Nomes
void buscar_nome(int numero_nomes)
{
    char nome_buscado[10];
    Pessoas *p;
    p = pbuffer;
    printf("\nQual pessoa quer buscar: ");
    scanf("%s", nome_buscado);

    for (int c = 0; c < numero_nomes; c++)
    {
        if (strcmp(nome_buscado, p->nome) == 0)
        {
            printf("\nNome: %s", p->nome);
            printf("\nIdade: %d", p->idade);
            printf("\nTelefone: %d", p->telefone);
            return;
        }
        p++;
    }
    printf("\n---PESSOA NAO CADASTRADA---\n");
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de Listar Nomes
void listar_nome(int numero_nomes)
{
    Pessoas *p;
    p = pbuffer;
    for (int c = 0; c < numero_nomes; c++)
    {
        printf("\n\n---PESSOA: %d---", c + 1);
        printf("\nNome: %s", p->nome);
        printf("\nIdade: %d", p->idade);
        printf("\nTelefone: %d", p->telefone);
        p++;
    }
    return;
}