#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NSIZE 1024

double* alocaArray(int n);
double** alocaMatryx(int n, int m);

void ini_ArrayR(double* array, int n);
void ini_Array(double* array, int n);
void iniMatrixR(double** matrix, int n, int m);
void iniMatrix(double** matrix, int n, int m);


int main(void)
{
    double* x;
    double** M;

    srand(time(NULL));
    x = alocaArray(NSIZE);
    M = alocaMatryx(NSIZE, NSIZE);

    return 0;
}

double* alocaArray(int n)
{
    double* array = (double*) malloc(n*sizeof(double));
    return array;
}

double** alocaMatryx(int n, int m)
{
    double** matrix = (double**) malloc(n*sizeof(double*));
    for(int i = 0; i < n; i++)
        matrix[i] = alocaArray(m);
        //matrix = (double*) malloc(m*sizeof(double));
    return matrix;
}


/*
    matrix[i][j] --> matrix[k] onde
        - se por linhas  k = i*m + j
        - se por colunas k = j*n + i
*/
double* alocaMatryxAsArray(int n, int m)
{
    double* matrix = (double*) malloc(n*m*sizeof(double));
    return matrix;
}

void ini_ArrayR(double* array, int n)
{   
    if(n > 0)
    {
        array[--n] = (double) rand() / RAND_MAX;
        ini_ArrayR(array, n);
    }
}

void ini_Array(double* array, int n)
{   
    for(int i = 0; i < n; i++)
        array[i] = (double) rand() / RAND_MAX;
}


void iniMatrixR(double** matrix, int n, int m)
{
    if(n > 0)
    {
        ini_ArrayR(matrix[--n], m);
        iniMatrixR(matrix, n, m);
    }
}

void iniMatrix(double** matrix, int n, int m)
{
    for(int i = 0; i < n; i++)
        //ini_Array(matrix[i], m);
    {
        for(int j = 0; j < m; j++)
            matrix[i][j] = (double) rand() / RAND_MAX;
    }
}

unsigned char* imageGray(int linhas, int colunas)
{
    unsigned char* img = malloc(linhas * colunas * sizeof(unsigned char));
    return img; 
}

void criaImagemGray(unsigned char* img, int linhas, int colunas)
{

    for(int i = 0; i < linhas*colunas, i += colunas)
        for(int j = 0; j < colunas; j++)
            img[i +  j] = (unsigned char) (rand()%256);
}

void limiariza(unsigned char* matrix, int n, int m, unsigned char limiar)
{
    for(int i = 0; i < n*m, i++)
        if (matrix[i] < limiar)
            matrix[i] = 0;
        else
            matrix[i] = 255;
}

unsigned char calcLimiar(unsigned char* matrix, int n, int m, unsigned char l0)
{
    int l1 = 0, l2 = 0;
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < n*m; i++)
    {
        if (matrix[i] < l0)
        {
            l1++;
            sum1 += matrix[i];
        }else{
            l2++;
            sum2 += matrix[i];
        }
    }
    l1 = sum1/l1;
    l2 = sum2/l2;
    return (unsigned char)(l1 + l2)/2;
}



int* geraHistograna(unsigned char* matrix, int n, int m)
{
    int* hist = (int*) calloc(256, sizeof(int));
    for(int i = 0; i < n*m; i++)
        hist[matrix[i]]++;
    return hist;
}

unsigned char calcLimiarHist(int* hist, unsigned char l0)
{
    int l1 = 0, l2 = 0;
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < l0; i++ )
    {
        l1 += hist[i];
       sum1 += i*hist[i];
    }
    for(int i = l0; i < 256; i++ )
    {
        l2 += hist[i];
       sum2 += i*hist[i];
    }
    1 = sum1/l1;
    l2 = sum2/l2;
    return (unsigned char)(l1 + l2)/2;
}