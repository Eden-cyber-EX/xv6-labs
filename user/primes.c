#include "kernel/types.h"
#include "user/user.h"



void primer(int fd)
{
  int primes;
  int n_p[2];
  if(read(fd,&primes,sizeof(int)) <= 0){
	  close(fd);
	  return;
  }
  int n = primes;
  printf("prime %d\n",n);  
  
  pipe(n_p);
  int pid = fork(); 

   if(pid == 0)
     {
      close(n_p[1]);
      close(fd);
      primer(n_p[0]);
      close(n_p[0]);
      exit(0);
     }
     else
     {
         close(n_p[0]);
 	 while(read(fd,&primes,sizeof(int)) > 0)
        {
  	 if(primes % n == 0){
	 }
 	 else{
    	 write(n_p[1],&primes,sizeof(int));
         }
	}
	 close(n_p[1]);
	 close(fd);
         wait(0);
     }
     
     
}


int main(void)
{
   int p[2];
   pipe(p);
   int pid = fork();
   if(pid == 0)
   {
      close(p[1]);
      primer(p[0]);
      close(p[0]);
      exit(0);
   }else
   {
    close(p[0]);
    for(int i = 2;i <= 35;i++)
    {
      write(p[1],&i,sizeof(int));
    }
    close(p[1]);
    wait(0);
   }
  exit(0);
}
