#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NS_PER_S (1000000000L)

uint64_t getNs() {
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec*NS_PER_S + ts.tv_nsec;
}

int main(int argc, const char** argv) {
	uint32_t maxThreads = omp_get_num_procs();
	//Usage: "./cpu <duration in sec>"
	if (argc < 2) { 
		printf("Usage: ./cpu <duration in sec>\n"); 
		exit(0);
	}
	uint64_t nsPerRun = NS_PER_S*atoi(argv[1])/maxThreads;  // ns

	for (uint32_t threads = 1; threads <= maxThreads; threads++) {
		printf("Running with %d threads\n", threads);
		omp_set_num_threads(threads);
		//uint64_t endNs = pi*getNs() + nsPerRun;
		uint64_t endNs = getNs() + nsPerRun;
#pragma omp parallel
		while (getNs() < endNs);
	}
	return 0;
}

