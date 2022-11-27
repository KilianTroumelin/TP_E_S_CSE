#include "stdes.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

FICHIER *ouvrir(const char *nom, char mode){
    FICHIER *file=malloc(sizeof(FICHIER));
        file->file_buffer=(void *) malloc(BUFFER_SIZE);
        file->current_pos=0;
        if (mode =='L'){
            file->file_descriptor=open(nom, O_RDONLY, 00777);
            file->buff_size=read(file->file_descriptor, file->file_buffer, BUFFER_SIZE);
            file->mode='L';
        }
        else if (mode =='E')
        {
            file->file_descriptor=open(nom, O_WRONLY | O_CREAT, 00777);
            file->buff_size=0;
            file->mode='E';
        }
        else
            return 0;
    return file;
}

int fermer(FICHIER*f){
    vider(f);
    fcntl(f->file_descriptor, O_RDWR);
    close(f->file_descriptor);
    free(f);
    return 0;
}

int lire(void *p, unsigned int taille, unsigned int nbelem, FICHIER *f){
    if(f->buff_size==0) return 0;
    unsigned int nbBytes=taille*nbelem;
    if (nbBytes>(f->buff_size-f->current_pos)){
        memcpy(p, f->file_buffer+f->current_pos, f->buff_size-f->current_pos);
        int bwrite=f->buff_size-f->current_pos;
        f->current_pos+=bwrite;
        int rest=read(f->file_descriptor, p+bwrite, nbBytes-bwrite);
        f->buff_size=read(f->file_descriptor, &f->file_buffer[0], BUFFER_SIZE);
        f->current_pos=0;
        return ((bwrite+rest)/taille);
    }else
    {
        memcpy(p, f->file_buffer+f->current_pos, nbBytes);
        f->current_pos+=nbBytes;
        if (f->current_pos>=f->buff_size){
            f->buff_size=read(f->file_descriptor, &f->file_buffer[0], BUFFER_SIZE);
            f->current_pos=0;
        }
    return nbelem;
    }
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
    if (f->buff_size!=0 && f->mode!='L')
        n=write(f->file_descriptor, f->file_buffer, f->buff_size);
    f->buff_size=0;
    f->current_pos=0;
    return n;
}

char *_strrev(char *str)
{
    int i;
    int len = 0;
    char c;
    if (!str)
        return NULL;
    while (str[len] != '\0')
    {
        len++;
    }
    for (i = 0; i < (len / 2); i++)
    {
        c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
    return str;
}

char *__itoa(int i, char *strout, int base)
{
    
    char *str = strout;
    if (i==0){
        str[0]='0';
        str[1]='\0';
        return strout;
    }
    int digit, sign = 0;
    if (i < 0)
    {
        sign = 1;
        i *= -1;
    }
    while (i)
    {
        digit = i % base;
        *str = (digit > 9) ? ('A' + digit - 10) : '0' + digit;
        i = i / base;
        str++;
    }
    if (sign)
    {
        *str++ = '-';
    }
    *str = '\0';
    _strrev(strout);
    return strout;
}

int fecriref (FICHIER *f, const char *format, ...){
    va_list ap;
    int wr_char=0;
    va_start(ap, format);
    while (*format != '\0'){
        if (*format!='%')
        {
            ecrire(format, 1,1,f);
            format++;
            wr_char+=1;
            continue;
        }
        format++;
         switch (*format) {
        case 'c':              // char 
            char c =  va_arg(ap, int);
            ecrire(&c, sizeof(char), 1, f);
            format++;
            wr_char+=1;
            break;
        case 'd':              // int 
            int v = va_arg(ap, int);
            char str_itoa[10];
            if (v==0)
            {
                char n='0';
                ecrire(&n, 1, 1, f);
                format++;
                wr_char+=1;
                break;
            }else {            
            __itoa(v,str_itoa,10);
            int l=strlen(str_itoa);
            ecrire(str_itoa, l, 1, f);}
            format++;
            wr_char+=strlen(str_itoa);
            break;
        case 's':              // string 
            char *str = va_arg(ap, char*);
            ecrire(str, strlen(str), 1 , f);
            format++;
            wr_char+=strlen(str);
            break;
        }
    }
    va_end(ap);
    return wr_char;
}

/* directly in stdout */
int ecriref (const char *format, ...){
    va_list ap;
    int wr_char=0;
    va_start(ap, format);
    while (*format != '\0'){
        if (*format!='%')
        {
            ecrire(format, 1,1,stdout);
            format++;
            wr_char ++;
            continue;
        }
        format++;
         switch (*format) {
        case 'c':              // char 
            char c =  va_arg(ap, int);
            wr_char+=ecrire(&c, sizeof(char), 1, stdout);
            format++;
            break;
        case 'd':              // int 
            int v = va_arg(ap, int);
            char str_itoa[10];
            if (v==0)
            {
                char n='0';
                ecrire(&n, 1, 1, stdout);
                format++;
                wr_char+=1;
                break;
            }else { 
            __itoa(v,str_itoa,10);
            int l=strlen(str_itoa);
            ecrire(str_itoa, l, 1, stdout);
            format++;
            wr_char+=strlen(str_itoa);
            break;
            }
        case 's':              // string 
            char *str = va_arg(ap, char*);
            ecrire(str, strlen(str), 1 , stdout);
            format++;
            wr_char+=strlen(str);
            break;
        }
    }
    char nul='\0';
    ecrire(&nul, 1,1,stdout);
    wr_char+=1;
    va_end(ap);
    vider(stdout);
    return wr_char;
}

int fliref (FICHIER *f, const char *format, ...){
/*   va_list vl;
    int i = 0,j=0;
    va_start(vl, format);
    while (format && format[i])
    {
        if (format[i] == '%')
        {
            i++;
            switch (format[i])
            {
            case 'c':
            {
                char *c = va_arg(vl, char *);
                lire(c, sizeof(*c), 1, f);
                i++;
                break;
            }
            case 'd':
            {
                int *v = va_arg(vl, int *);
                int bool = 1;
                char str[10];
                int j = 0;
                while (bool == 1)
                {
                    lire(&str[j], 1, 1, f);
                    if (str[j] == format[i + 1])
                    {
                        str[j] = '\0';
                        bool = 0;
                    }
                    else
                        j++;
                }
                *v = atoi(str);
                i++;
            }
            case 's':
            {
                int bool = 1;
                char *temp = va_arg(vl, char *);
                int j = 0;

                while (bool == 1)
                {
                    lire(&temp[j], 1, 1, f);

                    if (temp[j] == format[i + 1])
                    {
                        temp[j] = '\0';
                        bool = 0;
                        f->current_pos--;
                    }
                    else
                        j++;
                }
                i++;
            }
            default:
            {
                char c[1];
                lire(c, 1, 1, f);
                i++;
                break;
            }
            }
        }
        else
        {
            char c[1];
            lire(c, 1, 1, f);
            i++;
        }
        j++;
    }
    va_end(vl);
    return j;*/
    return 0;
}