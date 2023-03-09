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