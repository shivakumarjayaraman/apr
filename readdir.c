#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "apr_general.h"
#include "apr_file_io.h"

int main(int argc, char **argv) {
    apr_status_t rv;
    apr_pool_t *mp;
    apr_dir_t *dir;

    apr_initialize();
    
    apr_pool_create(&mp, NULL);
    // open a dir and list its contents

    if (apr_dir_open(&dir, "/etc", mp) == APR_SUCCESS) {
        apr_finfo_t finfo;
        apr_int32_t wanted = APR_FINFO_NORM;
        while ((rv = apr_dir_read(&finfo, wanted, dir)) == APR_SUCCESS) {
             printf ("... %s\n", finfo.name);
        } 
    } else {
        printf ("Error opening dir /etc\n");
    }
    
    apr_pool_destroy(mp);
    apr_terminate();
}
