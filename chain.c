//main.c - chain
//Eric Elsner
//02/09/22

#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, j, opt;

    //perror() message init
    char error_stmt[64];
    strcpy(error_stmt, argv[0]);
    strcat(error_stmt, ": Error");
    
    //default command line arguments init
    int nprocs = 4;
    //int nchars = 80;
    int sleeptime = 3;
    int niters = 1;
    //char *fname = "input.dat";
    //FILE *fname = NULL;

    printf("\n");

    //input command line args, getop() loop
    while ((opt = getopt(argc, argv, "hp:s:i:")) != -1) {
    
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
		    //number of processes = 'n'
		    case 'p':
			    if (optarg == NULL) {
				    break;
			    } else if (isdigit(*optarg)) {
				    nprocs = atoi(optarg);
				    break;
			    } else {
				    perror("optarg");
				    return 1;
			    }
			    break;
		    /*case 'c':
			    if(isdigit(*optarg)) {
				    nchars = atoi(optarg);
			    } else {
				    perror("invalid -c value");
			    }
			    break;
			    */
		    //function sleep(m); => sleep(sleeptime);
		    case 's':
			    if(isdigit(*optarg)) {
				    sleeptime = atoi(optarg);
			    } else {
				    perror("invalid -s value");
				    return 1;
			    }
			    break;
		    //loop iterations 'i' instead of 'k'
		    case 'i':
			    if(isdigit(*optarg)) {
				    niters = atoi(optarg);
			    } else {
				    perror("invalid -i value");
				    return 1;
			    }
			    break;
		    /*case '<':
			    fname = optarg;
			    break;
			    */
		    default:
			    return 1;
	    }
    }
    /*
    if (argc != 2) {
	    fprintf(stderr, "Usage: %s processes\n",argv[0]);
	    return 1;
    }
    */

    // 'nprocs' number of processes fork: for-loop
    for (i = 1; i < nprocs; i++)
	    if (childpid = fork())
		    break;
    // 'niters' number of fprintf iterations
    for (j = 0; j < niters; j++) {
	    sleep(sleeptime);
	    fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
		    i, (long)getpid(), (long)getppid(), (long)childpid);
    }
    return 0;
}
