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
    rv = apr_pool_initialize();
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

    // Get file info .. We can use apr_stat if we want to get from filename
    // but here we are getting it from apr_file_info_get
    apr_finfo_t finfo;
    apr_int32_t wanted = 0;
    rv = apr_file_info_get(&finfo, ~wanted, fp);
    printf("File %s: \n", finfo.fname);
    printf("Inode: %ld\n", finfo.inode);
    printf("Size : %ld\n", finfo.size);
    printf("User: %d\n", finfo.user);

    // destroying the pool closes the file 
    apr_pool_destroy(mp);
}
