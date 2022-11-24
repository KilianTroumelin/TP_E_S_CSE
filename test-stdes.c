#include <stdlib.h>
#include "stdes.h"

int main(int argc, char *argv[])
{
    char c;
    FICHIER *f1=ouvrir("/home/vmubuntu/TP_ES-20221118/TP_E_S_CSE/test_file.txt", 'L');
    FICHIER *f2=ouvrir("/home/vmubuntu/TP_ES-20221118/TP_E_S_CSE/test_dest.txt", 'E');
    
    while (lire (&c, 1, 1, f1) == 1) {
        ecrire (&c, 1, 1, f2);      
	}
    fermer(f1);
    fermer(f2);
}