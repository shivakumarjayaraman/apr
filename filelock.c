#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "apr_general.h"
#include "apr_file_io.h"

int main(int argc, char **argv) {
    // default read lock
    int lock = 0;
    int lock_type = APR_FLOCK_SHARED | APR_FLOCK_NONBLOCK; 

    if ((argc > 1) && (argv[1][0] == 'w')) {
        lock = 1;
        lock_type = APR_FLOCK_EXCLUSIVE | APR_FLOCK_NONBLOCK;
    }

    if (lock == 0) {
        printf ("Shared lock\n");
    } else {
        printf ("Exclusive lock\n");
    }

    apr_status_t rv;
    apr_file_t *fp;
    apr_pool_t *mp;

    apr_initialize();
    
    apr_pool_create(&mp, NULL);
    // open a file 
    if (apr_file_open(&fp, "/tmp/foo", APR_READ|APR_WRITE|APR_CREATE , APR_OS_DEFAULT, mp) 
             == APR_SUCCESS) {
        if (apr_file_lock(fp, lock_type) == APR_SUCCESS) {
              printf("Got lock\n");
              sleep(10);
              printf("Releasing lock\n");
        } else {
            printf ("Error acquiring lock\n");
        }
    } else {
        printf ("Error opening file\n");
    }
    
    apr_pool_destroy(mp);
    apr_terminate();
}
