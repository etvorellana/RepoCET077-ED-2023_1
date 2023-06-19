typedef struct
{
    int key;
    float val;
} TInfo;

typedef TInfo *PInfo;

struct noArvBin
{
    TInfo info;
    int nivel;
    struct noArvBin *esq;
    struct noArvBin *dir;
};

typedef struct noArvBin TNoArvBin;
typedef TNoArvBin *PNoArvBin;

PNoArvBin newNoArvBin();
PNoArvBin insereNoArvBin(PNoArvBin arv, TInfo info, int nivel);
void printArv(PNoArvBin arv, int tipo);
PNoArvBin removeNoArvBin(PNoArvBin arv, TInfo info);