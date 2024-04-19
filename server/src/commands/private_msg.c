/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** private_msg
*/

#include "my.h"

static int error_send_msg(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    user_t *new_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL || server->cmd_arg.tab[2] == NULL) {
        dprintf(client_fd, "%s\n%s",
            "private_msg.c/error_send_msg : not enough argument", CODE_101);
        return ERR_CMD;
    }
    if (strlen(server->cmd_arg.tab[2]) >= MAX_BODY_LENGTH)
        return ERR_CMD;
    TAILQ_FOREACH(new_user, &teams->user_head, user_entries) {
        if (strcmp(server->cmd_arg.tab[1], new_user->uuid) == 0)
            return WIN_CMD;
    }
    dprintf(client_fd, "%s%s\n%s", CODE_401,
        server->clients[server->user_index]->my_uuid, CODE_101);
    return ERR_CMD;
}

static void display_msg_other(server_t *server, private_msg_t *priv_msg)
{
    for (int index = 0; index != MAX_USER; index += 1) {
        if (server->clients[index]->my_uuid == NULL)
            continue;
        if (strcmp(server->clients[index]->my_uuid, priv_msg->uuid_other) == 0
            && server->clients[index]->is_connected == true) {
            dprintf(server->clients[index]->client_fd, "%s%s\n%s\n%s",
                CODE_205, priv_msg->uuid_sender, priv_msg->body, CODE_101);
        }
    }
    return;
}

int send_msg(server_t *server, const int client_fd, my_teams_t *teams)
{
    private_msg_t *priv_msg;

    if (error_send_msg(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    priv_msg = malloc(sizeof(private_msg_t));
    TAILQ_INSERT_TAIL(&teams->priv_msg_head, priv_msg, private_msg_entries);
    strcpy(priv_msg->uuid_sender,
        server->clients[server->user_index]->my_uuid);
    strcpy(priv_msg->uuid_other, server->cmd_arg.tab[1]);
    strcpy(priv_msg->body, server->cmd_arg.tab[2]);
    priv_msg->timestamp = time(NULL);
    display_msg_other(server, priv_msg);
    dprintf(client_fd, "%s%s", CODE_200, CODE_101);
    return WIN_CMD;
}
