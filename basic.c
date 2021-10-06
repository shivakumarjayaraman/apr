#include <stdio.h>
#include "apr.h"
#include "apr_version.h"

int main() {
    printf("%s\n", apr_version_string());
}
