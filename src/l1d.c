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


	if (!(cpuinfo = fopen("/sys/devices/system/cpu/cpu0/cache/index1/size", "r"))) {
		perror("/sys/devices/system/cpu/cpu0/cache/index1/size: fopen");
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
	char* volatile block;
	int CACHE_SIZE = cache_size_kb(); 
	printf("L1d cache size: %dKB\n", CACHE_SIZE); 
	block = (char*)mmap(NULL, CACHE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);


	/*Usage: ./l1d <duration in sec>*/
	if (argc < 2) { 
		printf("Usage: ./l1d <duration in sec>\n"); 
		exit(0); 
	}	
	unsigned long int usr_timer = getNs() + NS_PER_S*atoi(argv[1]);


	while (getNs() < usr_timer) {
		memcpy(block, block+CACHE_SIZE/2, CACHE_SIZE/2);
		sleep((float)(usr_timer-getNs())/usr_timer);
	}
	return 0;
}

