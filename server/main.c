/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "teams.h"
#include "my.h"

static void exit_program(int signal)
{
    if (signal == SIGINT)
        exit(0);
}

static void print_usage(void)
{
    puts("USAGE: ./myteams_server port");
    puts("port is the port number on which the server socket listens");
}

int main(int ac, char *const *av)
{
    if (ac != 2) {
        fprintf(stdout, "run ./myteams_server -help\n");
        return 84;
    }
    if (strcmp(av[1], "-help") == 0)
        print_usage();
    signal(SIGINT, exit_program);
    return server(av[1]);
}
