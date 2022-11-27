#include "stdes.h"
#include <stdlib.h>

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



	FICHIER *f1;
	FICHIER *f2;
	char c;

	if (argc != 3)
		exit(-1);

	f1 = ouvrir (argv[1], 'L');
	if (f1 == NULL)
		exit (-1);

	f2 = ouvrir (argv[2], 'E');
	if (f2 == NULL)
		exit (-1);

	lire (&c, 1, 1500, f1);
          ecrire (&c, 1, 1500, f2);

        fermer (f1);
        fermer (f2);

	return 0;
}
