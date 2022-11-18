#include "stdes.h"
#include <fcntl.h>

FICHIER *ouvrir(const char *nom, char mode){
FICHIER *file=malloc(sizeof(FICHIER));
    if (mode =='L')
        file->file_descriptor=open(nom, O_RDONLY);
    if (mode =='R')
        file->file_descriptor=open(nom, O_WRONLY);
    else
        return 0;
    
return &file;
}

int fermer(FICHIER*f){
    
return 0;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
return 0;
}

int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
return 0;
}

int vider(FICHIER *f){
return 0;
}

int fecriref (FICHIER *f, const char *format, ...){
return 0;
}

/* directly in stdout */
int ecriref (const char *format, ...){
return 0;
}

int fliref (FICHIER *f, const char *format, ...){
return 0;
}