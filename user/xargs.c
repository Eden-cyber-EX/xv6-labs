#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"


void main(int argc,char* argv[])
{
   char buf[MAXARG];
   char temp[MAXARG];
   char ch;
   char* nargv[MAXARG];
   int idx = 0,i = 0,j = 0,nargc = 0;

   while(read(0,&ch,1) > 0)
   {
      buf[idx] = 0;
      if(ch == '\n')
         {
	   
           for(i = 1;i < argc;i++)
	   {
	      nargv[nargc] = argv[i];
	      nargc++;
	   }
           i = 0;
	   while(i < idx)
	   {
	      if(buf[i] == ' ' || buf[i] == '\t')
	      {
		 i++;
	      }
	      else
	      {
                 j = i;
		 while(j < idx && buf[j] != ' ' && buf[j] != '\t')
		 {
		    j++;
		 }
		 
		 for(int IDX = i;IDX < j;IDX++)
		 {
	            temp[IDX] = buf[IDX];
		 }
		 temp[j] = 0; 
		 nargv[nargc++] = &temp[i];
		i = j; 
	      }
	   }
	   
           nargv[nargc] = 0;
	   int pid = fork();
	   if(pid == 0)
	   {
	      exec(nargv[0],nargv);
	      exit(1);
	   }
	   else
	   {
	      wait(0);
	      idx = 0;
	      nargc = 0;
	   }
	 }
      else 
	  buf[idx++] = ch;

		     
   }

   exit(0);
}
