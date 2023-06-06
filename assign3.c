#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>
void main()
{
  char s1 [1024], s2[1024];

  int fd1,n,fd2 [2], pid;
  fd1= open("t1.txt", O_RDONLY, 0764); //a.txt is an existing file
  n=read (fd1,s1, sizeof(s1));
  pipe(fd2);
  pid = fork();
  if (pid ==-1)
  {
    printf("unsuccessful process creation\n");
    exit(1);
  }
  else if (pid==0) // in child process
  {
    close (fd2[1]);
    n=read (fd2[0], s2, sizeof(s2));
    s2[n]='\0';
    printf("\n reading from pipe \n");
    puts(s2);
  }
  else // in parent process
  {
    close(fd2[0]);
    write(fd2[1],s1,n);
  }
}
