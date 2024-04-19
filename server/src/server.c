/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** server
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

void free_server_struct(server_t *server)
{
    close(server->server_fd);
    free(server->fd_array);
    free(server);
}

int server(const char *port_number)
{
    server_t *server = init_server_struct(port_number);

    if (initialize_server(server) == 84)
        return 84;
    if (run_server(server) == 84)
        return 84;
    free_server_struct(server);
    return 0;
}
