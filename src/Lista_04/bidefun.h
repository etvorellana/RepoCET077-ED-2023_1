#define CSVSIZE 12000
#define TRUE 1
#define FALSE 0

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

/* 
    Classe para representar uma lista 
    * Lista linear -> lista de tamanho fixo
    * Lista cheia -> cap == tam
    * Lista vazia -> tam == 0
    * Lista ordenada -> eOrd == TRUE
        * Se lista for ordenada o tamanho do array é igual a cap
        * Se lista não for ordenada o tamanho do array é igual a cap + 1
*/
typedef struct
{
    TBook* lista;   //Array para os registros da lista
    int cap;        //Capacidade da lista
    int tam;        //Tamanho da lista
    int eOrd;       //TRUE se for ordenada 
} TListaLinear;


/*
    Classe para representar uma pilha
    * Pilha linear -> pilha de tamanho fixo
    * Pilha cheia -> topo == cap
    * Pilha vazia -> topo == 0
    * Para empilhar (push) colocar no topo e 
        depois incrementar o topo
    * Para desempilhar (pop) decrementar o topo 
        e depois retornar o elemento do topo
*/
typedef struct
{
    TBook* pilha;   //Array para os registros pilha
    int cap;        //Capacidade da pilha
    int topo;       //Topo da pilha
}TPilhaLinear;

/*
    Classe para representar uma fila
    * Fila linear -> fila de tamanho fixo
    * Fila cheia -> fim - ini == cap
    * Fila vazia -> fim == ini
    * Para enfileirar (enqueue) colocar no fim e 
        depois incrementar o fim
    * Para desenfileirar (dequeue) incrementar o ini 
        e depois retornar o elemento do ini
*/
typedef struct
{
    TBook* fila;    //Array para os registros da fila
    int cap;        //Capacidade da fila
    int ini;        //Índice do primeiro elemento da fila
    int fim;        //Índice do último elemento da fila
} TFilaLinear;




/*
    Esta função aloca um array de tipo TBook e preenche 
    com registros extraídos do arquivo CSV. 
    Para utilizar esta função:
    * O arquivo CSV tem que existir e estar disponível
    para leitura no caminho especificado.

    Entrada
    * fileName: String com o caminho para o arquivo CSV
    * tam: ponteiro para quantidade de registros na lista
    Retorna
    * O ponteiro para o array criado. A capacidade do array 
    está definida na constante simbólica CSVSIZE. O tamanho
    da lista, a quantidade de registros nela armazenados, 
    é atualizada na variável tam
    * Casso não seja possível abrir o arquivo, retorna NULL

*/
TBook* carregaDados(char *fileName, int *tam);

/*
    Esta função libera a memória utilizada pelos 
    registros da lista e, posteriormente libera a
    memória utilizada pelo array;

    Entrada
    * acervo: ponteiro para o array da lista
    * tam: quantidade de registros na lista    
*/
void limpaAcervo(TBook *acervo, int tam);

/*
    Esta função libera a memória utilizada por um 
    registro de tipo TBook;

    Entrada
    * book: registro a ser liberado   
*/
void limpaRegistro(TBook book);

TBook* clonaBook(TBook book);

void cpyTBook(TBook src, TBook *dest);

void imprimeTBook(TBook book);

void impResumo(TBook book);

void imprimeAcervo(TBook *acervo, int tam);

/*
    Esta função faz uma busca na lista de tamanho tam
    pelo registro com campo isbn especifico.
    Para utilizar esta função:
    * A lista não precisa estar ordenada;
    * A lista não pode estar vazia
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
    * Um valor i entre 0 e tam (0 <= i < tam) se existir
    um registro com o valor de isbn procurado. O valor retornado
    representa o índice do elemento procurado na lista
    * O valor tam quando não existir nenhum registro na lista com
    o isbn procurado
*/

int buscaPorISBN(char *isbn, TBook* lista, int tam);

/* 
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
    Esta função aloca uma array do tamanho definido pela capacidade

    Entrada
    * capacidade: Tamanho que se deseja alocar para o array

    Retorna
    * Ponteiro para o endereço de memória alocado para o array
*/
TBook* criaAcervo(int capacidade);

TBook* criaAcervoOrd(int cap);

/*
    Esta função faz uma busca em uma lista ordenada, de 
    tamanho tam, pelo registro com campo isbn especifico.
    Para utilizar esta função:
    * A lista precisa estar ordenada;
    * A lista não pode estar vazia; 
    
    Entrada 
    * isbn: chave de busca
    * lista: ponteiro para o array da lista
    * tam: quantidade de registros na lista
    Retorna
    * Um valor i entre 0 e tam (0 <= i <= tam) 
    O valor retornado representa o índice da posição
    no array onde o elemento procurado "deve" estar.
    Entretanto o registro pode ou não estar nessa posição.
*/

int buscaOrdPorISBN(char *isbn, TBook* lista, int tam);

