/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** server
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "my.h"

static void remove_client_socket(server_t *server, const int client_fd)
{
    for (size_t i = 0; i != server->size; i += 1) {
        if (server->fd_array[i] == client_fd) {
            server->fd_array[i] = 0;
            break;
        }
    }
}

void close_client_socket(server_t *server)
{
    clients_t *client = server->clients[server->user_index];

    if (client->has_been_closed) {
        close(client->client_fd);
        FD_CLR(client->client_fd, &server->readfds);
        remove_client_socket(server, client->client_fd);
    }
}
