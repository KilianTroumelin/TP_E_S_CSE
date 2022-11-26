#include <stdlib.h>
#include "stdes.h"


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

    char c;
    FICHIER *f1=ouvrir("/home/vmubuntu/TP_E_S_CSE/test_file.txt", 'L');
    FICHIER *f2=ouvrir("/home/vmubuntu/TP_E_S_CSE/test_dest.txt", 'E');
    int n=0;
    ecriref("%d\n", 0);
    while (lire (&c, 1, 1, f1) == 1) {
        n+=ecrire (&c, 1, 1, f2);     
	}
    ecriref("%d\n",n);
    fermer(f1);
    fermer(f2);
}