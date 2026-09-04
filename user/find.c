#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char* argv,char* target)
{
   char buf[512], *p,*temp;
   int fd;
   struct dirent de;
   struct stat st;
   struct stat child_st;

   if((fd = open(argv,0)) < 0){
    printf("find: cannot open %s\n",argv);
     return;
   }

   if(fstat(fd, &st) < 0){
    printf("find: cannot stat %s\n",argv);
     close(fd);
      return;
   }

   switch(st.type){

     case T_DIR:
       if(strlen(argv) + 1 + DIRSIZ + 1 > sizeof buf)
        {
          printf("find: path too long\n");
          break;
        }
          strcpy(buf,argv);
          p = buf + strlen(buf);
          *p++ = '/';
	  temp = p;

            while(read(fd,&de,sizeof(de)) == sizeof(de))
              {
                 if(de.inum == 0)
                 continue;
		 if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0)
		 continue;
                 memmove(p,de.name,DIRSIZ);
                 p[DIRSIZ] = 0;
		 p = temp;

                 if(stat(buf,&child_st) < 0)
                  {
	            printf("find: cannot stat %s\n",buf);
	            continue;
                  }

                if(strcmp(de.name,target) == 0)
                 {
	           printf("%s\n",buf);
	           continue;
                 }

                if(st.type == T_DIR)
                 {
	           find(buf,target);
                 }
		
               }
            break;     
	}
       close(fd);
}


void main(int argc,char* argv[])
{
	if(argc != 3)
	{ 
          printf("ERROR!\n");
	  exit(0);
	}

	find(argv[1],argv[2]);

	exit(0);

}
