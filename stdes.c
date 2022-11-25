#include "stdes.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

#define BUFFER_SIZE 1024

FICHIER *ouvrir(const char *nom, char mode){
    FICHIER *file=malloc(sizeof(FICHIER));
        file->file_buffer=(void *) malloc(BUFFER_SIZE);
        file->current_pos=0;
        if (mode =='L'){
            file->file_descriptor=open(nom, O_RDONLY);
            file->buff_size=read(file->file_descriptor, file->file_buffer, BUFFER_SIZE);
            file->mode='L';
        }
        else if (mode =='E')
        {
            file->file_descriptor=open(nom, O_WRONLY);
            file->buff_size=0;
            file->mode='E';
        }
        else
        return 0;
    return file;
}

int fermer(FICHIER*f){
    vider(f);
    free(f->file_buffer);
    free(f);
    return close(f->file_descriptor);
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
   if(f->buff_size==0) return 0; 
   unsigned int nbBytes=taille*nbelem;
       if (nbBytes>BUFFER_SIZE){
        memcpy(p,f->file_buffer, f->current_pos);
        vider(f);
        f->buff_size=read(f->file_descriptor, p, nbBytes);
        return f->buff_size/taille;
    }else if (nbBytes>BUFFER_SIZE-f->current_pos){
        memcpy(p, f->file_buffer,f->current_pos);
        memcpy(f->file_buffer, f->file_buffer+f->current_pos, BUFFER_SIZE-f->current_pos);
        f->current_pos=BUFFER_SIZE-f->current_pos;
        f->buff_size=read(f->file_descriptor, f->file_buffer+f->current_pos, BUFFER_SIZE-f->current_pos);
        f->current_pos=0;
    }
    memcpy(p, f->file_buffer+f->current_pos, nbBytes);
    f->current_pos+=nbBytes;
    if (f->current_pos==f->buff_size){
        f->buff_size=read(f->file_descriptor, f->file_buffer, BUFFER_SIZE);
        f->current_pos=0;
    }
    return nbelem;
}

int ecrire(const void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
    unsigned int nbBytes=taille*nbelem;
    if (nbBytes>BUFFER_SIZE){
        vider(f);
        write(f->file_descriptor, p, nbBytes);
        return nbelem;
    }
    if (nbBytes>BUFFER_SIZE-f->buff_size)
        vider(f);
    memcpy(f->file_buffer+f->buff_size, p, nbBytes);
    f->buff_size+=nbBytes;
    return nbelem;
}

int vider(FICHIER *f){
    int n=0;
    if (f->mode=='E')
        n=write(f->file_descriptor, f->file_buffer, f->buff_size);
    f->buff_size=0;
    f->current_pos=0;
    return n;
}

int fecriref (FICHIER *f, const char *format, ...){
    va_list ap;
    char r_char;
    size_t wr_char=0;
    char *temp_buffer=(char *) malloc(BUFFER_SIZE);
    int tb_pos=0;
    va_start(ap, format);
    while ((r_char=*format) != '\0'){
        format++;
        if (r_char!='%')
        {
            wr_char ++;
            continue;
        }
         switch (*format++) {
        case 'c':              // char 
            char *c = (char *) va_arg(ap, char *);
            //memcpy((char *) temp_buffer+tb_pos, c, sizeof(char));
            ecrire(c, sizeof(char), 1, f);
            wr_char+= 1;
            break;
        case 'd':              // int 
            int v = (int) va_arg(ap, int);
            //memcpy((char *) temp_buffer+tb_pos, &v, sizeof(int));
            ecrire(&v, 1, sizeof(int), f);
            
            wr_char+= 1;
            break;
        case 's':              // string 
            const char *str = (const char *) va_arg(ap, const char *);
            while (*str != '\0')
            {
                memcpy((char *) temp_buffer+tb_pos, str, sizeof(char));
                tb_pos+=1;
                wr_char+= 1;
            }
            break;
        }
    }
    ecrire(temp_buffer, 1, tb_pos, f);
    va_end(ap);
    return 0;
}

/* directly in stdout */
int ecriref (const char *format, ...){
return 0;
}

int fliref (FICHIER *f, const char *format, ...){
return 0;
}