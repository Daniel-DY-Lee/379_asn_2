#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

  FILE * fp;
  pid_t pid = 20;
  char test [100], * pids;
  
  sprintf (pids, "%d", pid);
  strcpy (test, "server379");
  strcat (test, pids);
  strcat (test, ".log");

  //  printf ("%s", test);

  fp = fopen (test, "w+");
  fprintf (fp, "I'M ALIVE!!!\n");
  return 0;

}