/* 
    Esta função faz uma inclusão numa lista ordenada, de 
    tamanho tam, de um novo registro. 
    Antes de chamar esta função o usuário deve verificar se:
    * A lista tem capacidade para um novo registro, ou seja, se
    o tamanho é menor que a capacidade;
    Entrada 
    * book: Registro que se deseja incluir
    * lista: ponteiro para o array da lista
    * tam: ponteiro para quantidade de registros na lista
    Retorna
    * Verdadeiro (1) se conseguir incluir o novo registro na lista.
    Novos elementos sempre serão incluídos mantendo a lista ordenada 
    e, após a inclusão, o tamanho da lista deve ser incrementado;  
    * Falso (0) se não for possível incluir o registro na lista. Um 
    registro não poderá ser incluído na lista se já existir nela 
    outro registro com o mesmo campo chave (isbn) 
*/

int incOrdRegistro(TBook book, TBook* lista, int* tam);

/* 
    Esta função faz uma remoção em uma lista ordenada, de 
    tamanho tam, do registro com campo chave isbn. 
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
    vazios no array nem alterar a ordenação da lista e, após a mesma, o 
    tamanho da lista deve ser decrementado;
    * Falso (0) se não for possível remover o registro da lista. Um 
    registro não poderá ser removido da lista se não existir nela 
    um registro com o campo chave especificado (isbn). 
*/

int remOrdRegistro(char* isbn, TBook* lista, int* tam);

// Para a lista do dia 10/04/2023

/*
    Esta função cria uma instância da classe TListaLinear com capacidade
    especificada e definindo se será uma lista ordenada ou não

    Entrada
    * cap: Capacidade da lista. 
        * Se a lista for não ordenada, o array será alocado com 
        tamanho cap+1;
        * Se a lista for ordenada, o array será alocado com tamanho cap;
    * eOrd: (0 ou 1) Indica se a lista será ordenada ou não;
        * 0: Lista não ordenada
        * 1: Lista ordenada
    Retorna
    * Ponteiro para a instância da classe TListaLinear criada
*/
TListaLinear* criaListaLinear(int cap, int eOrd);

/*
    Este é o método da classe TListaLinear que implementa 
    a busca pelo registro com campo isbn especifico.
    O método verifica se a lista está vazia 
    
    Entrada 
    * isbn: chave de busca
    * lista: ponteiro o objeto da classe
    Retorna
    * Um valor i entre 0 e tam (0 <= i <= tam) 
    O valor retornado representa o índice da posição onde
    o registro deve estar.
*/

int buscaNaLista(char* isbn, TListaLinear* lista);

/*
    Este é o método da classe TListaLinear que implementa 
    a inclusão de um registro especifico.
    O método verifica se a lista está vazia
    
    Entrada 
    * book: Registro que se deseja incluir
    * lista: ponteiro o objeto da classe
    Retorna
    * Verdadeiro (1) se conseguir incluir o novo registro na lista; 
    * Falso (0) se não for possível incluir o registro na lista;
*/

int insereNaLista(TBook book, TListaLinear* lista);

/*  
    Este é o método da classe TListaLinear que implementa 
    a remoção de um registro com campo isbn especifico.
    O método verifica se a lista está vazia

    Entrada 
    * isbn: Registro que se deseja remover
    * lista: ponteiro o objeto da classe
    Retorna
    * O ponteiro para o registro que foi removido da lista. 
*/
TBook* removeDaLista(char* isbn, TListaLinear* lista);

// Para a lista do dia 17/04/2023

/*
    Esta função cria uma instância da classe TFilaLinear com capacidade
    especificada

    Entrada
    * cap: Capacidade da lista. 
    Retorna
    * Ponteiro para a instância da classe TFilaLinear criada
*/

TFilaLinear* criaFilaLinear(int cap);

/*
    Esta função cria uma instância da classe TPilhaLinear com capacidade
    especificada

    Entrada
    * cap: Capacidade da lista. 
    Retorna
    * Ponteiro para a instância da classe TPilhaLinear criada
*/

TPilhaLinear* criaPilhaLinear(int cap);

/*
    Este é o método da classe TFilaLinear que implementa 
    a inclusão de um registro especifico.
    O método verifica se a fila está cheia
    
    Entrada 
    * book: Registro que se deseja incluir
    * fila: ponteiro o objeto da classe
    Retorna
    * Verdadeiro (1) se conseguir incluir o novo registro na fila; 
    * Falso (0) se não for possível incluir o registro na fila;
*/


int insereNaFila(TBook book, TFilaLinear* fila);

/*
    Este é o método da classe TPilhaLinear que implementa 
    a inclusão de um registro especifico.
    O método verifica se a pilha está cheia
    
    Entrada 
    * book: Registro que se deseja incluir
    * pilha: ponteiro o objeto da classe
    Retorna
    * Verdadeiro (1) se conseguir incluir o novo registro na pilha; 
    * Falso (0) se não for possível incluir o registro na pilha;
*/

int insereNaPilha(TBook book, TPilhaLinear* pilha);

/*
    Este é o método da classe TFilaLinear que implementa 
    a remoção de um registro da fila.
    O método verifica se a fila está vazia

    Entrada 
    * fila: ponteiro o objeto da classe
    Retorna
    * O ponteiro para o registro que foi removido da fila. 
*/


TBook* removeDaFila(TFilaLinear* fila);

/*
    Este é o método da classe TPilhaLinear que implementa 
    a remoção de um registro da pilha.
    O método verifica se a pilha está vazia

    Entrada 
    * pilha: ponteiro o objeto da classe
    Retorna
    * O ponteiro para o registro que foi removido da pilha.
*/

TBook* removeDaPilha(TPilhaLinear* pilha);

