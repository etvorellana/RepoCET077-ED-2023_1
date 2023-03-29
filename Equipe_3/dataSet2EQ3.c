#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSVSIZE 13000

typedef struct {
    int number;
    char *DataTime;
    char *duracao;
    char *title;
    char *genero;
    char *dataLanc;
    char *movieId;
    char *userId;
} t_dados;

//////////////////////////////////////////////////////
///////////////////PROTOTIPOS////////////////////////
t_dados *carregaDados(char *arquivo, int *tam);
void limpaArquivo(t_dados *netflix, int tam);
int procurar_id_Arquivo(t_dados *netflix, int n_registros, char *id_estoque_procurado);
int buscaElemento(t_dados *netflix, int tam, char *idBusca);
void criar_subArquivo(char *arquivo_original, char *subArquivo);
void inserir_elemento_no_subArquivo(char *arquivo_original, char *subArquivo, char *id);
void remover_elemento_do_subArquivo(char *subArquivo, char *id);


int main() {
    t_dados *netflix;
    int tam;

    netflix = carregaDados("netflix.csv", &tam);

            // busca por um id especifico
            char idBuscado[16];

            printf("digite o id: ");
            scanf("%s", idBuscado);
            int index = procurar_id_Arquivo(netflix, &tam, idBuscado); //indice recebe por Parametro: lista do arquivo, qtde de registros, idDesejado

            int posicao = buscaElemento(netflix, &tam, idBuscado); // buscar o elemento com id
            if(posicao >= 0)
            {
                printf("Elemento encontrado na posicao %d do arquivo.\n", posicao);
            } else {
                printf("Elemento nao encontrado no arquivo.\n");
            }

            criar_subArquivo("netiflix.csv", "subArquivo.csv");
            inserir_elemento_no_subArquivo("netflix.csv", "subArquivo.csv", idBuscado);
            remover_elemento_do_subArquivo("subArquivo.csv", idBuscado);


    limpaArquivo(netflix, tam);

    return 0;
}

//////////////////////////////////////////
///////////////FUNÇÔES///////////////////
////////////////////////////////////////


t_dados *carregaDados(char *arquivo, int *tam) {
    t_dados *netflix = NULL;
    FILE *fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("Arquivo nao pode ser aberto!\n");
        exit(1);
    }

    char str[900];
    char *ok;

    // Ignora o cabeçalho do CSV
    ok = fgets(str, 900, fp);
    if (ok == NULL) {
        printf("Erro na leitura do arquivo CSV.\n");
        exit(1);
    }

    int i = 0;
    char sep[] = ",";

    netflix = (t_dados *)malloc(CSVSIZE * sizeof(t_dados));
    if (netflix == NULL) {
        printf("Nao foi possivel alocar memoria!\n");
        exit(1);
    }

    while (!feof(fp) && i < CSVSIZE) {
        ok = fgets(str, 900, fp);
        if (ok) {
            char *campo;

            campo = strtok(str, sep);
            netflix[i].number = atoi(campo);

            campo = strtok(NULL, sep);
            netflix[i].DataTime = strdup(campo);

            campo = strtok(NULL, sep);
            netflix[i].duracao = strdup(campo);

            campo = strtok(NULL, sep);
            netflix[i].title = strdup(campo);

            campo = strtok(NULL, sep);
            netflix[i].genero = strdup(campo);

            campo = strtok(NULL, sep);
            netflix[i].dataLanc = strdup(campo);

            campo = strtok(NULL, sep);
            netflix[i].movieId = strdup(campo);

            campo = strtok(NULL, sep);
            netflix[i].userId = strdup(campo);

            i++;
        }
    }

    fclose(fp);
    *tam = i;

    return netflix;
}

//////////////////////////////////////////////
void limpaArquivo(t_dados *netflix, int tam)
{
    for(int j = 0; j < tam; j++)
    {
        free(netflix[j].DataTime);
        free(netflix[j].duracao);
        free(netflix[j].title);
        free(netflix[j].genero);
        free(netflix[j].dataLanc);
        free(netflix[j].movieId);
        free(netflix[j].userId);
    }
    free(netflix);
}

