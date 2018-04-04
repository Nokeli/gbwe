#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>

//#define SHARE_ID 123
//#define ACCESS_TIMEOUT 8e06

FILE *dicofopen(const char *nom,const char *mode)
{
    FILE *flot;
    int fd=fopen(nom,mode);
    flot=fopen(nom,mode);
    //flock(flot->_file,LOCK_EX);
    flock(flot->_file,LOCK_EX | LOCK_NB);
    return flot;

/*
    int desc,flag,fcn_status;
    //flag = O_RDWR | O_DSYNC | O_RSYNC | O_SYNC;
//	      2     010000     010000    010000
    flag = O_RDWR | O_FSYNC;
    desc = open(nom,flag);
    if (desc==-1)
        return NULL;
    //fcn_status=flock(desc,LOCK_EX | LOCK_NB);
    fcn_status=flock(desc,LOCK_EX);

    flot=fopen(nom,mode);
    fcn_status=flock(flot->_file,LOCK_EX | LOCK_NB);
    if (fcn_status == -1)
    {
//	    return NULL;
        //double tdiff;
        //long tdiffm;
        //struct timeval *temps2,*temps1;
        //struct timezone *tps2,*tps1;
	struct timespec thistime;
	struct timespec firsttime;
	long timediff0;

        //temps1 = malloc(sizeof(struct timeval));
        //temps2 = malloc(sizeof(struct timeval));
        //tps1 = malloc(sizeof(struct timezone));
        //tps2 = malloc(sizeof(struct timezone));
        //gettimeofday(temps1,tps1);
		clock_gettime(CLOCK_REALTIME,&firsttime);

        do {
		clock_gettime(CLOCK_REALTIME,&thistime);
		gettimeofday(temps2,tps2);
            tdiff = (double)difftime(temps2->tv_sec,temps1->tv_sec);
            tdiffm = temps2->tv_usec-temps1->tv_usec;
            tdiff = tdiff*1000000 + tdiffm;
            if (tdiff>ACCESS_TIMEOUT)
                return NULL;
		timediff0=thistime.tv_sec - firsttime.tv_sec;
		if(timediff0 > ACCESS_TIMEOUT)
			return NULL;
            fcn_status=flock(desc,LOCK_EX | LOCK_NB);
        } while (fcn_status == -1);
    }
    //flot = fdopen(desc,mode);
    return flot;
*/
}

void dicofclose(FILE *f)
{
    flock(f->_file,LOCK_UN);
    //flock(f,LOCK_UN);
    close(f);
}