#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sig_int( int );
void pr_mask( const char *);    //call to funtion pr_mask
void oops(void *);

int main(int argc , char *argv[]){

    setbuf( stdout , NULL );    //close buffer
    pr_mask( "before catching signal ,mask sig  :" );

    if( signal( SIGINT , sig_int ) == SIG_ERR )
        oops( "signal" );
    //keep loop to catch signal interuption
    while(1)
    //  pause();
        sleep(3);

    pr_mask( "end catching signal ,mask sig  :" );

    return 0;
}

//signal handler
void  sig_int( int signo ){
    pr_mask( "in signal handler:" );
}


void pr_mask( const char *str ){
    sigset_t set, n_set;
    int errno_save;         //get the pre errno

    errno_save = errno;

    sigemptyset(&set);
    sigemptyset(&n_set);
    sigaddset(&n_set, SIGUSR1);
    sigprocmask( SIG_BLOCK, &n_set , NULL);
    if( sigprocmask( SIG_BLOCK, &n_set , &set ) == -1 )
        oops( " sigmask" );
    else{
        printf( "\n%s" , str );
        if( sigismember( &set , SIGQUIT ) )
            printf( " SIGQUIT" );
        if( sigismember( &set , SIGINT ) )
            printf( " SIGINT" );
        if( sigismember( &set , SIGUSR1 ) )
            printf( " SIGUSR1" );
        if( sigismember( &set , SIGALRM ) )
            printf( " SIGALRM" );
    }
    errno = errno_save ;
}

void oops(void *msg){
    perror(msg);
    exit(1);
}

