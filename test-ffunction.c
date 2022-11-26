#include <unistd.h>
#include <stdlib.h>
#include "stdes.h"

int main (int argc, char **argv)

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

    ecriref ("%d test %c test %s\n", 1023, 'z', "yo");
}