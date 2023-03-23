#define CSVSIZE 12000

// Armazenando as informações de um libro de acordo com os campos de CSV
typedef struct
{
    int bookID;             // bookID - 1,
    char *title;            // title - Harry Potter and the Half-Blood Prince (Harry Potter  #6),
    char *authors;          // authors - J.K. Rowling/Mary GrandPré,
    float avgRating;        // average_rating - 4.57,
    char *isbn;          // isbn - 0439785960,
    char *isbn13;        // isbn13 - 9780439785969,
    char *lang;           // language_code - eng,
    int numPages;           // num_pages - 652,
    int ratCounts;          // ratings_count - 2095690,
    int txtRevCounts;       // text_reviews_count - 27591,
    char *pubDate;       // publication_date - 9/16/2006,
    char *publisher;        // publisher - Scholastic Inc.  
} TBook;

TBook* carregaDados(char *fileName, int *tam);
void limpaAcervo(TBook *acervo, int tam);


/*
    Esta função faz uma busca na lista de tamanho tam
    pelo registro com campo isbn especifico.
    Para utilizar esta função:
    * A lista não precisa estar ordenada;
    * Antes de chamar à função a chave procurada deve ser 
    copiada para o campo isbn da primeira posição não ocupada
    no final da lista (posição de índice tam); 
    * Para que a ação anterior seja possível o  array da lista 
    precisa possuir um elemento a mais do que a capacidade para 
    que quando a lista estiver cheia (tamanho == capacidade) 
    ainda seja possível realizar a busca
    
    Entrada 
    * isbn: chave de busca
    * lista: ponteiro para o array da lista
    * tam: quantidade de registros na lista
    Retorna
    * Um valor i entre 0 e tam (0 <= i < tam) se o existir
    um registro com o valor de isbn procurado. O valor retornado
    representa o índice do elemento procurado na lista
    * O valor tam quando não existir nenhum registro na lista com
    o índice procurado
*/

int buscaPorISBN(char *isbn, TBook* lista, int tam);

/* 
    Tarefa para a aula de 27/03/2023
    Esta função faz uma inclusão na lista, de tamanho tam,
    de um novo registro. 
    Antes de chamar esta função o usuário deve verificar se:
    * A lista tem capacidade para um novo registro, ou seja, se
    o tamanho é menor que a capacidade;
    Entrada 
    * book: Registro que se deseja incluir
    * lista: ponteiro para o array da lista
    * tam: ponteiro para quantidade de registros na lista
    Retorna
    * Verdadeiro (1) se conseguir incluir o novo registro na lista.
    Novos elementos sempre serão incluídos no final da lista (na 
    posição de índice tam) e após a inclusão o tamanho da lista deve
    ser incrementado;  
    * Falso (0) se não for possível incluir o registro na lista. Um 
    registro não poderá ser incluído na lista se já existir nela 
    outro registro com o mesmo campo chave (isbn) 
*/

int incRegistro(TBook book, TBook* lista, int* tam);

/* 
    Tarefa para a aula de 27/03/2023
    Esta função faz uma remoção na lista, de tamanho tam,
    do registro com campo chave isbn. 
    Antes de chamar esta função o usuário deve verificar se:
    * A lista não está vazia, ou seja, se o tamanho é maior que 
    zero;
    Entrada 
    * isbn: Registro que se deseja remover
    * lista: ponteiro para o array da lista
    * tam: ponteiro para quantidade de registros na lista
    Retorna
    * Verdadeiro (1) se conseguir remover o registro na lista. A 
    remoção de um registro do interior da lista não pode deixar espaços 
    vazios no array e, após a mesma, o tamanho da lista deve ser 
    decrementado;
    * Falso (0) se não for possível remover o registro da lista. Um 
    registro não poderá ser removido da lista se não existir nela 
    um registro com o campo chave especificado (isbn). 
*/

int remRegistro(char* isbn, TBook* lista, int* tam);

/*
    Tarefa para a aula de 27/03/2023
    Discutam nas modificações necessárias para implementar as 
    operações anteriores (busca, inclusão e remoção) no caso
    da lista estar ordenada pelo campo chave 
*/

