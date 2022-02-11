//main.c - chain
//Eric Elsner
//02/09/22

#include <errno.h>
#include <getopt.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, j, opt;

    //perror() message init
    //char error_stmt[64];
    //strcpy(error_stmt, argv[0]);
    //strcat("chain: Error:", error_stmt);

    //  default command line arguments init
    int nprocs = 4;
    int nchars = 80;
    int sleeptime = 3;
    int niters = 1;
    char *fname = "";
    FILE *myfile  = NULL;

    int arrowflag = 0;
    //input command line args, getopt() loop

    while ((opt = getopt(argc, argv, "hpsi")) != -1) {

    
	    switch (opt) {
		    case 'h':
			    printf("simplechain usage:");
			    printf("chain [-h] [-p nprocs] [-c nchars] [-s sleeptime] [-i niters] < textfile");
			    printf("nprocs    = Number of processes [default 4]");
			    printf("nchars    = Number of characters read into the buffer [default 80]");
			    printf("sleeptime = Time to sleep in each iteration [default 3s]");
			    printf("niters    = Number of iterations in the loop");
			    printf("textfile  = File containing text to be read through stdin");
			    return 0;
		    
		    case 'p':
			    nprocs = atoi(optarg);
			    break;
		    case 'c':
			    nchars = atoi(optarg);
			    break;
		    case 's':
			    sleeptime = atoi(optarg);
			    break;
		    case 'i':
			    niters = atoi(optarg);
			    break;
	/*	    case '<':
			    fname = optarg;
			    arrowflag = 1;
			    break;
	*/		    
		    default:
			    return 0;
	    }
    }
    
   /* if (argc != 2) {
	    fprintf(stderr, "Usage: %s processes\n",argv[0]);
	    return 1;
    }*/
    fname = argv[optind];
    myfile = fopen(fname, "r");
    if (myfile == NULL) {
	printf("Filename: \'%s\'\n", fname);
	perror("fopen");
	return -1;
    }
    printf("Filename: \'%s\'\n", fname);
    

    //char mybuf[nchars], mb;
    	
    for (i = 1; i < nprocs; i++) {
        if (childpid = fork()) {
            break;
        }
    }
    for (j = 0; j < niters; j++) {
        sleep(sleeptime);
        fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
    		i, (long)getpid(), (long)getppid(), (long)childpid);
	/*
	wait(NULL);
    	fprintf(stderr, "i:%d ", i);
	fprintf(stderr, "process ID:%ld ", (long)getpid());
	fprintf(stderr, "parent ID:%ld ", (long)getppid());
	fprintf(stderr, "child ID:%ld \n", (long)childpid);
	*/
    }

    fclose(myfile);
    return 0;
}
