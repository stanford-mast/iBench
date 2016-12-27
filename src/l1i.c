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
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ICPOISON do { x ^= y; } while (0)

#define ICPOISON2      ICPOISON;       ICPOISON
#define ICPOISON4      ICPOISON2;      ICPOISON2
#define ICPOISON8      ICPOISON4;      ICPOISON4
#define ICPOISON16     ICPOISON8;      ICPOISON8
#define ICPOISON32     ICPOISON16;     ICPOISON16
#define ICPOISON64     ICPOISON32;     ICPOISON32
#define ICPOISON128    ICPOISON64;     ICPOISON64
#define ICPOISON256    ICPOISON128;    ICPOISON128
#define ICPOISON512    ICPOISON256;    ICPOISON256
#define ICPOISON1024   ICPOISON512;    ICPOISON512
#define ICPOISON2048   ICPOISON1024;   ICPOISON1024
#define ICPOISON4096   ICPOISON2048;   ICPOISON2048
#define ICPOISON8192   ICPOISON4096;   ICPOISON4096
#define ICPOISON16384  ICPOISON8192;   ICPOISON8192
#define ICPOISON32768  ICPOISON16384;  ICPOISON16384
#define ICPOISON65536  ICPOISON32768;  ICPOISON32768
#define ICPOISON131072 ICPOISON65536;  ICPOISON65536
#define ICPOISON262144 ICPOISON131072; ICPOISON131072

int main(int argc, char **argv) {
  int x = 0xf0;
  int y = 0x0f;

  //if (argc != 2) {
  //  printf("Usage: ic_possoin [0-..]\n");
  //}

  //printf("%d\n", atoi(argv[1]));

  int usr_timer = atoi(argv[1]);
  printf ("%d\n", usr_timer); 
  //if (((usr_timer)%20) != 0) { 
  //	  printf("usr_timer must be multiple of 20\n"); 
  //	  exit(0); 
  //}

  clock_t begin, end;
  double time_spent;

  begin = clock();

  int intensity = 0; 

  intensity = atoi(argv[2]);

  printf("%d\n", intensity); 

  //for (int j = 0; j < 10*usr_timer; j++) { 
  for (int j = 0; j < 1500; j++) { 
	switch (intensity) {
	    case 0:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON; } //intensity = 1; 
	    case 1:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON2; } //intensity = 2;
	    case 2:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON4; } //intensity = 3; 
	    case 3:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON8; } //intensity = 4;
	    case 4:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON16; } //intensity = 5;
	    case 5:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON32; } //intensity = 6;
	    case 6:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON64; } //intensity = 7;
	    case 7:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON128; } //intensity = 8;
	    case 8:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON256; } //intensity = 9;
	    case 9:  for (int i = 0; i < int(usr_timer); i++) { ICPOISON512; } //intensity = 10;
	    case 10: for (int i = 0; i < int(usr_timer); i++) { ICPOISON1024; } //intensity = 11;
	    case 11: for (int i = 0; i < int(usr_timer); i++) { ICPOISON2048; } //intensity = 12;
	    case 12: for (int i = 0; i < int(usr_timer); i++) { ICPOISON4096; } //intensity = 13;
	    case 13: for (int i = 0; i < int(usr_timer); i++) { ICPOISON8192; } //intensity = 14;
	    case 14: for (int i = 0; i < int(usr_timer); i++) { ICPOISON16384; } //intensity = 15;
	    case 15: for (int i = 0; i < int(usr_timer); i++) { ICPOISON32768; } //intensity = 16;
	    case 16: for (int i = 0; i < int(usr_timer); i++) { ICPOISON65536; } //intensity = 17;
	    case 17: for (int i = 0; i < int(usr_timer); i++) { ICPOISON131072; } //intensity = 18;
	    case 18: for (int i = 0; i < int(usr_timer); i++) { ICPOISON262144; } //intensity = 19;
	    case 19: for (int i = 0; i < int(usr_timer); i++) { ICPOISON262144; } //intensity = 20;
	    case 20: for (int i = 0; i < int(usr_timer); i++) { ICPOISON262144; } 
  	}
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time spent: %f\n", time_spent);
  
  return 0;
}
