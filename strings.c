#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "apr_general.h"
#include "apr_strings.h"

int main() {
    apr_pool_t *mp;
    apr_initialize();
    apr_pool_create(&mp, NULL);

    char *s1 = "hello";
    char *s2 = "world";
    char *s3 = "shiva";

    const char *concat = apr_pstrcat(mp, s1, s2, s3, NULL);
    printf ("%s\n", concat);

    const char *res = apr_psprintf(mp, "Hi : %s %s %s\n", s1, s2, s3);
    printf ("%s\n", res);

    apr_pool_destroy(mp);
    apr_terminate();
}
