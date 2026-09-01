#include "kernel/types.h"
#include "user/user.h"

int p1[2],p2[2];


int 
main(void)
{
   char ch;
   pipe(p1);
   pipe(p2);

   int pid = fork();

   if(pid == 0)
   {
      close(p1[1]);
      read(p1[0],&ch,1);
      close(p1[0]);
      printf("%d: received ping\n",getpid());
      close(p2[0]);

      write(p2[1],"pong",1);
      close(p2[1]);
      exit(0);

   }
   else
   {
      close(p1[0]);
      write(p1[1],"ping",1);
      close(p1[1]);
      
      close(p2[1]);
      read(p2[0],&ch,1);
      close(p2[0]);
      printf("%d: received pong\n",getpid());
   }
   exit(0);
}
