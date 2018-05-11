#include "debugController.h"

void debug(char * msg){
    fprintf(stderr, "[DEBUG] ");
    fprintf(stderr, "%s\n", msg);
}
