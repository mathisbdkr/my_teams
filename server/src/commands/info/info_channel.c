/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_channel
*/

#include "my.h"

static void find_channel(const int client_fd, my_teams_t *teams, team_t *team)
{
    channel_t *channel;

    TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            dprintf(client_fd, "%s%s\n%s\n%s\n%s", CODE_218,
            channel->uuid, channel->name, channel->description, CODE_101);
            return;
        }
    }
    dprintf(client_fd, "%s%s\n%s", CODE_403,
    teams->command_context->channel_uuid, CODE_101);
}

int info_channel(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0)
            find_channel(client_fd, teams, team);
    }
    return WIN_CMD;
}
