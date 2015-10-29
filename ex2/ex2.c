#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define BLOCKSIZE 4096
#define NBLOCKS 262144

int main(int argc, char **argv) {
	struct timeval t1, t2;
	double elapsedTime;
	double throughput;
	double gig; 
	gig = strtod(argv[1], NULL);
	int fd = open ("mydata", O_CREAT | O_RDWR, S_IWRITE);

	char datablock[BLOCKSIZE];
	
	gettimeofday(&t1, NULL);
	int i;
	for (i=0; i<NBLOCKS*gig; i++) {
		write(fd,datablock,BLOCKSIZE);
	}

	int fc = close(fd);

	gettimeofday(&t2, NULL);
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
	throughput = (gig*1024.0)/elapsedTime;

	printf("Throughput:\t %.0f MB/s", throughput*1000.0); 
	printf("Time:\t%.0f ms\n", elapsedTime);
	
	return fc;
}
