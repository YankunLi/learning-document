#include <stdio.h>
#include <stdlib.h>

#define NGX_MAX_INT_T_VALUE 2147483647

int f_atoi(char *line, size_t n)
{
    int  value, cutoff, cutlim;

    if (n == 0) { 
        return -1;
    }    

    cutoff = NGX_MAX_INT_T_VALUE / 10;
    cutlim = NGX_MAX_INT_T_VALUE % 10;

    for (value = 0; n--; line++) {                                                                                                                                                                                  
        if (*line < '0' || *line > '9') {
            return -1;
        }

        if (value >= cutoff && (value > cutoff || *line - '0' > cutlim)) {
            return -1;
        }

        value = value * 10 + (*line - '0');
    }    

    return value;
}
