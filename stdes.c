#include "stdes.h"
#include <fcntl.h>
#include <stdlib.h>


FICHIER *ouvrir(const char *nom, char mode){
    FICHIER *file=malloc(sizeof(FICHIER));
        file->file_buffer=malloc(1024);
        if (mode =='L'){
            file->file_descriptor=open(nom, O_RDONLY);
            
        }if (mode =='R')
            file->file_descriptor=open(nom, O_WRONLY);
        else
            return 0;
    return file;
}

int fermer(FICHIER*f){
    int i = close(f);
    free(f);
    return i;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
    read(&f->file_descriptor, &f->file_buffer, 1024);
    unsigned int tot=taille*nbelem;
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