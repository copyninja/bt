#include "arg.h"

#include <stdlib.h>
#include <stdio.h>

char *argv0;

void usage()
{
     fprintf(stderr, "usage: bt -v -f filename\n");
}

char *slurp(char *f)
{
     FILE *in = fopen(f, "r");
     long fsize;
     char *str;

     fseek(in, 0, SEEK_END);
     fsize = ftell(in);
     rewind(in);

     str = (char *)malloc(fsize * sizeof(char));
     fread(str, sizeof(char), fsize, in);
     fclose(in);

     return str;
}

int main(int argc, char *argv[])
{
     char *f;
     char *metainfo;
  
     ARGBEGIN{
     case 'f':
	  f = ARGF();
	  metainfo = slurp(f);
	  fprintf(stderr, "%s\n", metainfo);
	  break;
     case 'v':
     default:
	  usage();
	  exit(1);
     } ARGEND;
}
