#include "unit_test.h"
#include <stdio.h>

void show_fail_status () {
    out("%10s", "Case ");

    for (int i = 0; i < cases; i++)
        if (failed_cases[i])
            fprintf(stdout, "%s%d%s ", COLOR_ERR, i + 1, COLOR_NRM);
    
    strout("failed.");
    nl(); nl();
}

void show_result () {
    if (pass == cases) {
        p_success();
        count();
        nl(); nl();
    }

    else {
        p_failure();
        count();
        show_fail_status();
    }
}
