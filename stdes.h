

#ifndef _STDES_H
#define _STDES_H
#define BUFFER_SIZE 1280


struct _ES_FICHIER{
    int file_descriptor;
    char *file_buffer;
    int current_pos;
    long buff_size;
    char mode;
};



typedef struct _ES_FICHIER FICHIER;

extern FICHIER *stdout;
extern FICHIER *stderr;
char *itoa(int v, char * str);
int pw(int n,int p);
/* mode: 'L' = lecture, 'E' = écriture */
FICHIER *ouvrir(const char *nom, char mode);
int fermer(FICHIER*f);
int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f);
int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f);
int vider(FICHIER *f);

int fecriref (FICHIER *f, const char *format, ...);
/* directly in stdout */
int ecriref (const char *format, ...);
int fliref (FICHIER *f, const char *format, ...);

#endif

