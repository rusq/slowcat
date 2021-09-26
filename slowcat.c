/*
 * slowcat.c - slow down the display of a file
 * copyright (c) 2001,2002,2007  dave w capella   All Rights Reserved
 *
 * distributed under the terms of the GNU Public license
 *
 * There is NO WARRANTY, and NO SUPPORT WHATSOEVER.
 *
 * building: make slowcat && mv slowcat $HOME/bin
 * (assuming that you have a personal bin directory)
 *
 * usage: slowcat [-d usecs] filename
 * where usecs is the number of micro-seconds to delay.
 *
 * feedback welcome. enjoy!
 * ...dave
 *
 *
 * 09/24/07 - modifications to include nanosleep, brian at landsberger.com
 * 09/26/21 - include string.h and usage function, support for Darwin.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int debug = 0;

void usage(char *name) {
	fprintf(stderr,"usage: %s [-d usecs] filename\n", name);
}

int main(int argc, char **argv) {
	int c;
	unsigned long usecs,s;
	FILE *fp;
	char *fnam;
    struct timespec ts;

	if(argc != 2 && argc != 4) {
		usage(argv[0]);
		exit(1);
	}

	if(argc == 4 ) {
		 if( !strncmp(argv[1],"-d",2) ) {
			usecs = strtoul(argv[2],NULL,10);
			if(usecs<=0 || usecs>500000L) {
				usecs = 1;
			}
		}
		if(debug) {
			fprintf(stderr,"usecs: %lu\nAny key to continue.\n",usecs);
			c = getchar();
		}
		fnam = argv[3];
	}
	/* set timespec */
	ts.tv_sec=0;
	ts.tv_nsec=usecs;

	if(argc == 2 ) {
		fnam = argv[1];
	}
	fp = fopen(fnam,"r");
	if(fp == NULL) {
		usage(argv[0]);
		exit(2);
	}

	while( (c = fgetc(fp)) != EOF) {
		putchar(c);
#if defined(_POSIX_C_SOURCE) || defined(__DARWIN_C_ANSI) // assuming >= 199309L
		if (debug) {
			fprintf(stderr,"sleeping using nanosleep\n");
		}
		nanosleep(&ts,NULL);
#else  
		if (debug) {
			fprintf(stderr,"sleeping using for\n");
		}
		for(s=0;s<usecs;s++)
			;
#endif
	}

	fclose(fp);
	return (0);
}
