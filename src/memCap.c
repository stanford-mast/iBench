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

long long int memory_size_kb(void) {
	char line[512], buffer[32];
	long long int column;
	FILE *meminfo;


	if (!(meminfo = fopen("/proc/meminfo", "r"))) {
		perror("/proc/meminfo: fopen");
		return -1;
	}


	while (fgets(line, sizeof(line), meminfo)) {
		if (strstr(line, "MemTotal")) {
			char* colStr;
			colStr = strstr(line, ":");
			remove_all_chars(colStr, ':'); 
			remove_all_chars(colStr, 'k'); 
			remove_all_chars(colStr, 'B');
			remove_all_chars(colStr, ' ');
			column = atoi(colStr);
		        column = 1000*column;	
			fclose(meminfo);
			return column; 
		}
	}
	fclose(meminfo);
	return -1;
}

int main(int argc, char **argv) {
	char* volatile block;
	long long int MEMORY_SIZE = memory_size_kb(); 
	printf("Total Memory Size: %llu\n", MEMORY_SIZE);

	/*Usage: ./l3 <duration in sec>*/
	if (argc < 2) { 
		printf("Usage: ./cap_mem <duration in sec>\n"); 
		exit(0); 
	}	
	block = (char*)mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	//This needs to be more gradual
	//block = (char*)mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	int usr_timer = atoi(argv[1]);
	double time_spent = 0.0; 
  	clock_t begin, end;


	while (time_spent < usr_timer) {
  		begin = clock();
		memcpy(block, block+MEMORY_SIZE/2, MEMORY_SIZE/2);
		//sleep((float)(usr_timer-time_spent)/usr_timer);
		end = clock();
  		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	}
	return 0;
}

