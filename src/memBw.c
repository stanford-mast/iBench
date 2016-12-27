/** $lic$
 * Copyright (C) 2016-2017 by The Board of Trustees of Cornell University
 * Copyright (C) 2013-2016 by The Board of Trustees of Stanford University
 *    
 * This file is part of iBench. 
 *    
 * iBench is free software; you can redistribute it and/or modify it under the
 * terms of the Modified BSD-3 License as published by the Open Source Initiative.
 *    
 * If you use this software in your research, we request that you reference
 * the iBench paper ("iBench: Quantifying Interference for Datacenter Applications", 
 * Delimitrou and Kozyrakis, IISWC'13, September 2013) as the source of the benchmark 
 * suite in any publications that use this software, and that
 * you send us a citation of your work.
 *    
 * iBench is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the BSD-3 License for more details.
 *    
 * You should have received a copy of the Modified BSD-3 License along with
 * this program. If not, see <https://opensource.org/licenses/BSD-3-Clause>.
 **/

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

int main (int argc, char **argv) { 
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
	}
	return 0;
}
