#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "apr_general.h"
#include "apr_time.h"

int main() {
    // get current time
    apr_time_t now = apr_time_now();

    // convert to local time
    apr_time_exp_t localtime;
    apr_time_exp_lt(&localtime, now);

    // make a string out of the time
    char date_str[256];
    apr_ctime(date_str, now);
    printf("%s\n", date_str);
}
