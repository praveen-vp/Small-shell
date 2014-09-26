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
	int fd;

	fd = open("dat",O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("%d\n",fd);
	close(1);
	dup(fd);
	printf("hello\n");

}

