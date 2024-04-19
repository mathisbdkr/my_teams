/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_thread
*/

#include "my.h"
#include <uuid/uuid.h>

static int thread_exist(server_t *server,
    const int client_fd, channel_t *channel)
{
    thread_t *thread;

    if (TAILQ_EMPTY(&channel->thread_head))
        TAILQ_INIT(&channel->thread_head);
    TAILQ_FOREACH(thread, &channel->thread_head, thread_entries) {
        if (strcmp(thread->name, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s%s", CODE_302, CODE_101);
            return ERR_CMD;
        }
    }
    return WIN_CMD;
}

static int find_channel(server_t *server,
    const int client_fd, my_teams_t *teams, team_t *above_team)
{
    channel_t *channel;

    TAILQ_FOREACH(channel, &above_team->channel_head, channel_entries) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            return thread_exist(server, client_fd, channel);
        }
    }
    return WIN_CMD;
}

static int error_thread(server_t *server,
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
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0) {
            return find_channel(server, client_fd, teams, above_team);
        }
    }
    return WIN_CMD;
}

static void display_send(const int client_fd, my_teams_t *teams,
    thread_t *thread)
{
    dprintf(client_fd, "%s%s\n%s\n%ld\n%s\n%s\n%s", CODE_213,
    thread->uuid, thread->uuid_creator, thread->timestamp,
    thread->name, thread->description, CODE_101);
    server_event_thread_created(teams->command_context->channel_uuid,
    thread->uuid, thread->uuid_creator, thread->name,
    thread->description);
}

static void init_thread(server_t *server,
    my_teams_t *teams, team_t *above_team, const int client_fd)
{
    channel_t *channel;
    thread_t *thread;
    uuid_t tmp_uuid;

    for ((channel) = ((&above_team->channel_head)->tqh_first); (channel);
        (channel) = ((channel)->channel_entries.tqe_next)) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            thread = malloc(sizeof(thread_t));
            TAILQ_INSERT_TAIL(&channel->thread_head, thread, thread_entries);
            strcpy(thread->name, server->cmd_arg.tab[1]);
            strcpy(thread->description, server->cmd_arg.tab[2]);
            thread->timestamp = time(NULL);
            uuid_generate_random(tmp_uuid);
            strcpy(thread->uuid_creator,
                server->clients[server->user_index]->new_user->uuid);
            uuid_unparse(tmp_uuid, thread->uuid);
            TAILQ_INIT(&thread->thread_msg_head);
            display_send(client_fd, teams, thread);
        }
    }
}

int create_thread(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *above_team;

    if (error_thread(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    for ((above_team) = ((&teams->team_head)->tqh_first); (above_team);
        (above_team) = ((above_team)->team_entries.tqe_next)) {
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0)
            init_thread(server, teams, above_team, client_fd);
    }
    return WIN_CMD;
}
