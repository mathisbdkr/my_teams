/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** disp_priv_msg
*/

#include "my.h"

static int error_disp_msg(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    user_t *new_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s\n",
            "private_msg.c/error_disp_msg : not enough argument");
        return ERR_CMD;
    }
    TAILQ_FOREACH(new_user, &teams->user_head, user_entries) {
        if (strcmp(server->cmd_arg.tab[1], new_user->uuid) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s%s\n%s", CODE_401, server->cmd_arg.tab[1], CODE_101);
    return ERR_CMD;
}

int display_priv_msg(server_t *server, const int client_fd, my_teams_t *teams)
{
    private_msg_t *prv_msg;

    if (error_disp_msg(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    dprintf(client_fd, "%s", CODE_206);
    TAILQ_FOREACH(prv_msg, &teams->priv_msg_head, private_msg_entries) {
        if (strcmp(prv_msg->uuid_other, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s\n%ld\n%s\n", prv_msg->uuid_sender,
            prv_msg->timestamp, prv_msg->body);
        }
    }
    dprintf(client_fd, "%s", CODE_101);
    return WIN_CMD;
}
