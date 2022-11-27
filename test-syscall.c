#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "temps.h"
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[])
{
    int f1; //fichier pour lire
    int f2; //fichier pour ecrire
    char c;

    struct timeval temps1;
    struct timeval temps2;

    if (argc != 3)
        exit(-1);

    gettimeofday(&temps1, NULL);
    f1 = open (argv[1], O_RDONLY);
    if (f1 == -1)
        exit (-1);
    f2 = open (argv[2], O_WRONLY|O_CREAT,0700);

    if (f2 == -1)
        exit (-1);
    while (read (f1, &c, 1) == 1) {
        write (f2, &c, 1);
    }

    close (f1);
    close (f2);
    gettimeofday(&temps2, NULL);
    long long int tps1 = to_usec(temps1);
    long long int tps2 = to_usec(temps2);
    long long int tempsprocess = tps2 - tps1;
    printf("%lld \n", tempsprocess);
    return 0;
}