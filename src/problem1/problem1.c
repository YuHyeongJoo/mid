#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include<unistd.h>

char * 
read_exec (char * exe)
{
	int fd = open("a.out",O_WRONLY | O_CREAT, 0644);
	int dup2(fd,1);
	char buffer[2048];
	read(fd, buffer,2048);
	return buffer;
}


int 
main (int argc, char ** argv)
{
	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments\n") ;
		exit(1) ;
	}

	char * s ;
	s = read_exec(argv[1]) ;
	printf("\"%s\"\n", s) ;
	free(s) ;
	exit(0) ;
}
