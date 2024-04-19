/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** client_command
*/

#include "my.h"

int quit_cmd(server_t *server, const int client_fd, my_teams_t *)
{
    char *uuid;
    char *username;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    uuid = strdup(server->clients[server->user_index]->my_uuid);
    username = strdup(server->clients[server->user_index]->username);
    server_event_user_logged_out(uuid);
    dprintf(client_fd, "%s%s\n%s\n%s", CODE_202, uuid, username, CODE_101);
    server->clients[server->user_index]->has_been_closed = true;
    server->clients[server->user_index]->new_user->is_logged = false;
    server->clients[server->user_index]->username = malloc(sizeof(char) * 1);
    server->clients[server->user_index]->is_connected = false;
    server->fd_array[server->user_index] = 0;
    return WIN_CMD;
}

int handle_ctrl_c(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (server->clients[server->user_index]->new_user != NULL)
        if (server->clients[server->user_index]->new_user->is_logged)
            return quit_cmd(server, client_fd, teams);
    server->clients[server->user_index]->has_been_closed = true;
    server->fd_array[server->user_index] = 0;
    return WIN_CMD;
}
