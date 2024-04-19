/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** list_thread
*/

#include "my.h"

static void find_channel(const int client_fd, my_teams_t *teams, team_t *team)
{
    channel_t *channel;
    thread_t *thread;

    TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            dprintf(client_fd, "%s", CODE_219);
            TAILQ_FOREACH(thread, &channel->thread_head, thread_entries) {
                dprintf(client_fd, "%s\n%s\n%ld\n%s\n%s\n",
                thread->uuid, thread->uuid_creator,
                thread->timestamp, thread->name, thread->description);
            }
            dprintf(client_fd, "%s", CODE_101);
        }
    }
}

int list_thread(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0) {
            find_channel(client_fd, teams, team);
        }
    }
    return WIN_CMD;
}
