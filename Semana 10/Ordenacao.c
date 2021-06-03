//Hyhickle Ryozo Umetsubo Gonçalves - AED1
//Semana 10 - Algoritmos de Ordenação

//Condição 1: Implementar os algoritmos de ordenação Insertion Sort, Selection Sort, Quick Sort e Merge Sort.
//Condição 2: O programa deve solicitar o tamanho do vetor de números (n) que será ordenado
//Condição 3: O programa deve preencher um vetor de tamanho n com números aleatórios.
//Condição 4: Faça um código que verifica se o resultado dado por cada algoritmo de ordenação está correto.

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Menu_Inicial()
{
    int escolha_ordenacao;
    int tamanho_vetor;
    int testeQS=1;
    int testeMS=1;

    printf("\n\nIndique o tamanho do vetor: ");
    scanf("%d", &tamanho_vetor);

    int vetor_aleatorio[tamanho_vetor];

    printf("Vetor a ser Ordenado: ");

    //Com srand(time(NULL)) o programa irá sempre gerar novos valores aleatórios
    srand(time(NULL));
    
    for (int contador = 0; contador < tamanho_vetor; contador++)
    {
        vetor_aleatorio[contador] = rand();
        printf("%d ", vetor_aleatorio[contador]);
    }

    //Gerando um vetor para Quick Sort
    int vetor_QS[tamanho_vetor];
    for (int contador = 0; contador < tamanho_vetor; contador++) {vetor_QS[contador] = vetor_aleatorio[contador];}

    //Gerando um vetor para Merge Sort
    int vetor_MS[tamanho_vetor];
    for (int contador = 0; contador < tamanho_vetor; contador++) {vetor_MS[contador] = vetor_aleatorio[contador];}

    for (;;)
    {
        printf("\n\n----Selecione o metodo de Ordenacao----\n\n");
        printf("1-Insertion Sort\n");
        printf("2-Selection Sort\n");
        printf("3-Quick Sort\n");
        printf("4-Merge Sort\n");
        printf("5-Finalizar Programa\n\n");
        printf("Digite sua Escolha: ");
        scanf("%d", &escolha_ordenacao);

        switch (escolha_ordenacao)
        {

        case 1:
            Insertion_Sort(vetor_aleatorio, tamanho_vetor);
            break;

        case 2:
            Selection_Sort(vetor_aleatorio, tamanho_vetor);
            break;

        case 3:
            Quick_Sort(vetor_QS, 0, tamanho_vetor - 1);
            printf("Vetor ordenado Quick Sort: ");
            for (int contador = 0; contador < tamanho_vetor; contador++) {printf("%d ", vetor_QS[contador]);}

            //Teste para Verificar se o Vetor esta Ordenado
            for(int contador=0;contador<=tamanho_vetor-1;contador++){
                if(vetor_QS[contador] <=vetor_QS[contador+1]) {testeQS++;}
            }
          
            if(testeQS==tamanho_vetor) {printf("\n-----O VETOR ESTA ORDENADO-----\n");}
            break;

        case 4:
            Merge_Sort(vetor_MS, 0 , tamanho_vetor-1);
            printf("Vetor ordenado Merge Sort: ");
            for (int contador = 0; contador < tamanho_vetor; contador++) {printf("%d ", vetor_MS[contador]);}

            //Teste para Verificar se o Vetor esta Ordenado
            for(int contador=0;contador<=tamanho_vetor-1;contador++){
                if(vetor_MS[contador]<=vetor_MS[contador+1]) {testeMS++;}
            }
            if(testeMS==tamanho_vetor){printf("\n-----O VETOR ESTA ORDENADO-----\n");}
            break;

        case 5:
            return;
            break;

        default:
            printf("\n----Opcao Invalida----\n");
            break;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Insertion_Sort(int vetor_aleatorio[], int tamanho_vetor)
{
    int i, j, tmp;
    int vetor_IS[tamanho_vetor];
    
    for (i = 0; i < tamanho_vetor; i++)
    {
        vetor_IS[i] = vetor_aleatorio[i];
    }

    struct timeval begin, end;
    gettimeofday(&begin, 0);
    

    for (i = 1; i < tamanho_vetor; i++)
    {
        tmp = vetor_IS[i];
        j = i - 1;

        while (j >= 0 && vetor_IS[j] > tmp)
        {
            vetor_IS[j + 1] = vetor_IS[j];
            j = j - 1;
        }
        vetor_IS[j + 1] = tmp;
    }

    printf("Vetor ordenado Insertion Sort: ");
    for (i = 0; i < tamanho_vetor; i++) {printf("%d ", vetor_IS[i]);}
    
    //Teste para Verificar se o Vetor esta Ordenado
    int testeIS=1;
    for(int contador=0;contador<tamanho_vetor-1;contador++){
        if(vetor_IS[contador]<=vetor_IS[contador+1]){
            testeIS++;
        }
    }

    if(testeIS==tamanho_vetor){
        printf("\n-----O VETOR ESTA ORDENADO-----\n");
    }

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("TIME: %.3f seconds.\n", elapsed);  
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Selection_Sort(int vetor_aleatorio[], int tamanho_vetor)
{
    int menor;
    int i;
    int tmp;
    int troca;
    int vetor_SS[tamanho_vetor];

    for (i = 0; i < tamanho_vetor; i++)
    {
        vetor_SS[i] = vetor_aleatorio[i];
    }

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    for (i = 0; i < tamanho_vetor - 1; i++) 
    {
        menor = i; 

        for (tmp = i + 1; tmp < tamanho_vetor; tmp++) 
        {
            if (vetor_SS[tmp] < vetor_SS[menor]) 
            {
                menor = tmp; 
            }
        }

        if (menor != i) 
        {
            troca = vetor_SS[i];
            vetor_SS[i] = vetor_SS[menor];
            vetor_SS[menor] = troca;
        }
    }

    printf("Vetor ordenado Selection Sort: ");
    for (i = 0; i < tamanho_vetor; i++) {printf("%d ", vetor_SS[i]);}

    //Teste para Verificar se o Vetor esta Ordenado
    int testeSS=1;

    for(int contador=0;contador<tamanho_vetor-1;contador++){
        if(vetor_SS[contador]<=vetor_SS[contador+1]){
            testeSS++;
        }
    }
    if(testeSS==tamanho_vetor){
        printf("\n-----O VETOR ESTA ORDENADO-----\n");
    }

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    printf("TIME: %.3f seconds.\n", elapsed);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Quick_Sort(int vetor_QS[], int left, int right)
{
    int i, j, x, y;
    int aux = right + 1;

    i = left;
    j = right;
    //Elemento do meio, ou pivô
    x = vetor_QS[(left + right) / 2]; 

    while (i <= j)
    {
        //Procura menor elemento que o pivô da esquerda até o final
        while (vetor_QS[i] < x && i < right)
        {
            i++;
        }
        //Procura maior elemento que o pivô do meio até o final
        while (vetor_QS[j] > x && j > left)
        {
            j--;
        }
        if (i <= j)
        {
            y = vetor_QS[i];
            vetor_QS[i] = vetor_QS[j];
            vetor_QS[j] = y;
            i++;
            j--;
        }
    }

    if (j > left)
    {
        Quick_Sort(vetor_QS, left, j);
    }
    if (i < right)
    {
        Quick_Sort(vetor_QS, i, right);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void merge(int vetor_MS[], int l, int m, int r){

    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = vetor_MS[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vetor_MS[m + 1 + j];
 
    i = 0;
    j = 0; 
    k = l; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor_MS[k] = L[i];
            i++;
        }
        else {
            vetor_MS[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        vetor_MS[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        vetor_MS[k] = R[j];
        j++;
        k++;
    }
}

void Merge_Sort(int vetor_MS[], int l, int r){
   
    if (l < r) {
        int m = l + (r - l) / 2;
 
        Merge_Sort(vetor_MS, l, m);
        Merge_Sort(vetor_MS, m + 1, r);
 
        merge(vetor_MS, l, m, r);
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    Menu_Inicial();
    printf("\n\n----FINALIZANDO PROGRAMA----\n\n");
    return 0;
}