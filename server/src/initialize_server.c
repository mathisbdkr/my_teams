/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** server
*/

#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static int check_socket_creation(server_t *server)
{
    if (server->port == 0) {
        fprintf(stdout, "argument isn't a port\n");
        return 84;
    }
    if (server->server_fd == -1) {
        fprintf(stdout, "socket creation failed\n");
        return 84;
    }
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) < 0) {
        fprintf(stdout, "setsockopt failed\n");
        return 84;
    }
    return 0;
}

static int check_socket_config(server_t *server)
{
    server->sock_addr.sin_family = AF_INET;
    server->sock_addr.sin_addr.s_addr = INADDR_ANY;
    server->sock_addr.sin_port = htons(server->port);
    if (bind(server->server_fd, (struct sockaddr *) &server->sock_addr,
        sizeof(server->sock_addr)) < 0) {
        fprintf(stdout, "socket configuration failed\n");
        return 84;
    }
    if (listen(server->server_fd, 128) == -1) {
        fprintf(stdout, "listen failed\n");
        return 84;
    }
    return 0;
}

static int *create_int_array(int size)
{
    int *array = malloc(sizeof(int) * size);

    if (array == NULL)
        return NULL;
    array[0] = 0;
    return array;
}

int initialize_server(server_t *server)
{
    if (check_socket_creation(server) == 84)
        return 84;
    if (check_socket_config(server) == 84)
        return 84;
    return 0;
}

void init_client_struct(server_t *server)
{
    server->clients = malloc(sizeof(clients_t) * (MAX_USER));
    for (int i = 0; i != MAX_USER; i += 1) {
        server->clients[i] = malloc(sizeof(clients_t));
        server->clients[i]->client_fd = 0;
        server->clients[i]->is_connected = false;
        server->clients[i]->has_been_closed = false;
        server->clients[i]->username = NULL;
        server->clients[i]->my_uuid = NULL;
    }
}

server_t *init_server_struct(const char *port_number)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return NULL;
    server->port = atoi(port_number);
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server->size = 1;
    server->fd_array = create_int_array(server->size);
    if (server->fd_array == NULL)
        return NULL;
    server->max_fd_set = 0;
    init_client_struct(server);
    return server;
}
