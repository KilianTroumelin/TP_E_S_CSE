#include "stdes.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

FICHIER *ouvrir(const char *nom, char mode){
    FICHIER *file=malloc(sizeof(FICHIER));
        file->file_buffer=malloc(1024);
        if (mode =='L')
            file->file_descriptor=open(nom, O_RDONLY);
        if (mode =='R')
            file->file_descriptor=open(nom, O_WRONLY);
        else
            return 0;
    return file;
}

int fermer(FICHIER*f){
    int i = close(f->file_descriptor);
    free(f);
    return i;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
    read(f->file_descriptor, f->file_buffer, 1024);
    unsigned int tot=taille*nbelem;
    for (unsigned int i = 0; i < tot; i++)
    {
        p=f->file_buffer;
        p+=1;
        f->current_pos+=1;
    }
    
    
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