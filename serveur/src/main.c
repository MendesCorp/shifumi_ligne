#include "shifumi_ligne/client/modules/global.h"

int main () {

    int serv_fd = socket (AF_INET, SOCKSTREAM, 0); perror("socket");
    if(serv_fd == -1) return EXIT_FAILURE;

    int error = 












    return 0;
}