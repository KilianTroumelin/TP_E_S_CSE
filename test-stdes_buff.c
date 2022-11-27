#include "stdes.h"
#include <stdlib.h>
#include "temps.h"
#include <sys/time.h>
#include <sys/resource.h>
int main(int argc, char *argv[])
{
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
    printf("%lld \n", tempsprocess);
    return 0;
}