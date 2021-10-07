#include <stdio.h>

#include "apr.h"
#include "apr_pools.h"
#include "apr_file_info.h"
#include "apr_file_io.h"
#include "apr_errno.h"

int main() {
    apr_status_t rv;
    apr_pool_t *mp;

    // Initialize the APR resource pools
    rv = apr_initialize();
    if (rv != APR_SUCCESS) {
        return -1;
    }
    apr_pool_create(&mp, NULL);

    // Open a file managed by the pool 
    apr_file_t *fp;
    char buf[513];
    rv = apr_file_open(&fp, "/etc/passwd", APR_FOPEN_READ, 0, mp);
    if (rv != APR_SUCCESS) {
        apr_strerror(rv, buf, sizeof(buf));
        puts(buf); 
        return -1;
    }
    
    // mess with the file
    apr_size_t nread = 512;
    rv = apr_file_read(fp, buf, &nread);
    printf("%ld\n", nread);
    while (nread > 0) {
        buf[nread] = 0;
        printf("%s", buf);
        nread=512;
        rv = apr_file_read(fp, buf, &nread);
    }

    // destroying the pool closes the file 
    apr_pool_destroy(mp);
    apr_terminate();
}
