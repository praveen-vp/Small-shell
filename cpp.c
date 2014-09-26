
#include "linux.h"

#define BUFLEN 1024

int main(int argc , char *argv[])
{
	int fdr, fdw, n;
	char buf[BUFLEN];
	
	assert(argc == 3);

	fdr = open (argv[1],O_RDONLY);
	assert (fdr >= 0);

	fdw = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	assert (fdw >= 0);

	while((n = read (fdr, buf, sizeof(buf))) > 0)
	   if(write (fdw, buf, n) != n) {
		   fprintf(stderr, "write error\n");
		   exit(1);
	   }
	if(n < 0) {
		fprintf(stderr,"read error\n");
		exit (1);
	}
	return 0;
}

