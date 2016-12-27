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



#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

//#define CACHE_SIZE 2*1024*1024
#define NS_PER_S (1000000000L)


unsigned long int getNs() {
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec*NS_PER_S + ts.tv_nsec;
}


void remove_all_chars(char* str, char c) {
	char *pr = str, *pw = str;
	while (*pr) {
		*pw = *pr++;
		pw += (*pw != c);
	}
	*pw = '\0';
}

int cache_size_kb(void) {
	char line[512], buffer[32];
	int column;
	FILE *cpuinfo;


	if (!(cpuinfo = fopen("/sys/devices/system/cpu/cpu0/cache/index2/size", "r"))) {
		perror("/sys/devices/system/cpu/cpu0/cache/index2/size: fopen");
		return -1;
	}


	while (fgets(line, sizeof(line), cpuinfo)) {
		char* colStr;
		remove_all_chars(line, 'K'); 
		remove_all_chars(line, 'B');
		column = atoi(line); 
		fclose(cpuinfo);
		return (int) column; //(int)strtol(buffer, NULL, 10);
	}
	fclose(cpuinfo);
	return -1;
}

int main(int argc, char **argv) {
	timespec sleepValue = {0};

	char* volatile block;
	int CACHE_SIZE = cache_size_kb(); 
	printf("L2 cache size: %dKB\n", CACHE_SIZE); 
	block = (char*)mmap(NULL, CACHE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);


	/*Usage: ./l2 <duration in sec>*/
	if (argc < 2) { 
		printf("Usage: ./l2 <duration in sec>\n"); 
		exit(0); 
	}	
	unsigned long int usr_timer = getNs() + NS_PER_S*atoi(argv[1]);


	while (getNs() < usr_timer) {
		memcpy(block, block+CACHE_SIZE/2, CACHE_SIZE/2);
		sleepValue.tv_nsec = (usr_timer-getNs())/usr_timer;
		nanosleep(&sleepValue, NULL);
	}
	return 0;
}

