#define CSVSIZE 13000

typedef struct
{
  int Position;
  long long int Key;
  char *ArtistName;
  char *SongName;
  int Days;
  float Top10Times;
  int PeakPosition;
  char *PeakPositionXtimes;
  int PeakStreams;
  int TotalStreams;
} TSongs;

TSongs* carregaDados(char *filename, int *tam);
void limpaAcervo(TSongs *acervo, int tam);
TSongs* sub_lista( TSongs *ponteiro, int tam, int *total);
int IncRegistro(TSongs song, TSongs *lista, int *tam);
int BuscaPorRank(int R, TSongs *lista, int tam);
int RemRegistro(TSongs song, TSongs *lista, int *tamaux);
int buscaBinPorPOSICAO(int position, TSongs* lista, int inicio, int tam);
int buscaBinporPOSICAOi(int position, TSongs* lista, int tam);
int RemRegistro_nao_ordenado(TSongs song, TSongs *lista, int *tamaux);
int RemRegistro_ordenado(TSongs song, TSongs *lista, int *tamaux);