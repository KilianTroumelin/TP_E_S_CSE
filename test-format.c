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


  FICHIER *f1, *f2;
  int n;
  if (argc != 3) exit (-1);

  f1 = ouvrir (argv[1], 'E');
  if (f1 == NULL) exit (-1);

  n = fecriref (f1, "Test char: '%c' and string: '%s' with normal number 12\n", 'a', "bonjour");
  ecriref("%d\n", n);
  fecriref (f1, "Test number: '%d' char written on the above line\n", n);

  for (n=-11;n<11;n++)
    fecriref (f1, "%d ", n);
  fecriref (f1, "\n", n);

#if 0
  /* Error, as expected: */
  fecriref (f1, "Num: '%e'\n");
#endif
  
  fermer (f1);

  {
    char c;
    int  d;
    char my_word[128];
    f2 = ouvrir (argv[2], 'L');
    fliref (f2, "  test  %c end %s", &c, my_word);
    ecriref ("Read '%c' and '%s' from %s\n", c, my_word, argv[2]);
    fliref (f2, "end %d %s", &d, my_word);
    ecriref ("Now read '%d' and '%s' from %s\n", d, my_word, argv[2]);

    fermer (f2);
  }
  return 0;
}
