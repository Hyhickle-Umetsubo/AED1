//Hyhickle Ryozo Umetsubo Gonçalves - AED1
//Semana 3 - Exercicio 5

//Condição 1: Faça um programa que armazene a informação de várias pessoas (Nome,Idade,Altura)
//Condição 2: O programa só deve sair quando o usuário disser que não deseja mais entrar com os dados de outra pessoa.
//Condição 3: Antes de sair o programa deve apresentar, de forma organizada, os dados de todas as pessoas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções Utilizadas no Programa
int adicionar_pessoas(int numero_pessoas);
void menu_inicial(int numero_pessoas);
void listar_pessoas(int numero_pessoas);

//Meu buffer global
void *agenda;

typedef struct pessoas
{
    char nome[30];
    int idade;
    float altura;
} Pessoas;

//-----------------------------------------------------------------------------------------------------------------------
//Função Main
int main()
{
    int numero_pessoas = 0;
    menu_inicial(numero_pessoas);
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de menu inicial do programa
void menu_inicial(int numero_pessoas)
{
    int escolha_usuario;

    for (;;)
    {
        printf("\n---DESEJA ADICIONAR UMA PESSOA---\n");
        printf("1- SIM\n2- NAO\n");
        printf("Insira sua Escolha: ");
        scanf("%d", &escolha_usuario);
        switch (escolha_usuario)
        {
        case 1:
            numero_pessoas = adicionar_pessoas(numero_pessoas);
            break;
        case 2:
            listar_pessoas(numero_pessoas);
            free(agenda);
            return 0;
            break;
        default:
            printf("\n---OPCAO INVALIDA---\n");
            break;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de Adicionar Pessoas 
int adicionar_pessoas(int numero_pessoas)
{
    Pessoas *p;
    agenda = (Pessoas *)realloc(agenda, (sizeof(Pessoas) * (numero_pessoas + 1)));
    if (agenda == NULL)
    {
        printf("\n---Erro, falta de memoria---\n");
        exit(1);
    }
    p = agenda + (sizeof(Pessoas) * (numero_pessoas));
    printf("\nInsira um Nome: ");
    scanf("%s", p->nome);
    fflush(stdin);
    printf("Insira uma Idade: ");
    scanf("%d", &p->idade);
    fflush(stdin);
    printf("Insira uma altura: ");
    scanf("%f", &p->altura);
    fflush(stdin);
    printf("\n---NOME ADICIONADO---\n");
    numero_pessoas = numero_pessoas + 1;
    return numero_pessoas;
}

//-----------------------------------------------------------------------------------------------------------------------
//Função de Listar as Pessoas
void listar_pessoas(int numero_pessoas)
{
    Pessoas *p;
    p = agenda;

    for (int c = 0; c < numero_pessoas; c++)
    {
        printf("\n\n---PESSOA: %d---", c + 1);
        printf("\nNome: %s", p->nome);
        printf("\nIdade: %d", p->idade);
        printf("\nAltura: %.2f", p->altura);
        p++;
    }
}