#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Dados de comércio eletrônico

#define CSVSIZE 10000

typedef struct ProjetoDataSet
{
    int nFatura;
    char *idEstoque;
    char *descricao;
    int qtde;
    char *data;
    float precoUni;
    int idCliente;
    char *pais;
}t_comerce;


int main()
{

    t_comerce *eletronico;
    FILE *fp;
    char str[900]; // para ler uma linha do arquivo
    int i = 0; //ontador que é usado para controlar o número de registros lidos

    eletronico = (t_comerce*) malloc(CSVSIZE * sizeof(t_comerce));

    if (eletronico == NULL)
    {
        printf("ERRO! Falha ao alocar memoria!\n");
        exit(1);
    }


    fp = fopen("data.csv", "r");

    if(fp == NULL)
    {
        printf("ERRO! Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    // pegando o cabeçalho
    char *ok; // se ok for NULL teve problema na leitura
    ok = fgets(str, 900, fp); // pega a string do arquivo
    if (ok == NULL)
    {
        printf("Erro lendo o cabecalho do CSV!!!", str);
        exit(1);
    }

    i = 0;
    char sep[] = ",";

    while (!feof(fp) && i < CSVSIZE) // enquanto nâo chegar no final do arquivo ou no tamanho do array
    {
        ok = fgets(str, 900, fp); // pega uma string do arquivo
        if (ok) // se ok != NULL (NULL é Falso, diferente de NULL verdadeiro)
        {
            char *campo;
            campo = strtok(str, sep); // pega o primeiro campo
            eletronico[i].nFatura = atoi(campo); // converte para inteiro e atribui ao campo nFatura
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].idEstoque = strdup(campo); // copia a string para o campo idEstoque
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].descricao = strdup(campo); // copia a string para o campo descricao
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].qtde = atoi(campo); // converte para inteiro e atribui ao campo qtde
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].data = strdup(campo); // copia a string e para o campo data
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].precoUni = atof(campo); // converte para float e atribui ao campo precoUnitario
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].idCliente = atoi(campo); // converte para inteiro e atribui ao campo idCliente
            campo = strtok(NULL, sep); // pega o próximo campo
            eletronico[i].pais = strdup(campo); // copia a string para o campo pais
            i++;
        }
    }

        fclose(fp);

        //exibindo os dados lidos
        for (int j = 0; j < i; j++)
        {
            printf("Num Fatura: %d\n", eletronico[j].nFatura);
            printf("Id Estoque: %s\n", eletronico[j].idEstoque);
            printf("Descricao: %s\n", eletronico[j].descricao);
            printf("Quantidade: %d\n", eletronico[j].qtde);
            printf("Data: %s\n", eletronico[j].data);
            printf("Preco Unitario: %.2f\n", eletronico[j].precoUni);
            printf("Id Cliente: %d\n", eletronico[j].idCliente);
            printf("Pais: %s\n", eletronico[j].pais);
        }

        //liberandi a memoria alocada
        for (int j = 0; j < i; j++)
        {
            free(eletronico[j].idEstoque);
            free(eletronico[j].descricao);
            free(eletronico[j].data);
            free(eletronico[j].pais);
        }

        free(eletronico);

    return 0;
}
