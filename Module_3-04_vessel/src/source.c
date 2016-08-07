#include <stdlib.h>

#include "source.h"

struct vessel create_vessel(const char *p_name,
        double p_length,
        double p_depth,
        struct cargo p_crg) {
    struct vessel result;
    int name_length = 30;

    strcpy(result.name, p_name);
    result.name[name_length] = '\0';

    result.length = p_length;
    result.depth = p_depth;
    result.crg = p_crg;

    return result;
}

void print_vessel(const struct vessel *ship) {
}
