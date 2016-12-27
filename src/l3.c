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


	if (!(cpuinfo = fopen("/proc/cpuinfo", "r"))) {
		perror("/proc/cpuinfo: fopen");
		return -1;
	}


	while (fgets(line, sizeof(line), cpuinfo)) {
		if (strstr(line, "cache size")) {
			char* colStr;
			colStr = strstr(line, ":");
			remove_all_chars(colStr, ':'); 
			remove_all_chars(colStr, 'K'); 
			remove_all_chars(colStr, 'B');
			column = atoi(colStr); 
			//colStr = strstr(colStr, "KB");
			//strncpy(buffer, line + column + 1, sizeof(buffer));
			fclose(cpuinfo);
			return (int) column; //(int)strtol(buffer, NULL, 10);
		}
	}
	fclose(cpuinfo);
	return -1;
}

int main(int argc, char **argv) {
	timespec sleepValue = {0};

	char* volatile block;
	int CACHE_SIZE = cache_size_kb(); 
	printf("%d\n", CACHE_SIZE);

	/*Usage: ./l3 <duration in sec>*/
	if (argc < 2) { 
		printf("Usage: ./l3 <duration in sec>\n"); 
		exit(0); 
	}	
	block = (char*)mmap(NULL, CACHE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	int usr_timer = atoi(argv[1]);
	double time_spent = 0.0; 
  	clock_t begin, end;


	while (time_spent < usr_timer) {
  		begin = clock();
		memcpy(block, block+CACHE_SIZE/2, CACHE_SIZE/2);
		//sleepValue.tv_nsec = (usr_timer-getNs())/usr_timer; 
 		//nanosleep(&sleepValue, NULL);
		end = clock();
  		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	}
	return 0;
}

