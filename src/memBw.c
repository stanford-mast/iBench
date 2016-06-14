#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <float.h>

#ifndef N
#   define N    2000000
#endif
#ifndef NTIMES
#   define NTIMES       100
#endif
#ifndef OFFSET
#   define OFFSET       0
#endif

static double   bwData[N+OFFSET],
		b[N+OFFSET],
		c[N+OFFSET];


unsigned int bwStreamSize = 2*N; 
//#ifdef _OPENMP
extern int omp_get_num_threads();
//#endif

int main (int argc, char **argv) { //char* argv[]) {
//#ifdef _OPENMP
//#pragma omp parallel 
//	{
//#pragma omp master
//	{
//		register int k = omp_get_num_threads();
//	    	printf ("Number of Threads requested = %i\n",k);
//	}
//	}
//#endif

	double scalar = 3.0;
	/*Usage: ./memBw <duration in sec>*/
	if (argc < 2) { 
		printf("Usage: ./memBw <duration in sec>\n"); 
		exit(0);
	}
	unsigned int usr_timer = atoi(argv[1]);
	double time_spent = 0.0; 
	while (time_spent<usr_timer) {
		double *mid=bwData+(bwStreamSize/2);
		clock_t begin = clock(); 
		#pragma omp parallel for 
		for (int i=0; i<bwStreamSize/2; i++) {
			bwData[i]= scalar*mid[i];
		}
		#pragma omp parallel for 
		for (int i=0; i<bwStreamSize/2; i++) {
			mid[i]= scalar*bwData[i];
		}
		clock_t end = clock(); 
  		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		//sleep(0.5); 
	}
	return 0;
}
