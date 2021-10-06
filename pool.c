#include "apr.h"
#include "apr_errno.h"
#include "apr_pools.h"

#include <stdio.h>

apr_status_t foo(void *ctx) {
    printf ("Called cleanup %d\n", (*(int *)ctx));
    return APR_SUCCESS;
}

int main() {
    apr_status_t rv;
    apr_pool_t *mp;

    rv = apr_pool_initialize();
    if (rv != APR_SUCCESS) {
        return -1;
    }
    rv = apr_pool_create(&mp, NULL);
    printf("%d\n", rv);

    apr_allocator_t *pa = apr_pool_allocator_get(mp);
    if (pa) {
        apr_allocator_max_free_set(pa, 64);
    }

    int x = 24;
    apr_pool_cleanup_register(mp, &x, foo, apr_pool_cleanup_null);

    char *buf1 = apr_palloc(mp, 1024);
    // apr_pool_clear(mp);
    char *buf2 = apr_palloc(mp, 1024 * 1024);

    apr_pool_destroy(mp);
    apr_terminate();
}
