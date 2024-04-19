/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_user
*/

#include "my.h"

int info_user(server_t *server, const int client_fd)
{
    dprintf(client_fd, "%s%s\n%s\n%d\n%s",
        CODE_203, server->clients[server->user_index]->new_user->uuid,
        server->clients[server->user_index]->new_user->name,
        server->clients[server->user_index]->new_user->is_logged, CODE_101);
    return WIN_CMD;
}
