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

static int check_clients_sockets(server_t *server, my_teams_t *teams)
{
    int client_fd = 0;

    for (size_t i = 0; i != server->size; i += 1) {
        client_fd = server->fd_array[i];
        if (FD_ISSET(client_fd, &server->readfds) != 0) {
            server->user_index = insert_client_in_struct(server, client_fd);
            get_user_input(server, client_fd, teams);
            close_client_socket(server);
        }
    }
    return 0;
}

static int add_client_socket(server_t *server, int new_client_fd)
{
    bool has_been_set = false;

    for (size_t i = 0; i != server->size; i += 1) {
        if (server->fd_array[i] == 0) {
            server->fd_array[i] = new_client_fd;
            has_been_set = true;
            break;
        }
    }
    if (!has_been_set) {
        server->size += 1;
        server->fd_array = realloc(server->fd_array,
            sizeof(int) * server->size);
        if (server->fd_array == NULL)
            return 84;
        server->fd_array[server->size - 1] = new_client_fd;
    }
    return 0;
}

static int accept_connections(server_t *server, int new_client_fd)
{
    socklen_t addrlen = sizeof(server->sock_addr);

    new_client_fd = accept(server->server_fd,
        (struct sockaddr *) &server->sock_addr, &addrlen);
    if (new_client_fd == -1) {
        fprintf(stdout, "accept failed\n");
        return 84;
    }
    return new_client_fd;
}

static int check_server_socket(server_t *server)
{
    int new_client_fd = 0;

    if (FD_ISSET(server->server_fd, &server->readfds) != 0) {
        new_client_fd = accept_connections(server, new_client_fd);
        if (new_client_fd == 84)
            return 84;
        dprintf(new_client_fd, "220 Service ready for new user.\n");
        if (add_client_socket(server, new_client_fd) == 84)
            return 84;
    }
    return 0;
}

static int set_sockets(server_t *server)
{
    int client_fd = 0;

    for (size_t i = 0; i != server->size; i += 1) {
        client_fd = server->fd_array[i];
        if (client_fd > 0)
            FD_SET(client_fd, &server->readfds);
        if (client_fd > server->max_fd_set)
            server->max_fd_set = client_fd;
    }
    if (select(server->max_fd_set + 1, &server->readfds,
        NULL, NULL, NULL) == -1) {
        fprintf(stdout, "select failed\n");
        return 84;
    }
    return 0;
}

static void init_my_teams(my_teams_t *teams)
{
    TAILQ_INIT(&teams->user_head);
    TAILQ_INIT(&teams->team_head);
    TAILQ_INIT(&teams->priv_msg_head);
    teams->command_context = malloc(sizeof(command_context_t));
    teams->command_context->team_context = NOTHING;
    teams->command_context->team_uuid = NULL;
    teams->command_context->channel_uuid = NULL;
    teams->command_context->thread_uuid = NULL;
}

int run_server(server_t *server)
{
    my_teams_t teams = {0};

    init_my_teams(&teams);
    parse_database(&teams);
    while (1) {
        FD_ZERO(&server->readfds);
        FD_SET(server->server_fd, &server->readfds);
        server->max_fd_set = server->server_fd;
        if (set_sockets(server) == 84)
            return 84;
        if (check_server_socket(server) == 84)
            return 84;
        if (check_clients_sockets(server, &teams) == 84)
            return 84;
        save_database(teams);
    }
    return 0;
}
