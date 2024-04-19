/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save_database
*/

#include <unistd.h>
#include <fcntl.h>
#include "teams.h"

static void save_team_belong(const int fd, user_t *user)
{
    team_belong_t *team_belong;

    dprintf(fd, "\tteams_uuid=");
    TAILQ_FOREACH(team_belong, &user->team_belong_head,
        belong_entries) {
        dprintf(fd, "%s", team_belong->uuid);
        if (TAILQ_NEXT(team_belong, belong_entries) != NULL)
            dprintf(fd, ",");
    }
    dprintf(fd, "\n");
}

static void save_private_msg(const int fd, const my_teams_t teams)
{
    private_msg_t *private_msg;

    TAILQ_FOREACH(private_msg, &teams.priv_msg_head, private_msg_entries) {
        dprintf(fd, "private_msg:\n");
        dprintf(fd, "\tuuid_sender=%s\n", private_msg->uuid_sender);
        dprintf(fd, "\tuuid_other=%s\n", private_msg->uuid_other);
        dprintf(fd, "\tbody=%s\n", private_msg->body);
        dprintf(fd, "\ttimestamp=%ld\n", private_msg->timestamp);
    }
}

static void save_users(const int fd, const my_teams_t teams)
{
    user_t *user;

    TAILQ_FOREACH(user, &teams.user_head, user_entries) {
        dprintf(fd, "user:\n");
        dprintf(fd, "\tuuid=%s\n", user->uuid);
        dprintf(fd, "\tname=%s\n", user->name);
        dprintf(fd, "\tis_logged=%d\n", user->is_logged);
        save_team_belong(fd, user);
    }
}

static void save_threads_msg(const int fd, thread_t *thread)
{
    thread_msg_t *thread_msg;

    dprintf(fd, "\t\t\tthread_message=");
    TAILQ_FOREACH(thread_msg, &thread->thread_msg_head, thread_msg_entries) {
        dprintf(fd, "uuid_sender:%s,", thread_msg->uuid_sender);
        dprintf(fd, "body:%s,", thread_msg->body);
        dprintf(fd, "timestamp:%ld", thread_msg->timestamp);
        if (TAILQ_NEXT(thread_msg, thread_msg_entries) != NULL)
            dprintf(fd, ",");
    }
    dprintf(fd, "\n");
}

static void save_threads(const int fd, channel_t *channel)
{
    thread_t *thread;

    TAILQ_FOREACH(thread, &channel->thread_head, thread_entries) {
        dprintf(fd, "\t\tthread:\n");
        dprintf(fd, "\t\t\tuuid=%s\n", thread->uuid);
        dprintf(fd, "\t\t\tuuid_creator=%s\n", thread->uuid_creator);
        dprintf(fd, "\t\t\tname=%s\n", thread->name);
        dprintf(fd, "\t\t\tdescription=%s\n", thread->description);
        dprintf(fd, "\t\t\ttimestamp=%ld\n", thread->timestamp);
        save_threads_msg(fd, thread);
    }
}

static void save_channels(const int fd, team_t *team)
{
    channel_t *channel;

    TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
        dprintf(fd, "\tchannel:\n");
        dprintf(fd, "\t\tuuid=%s\n", channel->uuid);
        dprintf(fd, "\t\tname=%s\n", channel->name);
        dprintf(fd, "\t\tdescription=%s\n", channel->description);
        save_threads(fd, channel);
    }
}

static void save_teams(const int fd, const my_teams_t teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams.team_head, team_entries) {
        dprintf(fd, "team:\n");
        dprintf(fd, "\tuuid=%s\n", team->uuid);
        dprintf(fd, "\tname=%s\n", team->name);
        dprintf(fd, "\tdescription=%s\n", team->description);
        save_channels(fd, team);
    }
}

void save_database(const my_teams_t teams)
{
    int fd = open(".database", O_WRONLY | O_TRUNC | O_CREAT, 422);

    save_users(fd, teams);
    dprintf(fd, "\n");
    save_teams(fd, teams);
    dprintf(fd, "\n");
    save_private_msg(fd, teams);
    close(fd);
}
