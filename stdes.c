#include "stdes.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

FICHIER *ouvrir(const char *nom, char mode){
    FICHIER *file=malloc(sizeof(FICHIER));
        file->file_buffer=malloc(1024);
        if (mode =='L'){
            file->file_descriptor=open(nom, O_RDONLY);
            read(file->file_descriptor, file->file_buffer, 1024);}
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
    unsigned int tot=taille*nbelem;
    if (tot>1024)
        return 0;
    if (tot>1024-f->current_pos){
        memcpy(f->file_buffer, p, (f->file_buffer+f->current_pos)-f->file_buffer);
        // write dans le buffer utilisateur et déplacement du reste du buffer
        memcpy(f->file_buffer, f->file_buffer+1024-f->current_pos, 1024-f->current_pos);
        f->current_pos=1024-f->current_pos;
        read(f->file_descriptor, f->file_buffer+f->current_pos, 1024-f->current_pos);
        for (unsigned int i = 0; i < tot; i++)//copy des octets
        {
            memcpy(f->file_buffer+f->current_pos, p+f->current_pos, 1);
            f->current_pos+=1;    
        }
    }
    for (unsigned int i = 0; i < tot; i++)//copy des octets
    {   memcpy(f->file_buffer+f->current_pos, p+f->current_pos, 1);
        f->current_pos+=1;    }

    return nbelem;
}

int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
return 0;
}

int vider(FICHIER *f){
    f->current_pos=0;
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