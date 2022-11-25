#include <unistd.h>
#include <stdlib.h>
#include "stdes.h"
int main (int argc, char **argv)

    { 
    FICHIER *f1;
    f1 = ouvrir (argv[1], 'E');
    if (f1 == NULL) exit (-1);
    fecriref (f1, "%c", 'e');
    fermer (f1);
}