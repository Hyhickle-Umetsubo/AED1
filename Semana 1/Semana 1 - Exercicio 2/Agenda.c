//Hyhickle Ryozo Umetsubo Gonçalves - AED1
//Semana 1 - Exercicio 2

//Condição 1 - Faça um programa que armazena nomes
//Condição 2 - O programa deve armazenar todos os nomes na mesma string
//Condição 3 - O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos.
//Condição 4 - Não pode ter desperdício de memória.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaração de funções utilizadas nesse programa:
char *adicionar_nome(char *string);
char *remover_nome(char *string);
void listar_nome(char *string);

int main()
{
    int escolha_menu;
    //Crio uma string sem um valor estabelecido de tamanho 1 para que assim nao tenha perda de memoria
    char *string_nomes = (char *)malloc(sizeof(char));
    //Estabeleço o primeiro valor da string com \0
    string_nomes[0] = '\0';

    for (;;)
    {
        printf("\n\n\n\n\n----------AGENDA DE NOMES----------\n\n");
        printf("1-Adicionar Nome\n");
        printf("2-Remover Nome\n");
        printf("3-Listar Nomes\n");
        printf("4-Sair\n");
        printf("Digite sua Opcao:  ");
        scanf("%d", &escolha_menu);
        switch (escolha_menu)
        {
        case 1:
            string_nomes = adicionar_nome(string_nomes);
            break;
        case 2:
            string_nomes = remover_nome(string_nomes);
            break;
        case 3:
            listar_nome(string_nomes);
            break;
        case 4:
            free(string_nomes);
            return 0;
        default:
            printf("\nEssa Opcao e invalida!\n");
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Caso a escolha seja igual a 1 abre a função de adicionar nome
char *adicionar_nome(char *string)
{
    char nome_adicionado[30];
    int tamanho_string;
    int tamanho_nome;
    int teste_tamanho_string;

    printf("\nInsira um nome: ");
    scanf("%s", nome_adicionado);
    //strcat concatena duas strings adicionando um '.' entre elas
    strcat(nome_adicionado, ".");
    //strlen pega o comprimento do nome adicionado e +1 para contar o '\0'
    tamanho_nome = strlen(nome_adicionado) + 1;
    tamanho_string = strlen(string) + 1;
    //tendo o comprimento do nome adicionado e o comprimento da string principal de nomes é possivel realocar a string de nomes com o tamanho correto
    string = (char *)realloc(string, (tamanho_string + tamanho_nome) * sizeof(char));
    if (string == NULL)
    {
        printf("Erro, falta de memoria");
        exit(1);
    }
    strcat(string, nome_adicionado);
    printf("\nNome adicionado com sucesso.\n");
    teste_tamanho_string = strlen(string) + 1;
    printf("Tamanho da String: %d", teste_tamanho_string);
    return string;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//Caso a escolha seja igual a 2 abre a função de remover nome
char *remover_nome(char *string)
{
    int remover_nome;
    int numero_pontos = 1;
    int tamanho_apagado = 0;
    int tamanho_string_principal = strlen(string) + 1;
    int teste_tamanho_string;
    char *string_reserva;

    if (string[0] == '\0')
    {
        printf("\n-----NENHUM NOME FOI ARMAZENADO-----\n");
    }
    else
    {
        printf("\nQual o indice do nome que deseja remover: ");
        scanf("%d", &remover_nome);

        for (int c = 0; string[c] != '\0'; c++)
        {
            if (string[c] == '.')
            {
                if (numero_pontos == remover_nome)
                {
                    string_reserva = &string[c + 1];
                }
                numero_pontos++;
            }
            else
            {
                if (numero_pontos == remover_nome)
                {
                    string[c] = '#';
                }
            }
        }
        for (int c = 0; string[c] != '\0'; c++)
        {
            if (string[c] == '#')
            {
                tamanho_apagado++;
                strcpy(&string[c], string_reserva);
            }
        }

        string = (char *)realloc(string, (tamanho_string_principal - tamanho_apagado) * sizeof(char));
        if (string == NULL)
        {
            printf("\nErro, falta de memoria");
            exit(1);
        }
        printf("\nNome Apagado com Sucesso\n");
    }
    teste_tamanho_string = strlen(string) + 1;
    printf("Tamanho da String: %d", teste_tamanho_string);
    return string;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
//Caso a escolha seja igual a 3 abre a função de listar os nomes
void listar_nome(char *string)
{
    int indice_nome = 1;
    if (string[0] == '\0')
    {
        printf("\n-----NENHUM NOME FOI ARMAZENADO-----\n");
    }
    else
    {
        printf("\nNomes: \n");
        printf("%d- ", indice_nome);
        for (int c = 0; string[c] != '\0'; c++)
        {
            if (string[c] != '.')
            {
                printf("%c", string[c]);
            }
            else
            {
                printf("\n");
                if (string[c + 1] != '\0')
                {
                    indice_nome++;
                    printf("%d- ", indice_nome);
                }
            }
        }
    }
}
