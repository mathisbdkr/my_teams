/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-yanis.harkouk
** File description:
** main
*/

#include <signal.h>
#include "client.h"

static int check_args(int ac, const char **av)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myteams_cli ip port\n");
        printf("\tip\tis the server ip address ");
        printf("on which the server socket listens\n");
        printf("\tport\tis the port number on which ");
        printf("the server socket listens\n");
        return 1;
    }
    return 0;
}

int main(int ac, const char **av)
{
    if (check_args(ac, av) != 0) {
        return 0;
    }
    if (ac != 3) {
        fprintf(stdout, "Bad number of arguments\n");
        return 84;
    }
    return client(av);
}
