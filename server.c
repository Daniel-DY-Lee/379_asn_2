#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define	MY_PORT	2222

/* ---------------------------------------------------------------------
 This	is  a sample server which opens a stream socket and then awaits
 requests coming from client processes. In response for a request, the
 server sends an integer number  such	 that  different  processes  get
 distinct numbers. The server and the clients may run on different ma-
 chines.
 --------------------------------------------------------------------- */

int main()
{
  int sock, snew, fromlength, number, outnum;
  struct sockaddr_in master, from;

  FILE *log;
  pid_t pid = 0;
  pid_t sid = 0;
  char logfile [100];
  char pidstr[20];
  int alwaystrue = 0;

  pid = fork();

  if (pid < 0)
    {
      printf("fork failed!\n");
      exit(1);
    }
  
  if (pid > 0)
    {
      /// in the parent, print error message and exit
      printf("pid of child process %d \n", pid);
 
      sprintf (pidstr, "%d", pid);
      strcpy (logfile, "server379");
      strcat (logfile, pidstr);
      strcat (logfile, ".log");
      log = fopen (logfile, "w");
      exit (0);
    }
  
  // Anything that happens here is the child process
  umask(0);

  sid = setsid(); /// Don't want it to look like an orphan
   
  if(sid < 0)
    {
      perror ("Cannot create new process group");
      exit(1);
    }

  if (chdir("/") < 0) { /// Change the curent working diretory
    printf ("Could not change working directory to /\n");
    exit (1);
  }


  // ------------ modified code -------------------------



  //  int optval = 1;
  //setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));

  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror ("Server: cannot open master socket");
    exit (1);
    }
  
  master.sin_family = AF_INET;
  master.sin_addr.s_addr = INADDR_ANY;
  master.sin_port = htons (MY_PORT);
  
  if (bind (sock, (struct sockaddr*) &master, sizeof (master))) {
    perror ("Server: cannot bind master socket");
    exit (1);
  }
  
  number = 0;
  
  listen (sock, 5);

  while (1) {
    fromlength = sizeof (from);
    snew = accept (sock, (struct sockaddr*) & from, & fromlength);
    if (snew < 0) {
      perror ("Server: accept failed");
      exit (1); /// Starting from else if is modified code
    } else  {
      perror ("i\n");
      fprintf (log, "Server has accepted a client\n");
    }
    fprintf (log, "Sending the number: %d\n", number);
    outnum = htonl (number);
    write (snew, &outnum, sizeof (outnum));
    close (snew);
    number++;
  }

  fclose(log);

  return(0);

}
//QQQ
