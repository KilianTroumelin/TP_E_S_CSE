#include "stdes.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

FICHIER *ouvrir(const char *nom, char mode){
    FICHIER *file=malloc(sizeof(FICHIER));
        file->file_buffer=(char *) malloc(1024);
        file->current_pos=0;
        if (mode =='L'){
            file->file_descriptor=open(nom, O_RDONLY);
            file->buff_size=(long) read(file->file_descriptor, file->file_buffer, 1024);
            file->mode = 'L';
        }
        else {
            if (mode =='E')
            {
                file->file_descriptor=open(nom, O_WRONLY);
                file->buff_size=0;
                file->mode='E';
            }
            else
                return 0;
        }
    return file;
}

int fermer(FICHIER*f){
    vider(f);
    int i = close(f->file_descriptor);
    free(f);
    return i;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
    unsigned int tot=taille*nbelem;
    if (tot>1024)
        f->buff_size=read(f->file_descriptor, p, tot);
    if (tot>1024-f->current_pos){
        memcpy(f->file_buffer, p+f->current_pos, (f->file_buffer+f->current_pos)-f->file_buffer);
        memcpy(f->file_buffer, f->file_buffer+1024-f->current_pos, 1024-f->current_pos);
        f->current_pos=1024-f->current_pos;
        f->buff_size=read(f->file_descriptor, f->file_buffer+f->current_pos, 1024-f->current_pos);
    }

    memcpy((char *) p+f->current_pos,(char *) f->file_buffer+f->current_pos, tot);
    f->current_pos+=tot;
    f->buff_size-=tot;
    if (f->buff_size<0)
        return 0;
    return nbelem;
}

int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
    unsigned int tot=taille*nbelem;
    int n;
    if (tot>1024)
        return write(f->file_descriptor, p, taille*nbelem)/taille;
    if (tot>1024-f->current_pos)
        n=vider(f);
    memcpy(f->file_buffer+f->current_pos, p+f->current_pos, tot);
    f->current_pos+=tot;
    f->buff_size+=tot;
    return nbelem;
}

int vider(FICHIER *f){
    int n=f->buff_size;
    if (f->mode != 'L')
        n=write(f->file_descriptor, f->file_buffer, f->buff_size);
    f->current_pos=0;
    f->buff_size=0;
    return n;
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