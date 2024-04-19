/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_channle
*/

#include "my.h"
#include <uuid/uuid.h>

static int channel_exist(server_t *server,
    const int client_fd, team_t *above_team)
{
    channel_t *channel;

    if (TAILQ_EMPTY(&above_team->channel_head))
        TAILQ_INIT(&above_team->channel_head);
    TAILQ_FOREACH(channel, &above_team->channel_head,
        channel_entries) {
        if (strcmp(channel->name, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s%s", CODE_302, CODE_101);
            return ERR_CMD;
        }
    }
    return WIN_CMD;
}

static int error_channel(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    team_t *above_team;

    if (server->cmd_arg.tab[1] == NULL || server->cmd_arg.tab[2] == NULL) {
        dprintf(client_fd, "%s",
            "create.c/error_channel : not enough argument\n");
        return ERR_CMD;
    }
    if (strlen(server->cmd_arg.tab[1]) >= MAX_NAME_LENGTH ||
        strlen(server->cmd_arg.tab[2]) >= MAX_DESCRIPTION_LENGTH)
            return ERR_CMD;
    TAILQ_FOREACH(above_team, &teams->team_head, team_entries) {
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0)
            return channel_exist(server, client_fd, above_team);
    }
    return WIN_CMD;
}

static void init_channel(server_t *server,
    team_t *above_team, const int client_fd, my_teams_t *teams)
{
    uuid_t tmp_uuid;
    channel_t *channel;

    channel = malloc(sizeof(channel_t));
    TAILQ_INSERT_TAIL(&above_team->channel_head,
        channel, channel_entries);
    strcpy(channel->name, server->cmd_arg.tab[1]);
    strcpy(channel->description, server->cmd_arg.tab[2]);
    uuid_generate_random(tmp_uuid);
    uuid_unparse(tmp_uuid, channel->uuid);
    TAILQ_INIT(&channel->thread_head);
    dprintf(client_fd, "%s%s\n%s\n%s\n%s", CODE_212, channel->uuid,
    channel->name, channel->description, CODE_101);
    server_event_channel_created(teams->command_context->team_uuid,
    channel->uuid, channel->name);
}

int create_channel(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *above_team;

    if (error_channel(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    for ((above_team) = ((&teams->team_head)->tqh_first); (above_team);
        (above_team) = ((above_team)->team_entries.tqe_next)) {
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0)
            init_channel(server, above_team, client_fd, teams);
    }
    return WIN_CMD;
}
