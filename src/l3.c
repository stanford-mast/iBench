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
		sleep((float)(usr_timer-time_spent)/usr_timer);
		end = clock();
  		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	}
	return 0;
}

