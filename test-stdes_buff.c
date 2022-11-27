#include "stdes.h"
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

long long int to_usec(struct timeval t) {
    return t.tv_sec*1000000LL + t.tv_usec;
}
int main(int argc, char *argv[])
{
    char *buf_stdout = malloc (sizeof(char) * BUFFER_SIZE);
    char *buf_stderr = malloc (sizeof(char) * BUFFER_SIZE);
    FICHIER stdout_s = {
        stdout->file_descriptor= 1, 
        stdout->file_buffer = buf_stdout,
        stdout->mode = 'E',
        stdout->current_pos = 0, 
        stdout->buff_size = 0
        };
    FICHIER stderr_s = {  
        stdout->file_descriptor = 2, 
        stdout->file_buffer = buf_stderr, 
        stdout->mode = 'E',
        stdout->current_pos = 0, 
        stdout->buff_size = 0
    };

    stdout = &stdout_s;
    stderr = &stderr_s;
    FICHIER *f1; //fichier pour lire
    FICHIER *f2; //fichier pour ecrire

    char c;
    struct timeval temps1;
    struct timeval temps2;

    if (argc != 3)
        exit(-1);
    gettimeofday(&temps1, NULL);
    f1 = ouvrir (argv[1], 'L');
    if (f1 == NULL)
        exit (-1);
    f2 = ouvrir (argv[2], 'E');
    if (f2 == NULL)
        exit (-1);
    while (lire (&c, 1, 1, f1) == 1) {
        ecrire (&c, 1, 1, f2);
    }
    fermer (f1);
    fermer (f2);
    gettimeofday(&temps2, NULL);
    long long int tps1 = to_usec(temps1);
    long long int tps2 = to_usec(temps2);
    long long int tempsprocess = tps2 - tps1;
    ecriref("%lld \n", tempsprocess);
    return 0;
}