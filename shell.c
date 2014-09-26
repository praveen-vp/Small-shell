#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int k,fdw,fdr,pip[2];
	char s[5],p[5],q[5],r[5];
	
	for (k=0;k<=5;k++)
		s[k]=p[k]=q[k]=r[k] = 0;

	while(1) {	

		if(fork() == 0) {
			printf("shell $:");
			gets(s);
			sscanf(s,"%s %s %s",p,q,r);

			if(q[0] == '>') {
				fdr = open(r,O_WRONLY | O_CREAT | O_TRUNC,0644);
				assert(fdr >= 0);
				close(1);
				dup(fdr);
				execlp(p,p,(char*)NULL);
			}
			else if(q[0] == '<') {
				fdr = open(r,O_RDONLY);
				assert(fdr >= 0);
				close(0);
				dup(fdr);
				execlp(p,p,(char*)NULL);
			}
		  	else if(q[0] == '|') {
				pipe(pip);

				if(fork() == 0) {
					close(0);
					dup(pip[0]);
					close(pip[1]);
					execlp(r,r,(char*)NULL);
				}
				else {
					close(1);
					dup(pip[1]);
					close(pip[0]);
					execlp(p,p,(char*)NULL);
				}
			}
			else if(q[0] == 0 && r[0] == 0)
				execlp(p,p,(char*) NULL);
			else if(r[0] == 0 && q[0] != 0)
				execlp(p,p,q,(char*) NULL);
			else 
				execlp(p,p,q,r,(char*)NULL);
		}
		wait();
	}
}

