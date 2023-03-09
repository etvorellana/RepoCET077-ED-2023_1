
/*
    a função int2bin() recebe um valor inteiro e retorna 
    uma string contendo a sequencia de 0 e 1 que representa
    o valor fornecido em binário  
*/
char* int2bin(int n);

/*
    a função sucessor() recebe um valor inteiro e retorna o
    sucessor do mesmo
*/
int sucessor(int n);

/*
    a função predecessor() recebe um valor inteiro e retorna o
    predecessor do mesmo
*/
int predecessor(int n);

/*
    a função soma() recebe dois valores inteiros e retorna a
    soma dos mesmos. Implementa esta função de forma recursiva
    utilizando as funções sucessor e predecessor
*/
int soma(int a, int b);

/*
    a função fibonacciRec() recebe um valor inteiro e retorna o
    n-esimo termo da sequencia de Fibonacci. Utilize uma 
    implementação recursiva
*/
int fibonacciRec(int n);

/*
    a função fibonacci() recebe um valor inteiro e retorna o
    n-esimo termo da sequencia de Fibonacci. Utilize uma 
    implementação não recursiva
*/
int fibonacci(int n);

/*
    a função somaN() recebe um valor inteiro e retorna a soma 
    dos n primeiros números inteiros
*/
int somaN(int n);

/*
    a função randArray() recebe um valor inteiro n e dois 
    valores inteiros a e b, e retorna o endereço de um array 
    de inteiros alocado dinamicamente com n posições. O array
    é preenchido com valores inteiros gerados de forma 
    aleatória no intervalo a <= x <= b  
*/
int* randArray(int n, int a, int b);

/*
    a função vetMax() recebe um ponteiro para um array de 
    inteiros de tamanho n e retorna a maior valor de do 
    array
*/
int vetMax(int* vet, int n);

/*
    a função vetSoma() recebe um ponteiro para um array de 
    inteiros de tamanho n e retorna a soma dos elementos do 
    array
*/
int vetSoma(int* vet, int n);

/*
    a função valInVet() recebe um valor inteiros e o ponteiro
    para um array de inteiros de tamanho n e retorna verdadeiro 
    (1) se o valor fizer parte do array e falso (0) caso 
    contrario 
*/
int valInVet(int val, int* vet, int n);

/*
    a função posValInVet() recebe um valor inteiros e o ponteiro
    para um array de inteiros de tamanho n e retorna um valor pos,
    0 <= pos < n, se o valor fizer parte do array onde pos é o
    índice do array onde se encontra este valor. Caso contrario
    retorna n;
*/
int posValInVet(int val, int* vet, int n);