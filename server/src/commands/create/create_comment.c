/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_comment
*/

#include "my.h"
#include <uuid/uuid.h>

static bool is_receivable(my_teams_t *teams, user_t *user)
{
    team_belong_t *team_belong;

    TAILQ_FOREACH(team_belong, &user->team_belong_head,
        belong_entries) {
        if (strcmp(teams->command_context->team_uuid,
            team_belong->uuid) == 0)
            return true;
    }
    return false;
}

static void print_receiver(server_t *server, my_teams_t *teams,
    thread_msg_t *comment, size_t index)
{
    user_t *user;
    bool send = false;

    TAILQ_FOREACH(user, &teams->user_head, user_entries) {
        if (server->clients[index]->my_uuid == NULL)
            continue;
        if (strcmp(user->uuid, server->clients[index]->my_uuid) == 0
            && strcmp(user->uuid, comment->uuid_sender) != 0
            && server->clients[index]->is_connected == true)
                send = is_receivable(teams, user);
    }
    if (send) {
        dprintf(server->clients[index]->client_fd,
            "%s%s\n%s\n%s\n%s\n%s",
            CODE_210, teams->command_context->team_uuid,
            teams->command_context->thread_uuid,
            comment->uuid_sender, comment->body, CODE_101);
    }
}

static void send_all_reply(server_t *server, my_teams_t *teams,
    thread_msg_t *comment)
{
    for (int index = 0; index != MAX_USER; index += 1) {
        print_receiver(server, teams, comment, index);
    }
}

static void fill_comment(server_t *server,
    thread_t *thread, const int client_fd, my_teams_t *teams)
{
    thread_msg_t *comment;

    if (TAILQ_EMPTY(&thread->thread_msg_head))
        TAILQ_INIT(&thread->thread_msg_head);
    comment = malloc(sizeof(thread_msg_t));
    TAILQ_INSERT_TAIL(&thread->thread_msg_head,
        comment, thread_msg_entries);
    strcpy(comment->uuid_sender,
        server->clients[server->user_index]->new_user->uuid);
    strcpy(comment->body, server->cmd_arg.tab[1]);
    comment->timestamp = time(NULL);
    dprintf(client_fd, "%s%s\n%s\n%ld\n%s\n%s", CODE_217, thread->uuid,
    server->clients[server->user_index]->my_uuid, thread->timestamp,
    comment->body, CODE_101);
    server_event_reply_created(thread->uuid, comment->uuid_sender,
    comment->body);
    send_all_reply(server, teams, comment);
}

static void init_channel(server_t *server, my_teams_t *teams,
    channel_t *channel, const int client_fd)
{
    thread_t *thread;

    for ((thread) = ((&channel->thread_head)->tqh_first); (thread);
        (thread) = ((thread)->thread_entries.tqe_next)) {
        if (strcmp(thread->uuid, teams->command_context->thread_uuid) == 0)
            fill_comment(server, thread, client_fd, teams);
    }
}

static void find_channel(server_t *server,
    my_teams_t *teams, team_t *above_team, const int client_fd)
{
    channel_t *channel;

    for ((channel) = ((&above_team->channel_head)->tqh_first);
    (channel); (channel) = ((channel)->channel_entries.tqe_next)) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            init_channel(server, teams, channel, client_fd);
        }
    }
}

int create_comment(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *above_team;

    if (server->cmd_arg.len != 2) {
        dprintf(client_fd, "%s",
            "create.c/error_channel : not enough argument\n");
        return ERR_CMD;
    }
    if (strlen(server->cmd_arg.tab[1]) >= MAX_BODY_LENGTH)
        return ERR_CMD;
    for ((above_team) = ((&teams->team_head)->tqh_first); (above_team);
        (above_team) = ((above_team)->team_entries.tqe_next)) {
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0) {
            find_channel(server, teams, above_team, client_fd);
        }
    }
    return WIN_CMD;
}
