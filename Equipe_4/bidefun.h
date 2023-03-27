#define CSVSIZE 13000

typedef struct
{
  int Position;
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