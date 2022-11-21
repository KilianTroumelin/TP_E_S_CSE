#include <stdlib.h>
#include <fcntl.h>
#include "stdes.h"

int main(int argc, char *argv[])
{
    FICHIER *f1=ouvrir(argv[0], 'L');


    int i=open('/home/vmubuntu//TP_ES-20221118/TP_E_S_CSE/test_file.txt' , O_RDONLY);

}