//////////////////////////////////////////////////
//função para encontrar Produto Estoque no arquivo
int procurar_id_Arquivo(t_dados *netflix, int n_registros, char *id_estoque_procurado)
{
    int encontrou = 0;

    for (int j = 0; j < n_registros; j++)
    {
        if (strcmp(netflix[j].userId, id_estoque_procurado) == 0)
        {
            encontrou = 1;
            printf("Registro encontrado:\n");
            printf("Number: %d\n", netflix[j].number);
            printf("Data Time: %s\n", netflix[j].DataTime);
            printf("Duração: %s\n", netflix[j].duracao);
            printf("Title: %s\n", netflix[j].title);
            printf("Genero: %s\n", netflix[j].genero);
            printf("Data Lancamento: %s\n", netflix[j].dataLanc);
            printf("Movie Id: %s\n", netflix[j].movieId);
            printf("User Id: %s\n", netflix[j].userId);
        }
    }

    if (!encontrou)
    {
        printf("Nenhum registro encontrado com o id %s\n", id_estoque_procurado);
        return 0;
    }

    return 1;
}

////////////////////////////////////////////////////////////
//Função Buscar Posiçãoo do Elemento no Arquivo////////////
int buscaElemento(t_dados *netflix, int tam, char *idBusca)
{
    for(int i = 0; i < tam; i++)
    {
        if (strcmp(netflix[i].userId, idBusca) == 0)
        {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////
void criar_subArquivo(char *arquivo_original, char *subArquivo) {
    FILE *origem = fopen(arquivo_original, "r");
    FILE *destino = fopen(subArquivo, "w");

    if (!origem || !destino) {
        printf("Erro ao abrir arquivos\n");
        return;
    }

    fclose(origem);
    fclose(destino);
}

///////////////////////////////////////////////////////////////////////////////
void inserir_elemento_no_subArquivo(char *arquivo_original, char *subArquivo, char *id) {
    FILE *origem = fopen(arquivo_original, "r");
    FILE *destino = fopen(subArquivo, "a"); //escrever sem alterar os dados anteriores

    if (!origem || !destino) {
        printf("Erro ao abrir arquivos\n");
        return;
    }

    char linha[1024]; //array de caracteres tam 1024
    while (fgets(linha, sizeof(linha), origem)) { //ler uma linha do arquivo origem
        if (strstr(linha, id)) {    //A condição strstr(linha, id) será verdadeira se id estiver em linha.
            fputs(linha, destino); //if verdadeira, o ID está presente na linha lida do arquivo origem e a fputs escreve no arquivo destino.
        }
    }
    //strstr Ela devolve um ponteiro nulo se não for encontrada nenhuma coincidência.

    fclose(origem);
    fclose(destino);
}

////////////////////////////////////////////////////////////////
void remover_elemento_do_subArquivo(char *subArquivo, char *id) {
    FILE *origem = fopen(subArquivo, "r");
    FILE *temp = fopen("temp.csv", "w"); //copiar todas as linhas que não contêm o ID especificado para o arquivo temporário temp. 

    if (!origem || !temp) {
        printf("Erro ao abrir arquivos\n");
        return;
    }

    char linha[1024]; //array de caracteres com tamanho 1024
    while (fgets(linha, sizeof(linha), origem)) {   //ler uma linha do arquivo origem
        if (!strstr(linha, id)) { //Se strstr() retornar NULL, significa que id não foi encontrado em linha
            fputs(linha, temp); //verificar se a string id está contida na string linha
        }
    }

    fclose(origem);
    fclose(temp);

    remove(subArquivo); //excluir um arquivo
    rename("temp.csv", subArquivo); //renomear o arquivo temporário temp.csv para o nome do arquivo subArquivo
}

