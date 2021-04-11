//Hyhickle Ryozo Umetsubo Gonçalves - AED1
//Semana 3 - Exercício 7

//Condição 1: O programa deve armazenar no máximo 10 pessoas
//Condição 2: Todas as variáveis que forem usadas no programa deve ser ponteiros.
//Condição 3: A única exceção é o item 1 que deve ser uma variável global Pessoa pessoas[10].
//Condição 4: Os ponteiros devem apontar para um buffer chamado pBuffer onde os dados devem ser armazenados.

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Observação: Nesse código obtei por faze-lo armazenar quantas pessoas o usuário desejar, realocando o espaço sempre que for adicionado ou removido um contato.
//Motivo 1: Dessa forma pude treinar ainda mais o conteúdo proposto.
//Motivo 2: Sentia que o código estava muito limitado. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaração das funções utilizadas no código
void incluir_nome();
void apagar_nome();
void buscar_nome();
void listar_nome();
void menu_inicial();

//Declaração dos meus Buffers Globais
void *pbuffer;
void *agenda_pessoas;

typedef struct variaveis
{
    int escolha_menu;
    int numero_nomes;
    int indice_pessoa_apagar;
    char nome_buscado[10];
    int contador;
} Variaveis;

typedef struct pessoas
{
    char nome[10];
    int idade;
    int telefone;
} Pessoas;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função de Incluir nomes
void incluir_nome()
{
    Pessoas *p;
    Variaveis *a;
    a = pbuffer;

    agenda_pessoas = (Pessoas *)realloc(agenda_pessoas, (sizeof(Pessoas) * (a->numero_nomes + 1)));
    if (agenda_pessoas == NULL)
    {
        printf("\n---Erro, falta de memoria---\n");
        exit(1);
    }
    p = agenda_pessoas + (sizeof(Pessoas) * (a->numero_nomes));
    printf("\nInsira um nome: ");
    scanf("%s", p->nome);
    fflush(stdin);
    printf("Insira a idade: ");
    scanf("%d", &p->idade);
    fflush(stdin);
    printf("Insira o telefone: ");
    scanf("%d", &p->telefone);
    fflush(stdin);
    printf("\n---NOME ADICIONADO---\n");
    a->numero_nomes = a->numero_nomes + 1;
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função de Apagar Nomes
void apagar_nome()
{
    Variaveis *a;
    Pessoas *p;
    Pessoas *p1;

    a = pbuffer;

    printf("\nQual indice voce deseja apagar: ");
    scanf("%d", &a->indice_pessoa_apagar);

    if (a->indice_pessoa_apagar > a->numero_nomes)
    {
        printf("\n---Nenhuma pessoa cadastrada---\n");
        return;
    }

    if (a->indice_pessoa_apagar == a->numero_nomes)
    {
        agenda_pessoas = (Pessoas *)realloc(agenda_pessoas, (sizeof(Pessoas) * (a->numero_nomes)));
        a->numero_nomes--;
        return;
    }
    p = agenda_pessoas + (sizeof(Pessoas) * (a->indice_pessoa_apagar - 1));
    p1 = agenda_pessoas + (sizeof(Pessoas) * (a->indice_pessoa_apagar));
    memcpy(p, p1, (sizeof(Pessoas) * (a->numero_nomes)) - (sizeof(Pessoas) * a->indice_pessoa_apagar));
    a->numero_nomes--;
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função de Buscar Nomes
void buscar_nome()
{
    Variaveis *a;
    Pessoas *p;
    a = pbuffer;
    p = agenda_pessoas;
    printf("\nQual pessoa quer buscar: ");
    scanf("%s", a->nome_buscado);

    for (a->contador = 0; a->contador < a->numero_nomes; a->contador++)
    {
        if (strcmp(a->nome_buscado, p->nome) == 0)
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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função de Listar Nomes
void listar_nome()
{
    Variaveis *a;
    Pessoas *p;
    a = pbuffer;
    p = agenda_pessoas;
    for (a->contador = 0; a->contador < a->numero_nomes; a->contador++)
    {
        printf("\n\n---PESSOA: %d---", a->contador + 1);
        printf("\nNome: %s", p->nome);
        printf("\nIdade: %d", p->idade);
        printf("\nTelefone: %d", p->telefone);
        p++;
    }
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função De Menu Inicial
void menu_inicial()
{
    Variaveis *a;
    a = pbuffer;

    for (;;)
    {
        printf("\n\n----------AGENDA----------\n\n");
        printf("1-Incluir Pessoa: \n");
        printf("2-Apagar Pessoa: \n");
        printf("3-Buscar Pessoa: \n");
        printf("4-Listar Pessoas: \n");
        printf("5-Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &a->escolha_menu);

        switch (a->escolha_menu)
        {
        case 1:
            incluir_nome();
            break;
        case 2:
            apagar_nome();
            break;
        case 3:
            buscar_nome();
            break;
        case 4:
            listar_nome();
            break;
        case 5:
            free(agenda_pessoas);
            free(pbuffer);
            return 0;
        default:
            printf("\n---OPCAO INVALIDA---\n");
            break;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    Variaveis *a;
    pbuffer = malloc(sizeof(Variaveis));
    if (pbuffer == NULL)
    {
        printf("Erro");
        exit(1);
    }

    a = pbuffer;
    a->numero_nomes = 0;

    menu_inicial();
}