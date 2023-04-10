#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<dataFun.h>

int main() {
    int tam;

    t_Fipe *fipe = carregaDados("fipe.csv", &tam);

    if (!fipe) {
        printf("Erro ao carregar dados!\n");
        return 1;
    }

    printf("Dados carregados com sucesso!\n");
    printf("Total de registros carregados: %d\n", tam);

    printLista(fipe, tam);

    /*Exemplo de inclusão de registro
    t_Fipe novoRegistro;
    novoRegistro.nCdg = "12345";
    novoRegistro.codigofp = "4321";
    novoRegistro.marca = "Exemplo";
    novoRegistro.modelo = "Carro Exemplo";
    novoRegistro.anoModelo = 2023;
    novoRegistro.mesReferencia = 4;
    novoRegistro.anoReferencia = 2023;
    novoRegistro.valor = 100000.00;*/

    int pos = incRegistro(novoRegistro, fipe, &tam);
    printf("Registro inserido na posição: %d\n", pos);

    // Exemplo de busca e remoção de registro
    char idBusca[25];
    int indice = buscaPorId(fipe, tam, idBusca);

    if (indice != -1) {
        printf("Registro encontrado na posição: %d\n", indice);
        printRegistro(fipe[indice]);

        int pos_removida = remRegistro(idBusca, fipe, &tam);
        printf("Registro removido da posição: %d\n", pos_removida);
    } else {
        printf("Registro não encontrado!\n");
    }

    /*Exemplo de inclusão ordenada
    t_Fipe novoRegistroOrd;
    novoRegistroOrd.nCdg = "11111";
    novoRegistroOrd.codigofp = "2222";
    novoRegistroOrd.marca = "Exemplo Ordenado";
    novoRegistroOrd.modelo = "Carro Exemplo Ordenado";
    novoRegistroOrd.anoModelo = 2023;
    novoRegistroOrd.mesReferencia = 4;
    novoRegistroOrd.anoReferencia = 2023;
    novoRegistroOrd.valor = 120000.00;*/

    int pos_ord = incRegOrd(novoRegistroOrd, fipe, &tam);
    printf("Registro inserido ordenadamente na posição: %d\n", pos_ord);

    limpaFipe(fipe, tam);

    return 0;
}
