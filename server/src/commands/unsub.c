/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** unsub
*/

#include "my.h"

static int error_unsub(server_t *server,
    const int client_fd)
{
    team_belong_t *my_teams;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s\n%s",
            "unsub.c/error_unsub : not enough argument", CODE_101);
        return ERR_CMD;
    }
    TAILQ_FOREACH(my_teams,
        &server->clients[server->user_index]->new_user->team_belong_head,
        belong_entries) {
        if (strcmp(server->cmd_arg.tab[1], my_teams->uuid) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s%s\n%s", CODE_402, server->cmd_arg.tab[1], CODE_101);
    return ERR_CMD;
}

int unsub_team(server_t *server, const int client_fd, my_teams_t *)
{
    team_belong_t *my_teams;

    if (error_unsub(server, client_fd) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(my_teams,
        &server->clients[server->user_index]->new_user->team_belong_head,
        belong_entries) {
        if (strcmp(my_teams->uuid, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s%s\n%s\n%s", CODE_209,
            server->clients[server->user_index]->username, my_teams->uuid,
            CODE_101);
            server_event_user_unsubscribed(my_teams->uuid,
            server->clients[server->user_index]->username);
            TAILQ_REMOVE(&server->clients[server->user_index]->
                new_user->team_belong_head,
                my_teams, belong_entries);
        }
    }
    return WIN_CMD;
}
