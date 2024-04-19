/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_teams
*/


#include "teams.h"
#include "my.h"

static void fill_team(enum TEAM_CONTEXT data, char *line,
    team_t *team, char **array)
{
    if (data != TEAM)
        return;
    if (strncmp(line, "\tuuid=", strlen("\tuuid=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(team->uuid, array[1]);
    if (strncmp(line, "\tname=", strlen("\tname=")) == 0 &&
        strlen(array[1]) < MAX_NAME_LENGTH)
        strcpy(team->name, array[1]);
    if (strncmp(line, "\tdescription=", strlen("\tdescription=")) == 0 &&
        strlen(array[1]) < MAX_DESCRIPTION_LENGTH)
        strcpy(team->description, array[1]);
}

static void fill_channel(enum TEAM_CONTEXT data, char *line,
    channel_t *channel, char **array)
{
    if (data != CHANNEL)
        return;
    if (strncmp(line, "\t\tuuid=", strlen("\t\tuuid=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(channel->uuid, array[1]);
    if (strncmp(line, "\t\tname=", strlen("\t\tname=")) == 0 &&
        strlen(array[1]) < MAX_NAME_LENGTH)
        strcpy(channel->name, array[1]);
    if (strncmp(line, "\t\tdescription=", strlen("\t\tdescription=")) == 0 &&
        strlen(array[1]) < MAX_DESCRIPTION_LENGTH)
        strcpy(channel->description, array[1]);
}

static void fill_thread_message(thread_t *thread, char **array)
{
    thread_msg_t *thread_msg;

    for (size_t i = 1; array[i] != NULL; i += 2) {
        if (strcmp(array[i], "uuid_sender") == 0) {
            thread_msg = malloc(sizeof(private_msg_t));
            TAILQ_INSERT_TAIL(&thread->thread_msg_head, thread_msg,
                thread_msg_entries);
            strcpy(thread_msg->uuid_sender, array[i + 1]);
        }
        if (strcmp(array[i], "body") == 0 &&
        strlen(array[i + 1]) < MAX_BODY_LENGTH)
            strcpy(thread_msg->body, array[i + 1]);
        if (strcmp(array[i], "timestamp") == 0)
            thread_msg->timestamp = my_get_timestamp(array[i + 1]);
    }
}

static void fill_thread(enum TEAM_CONTEXT data, char *line,
    thread_t *thread, char **array)
{
    if (data != THREAD)
        return;
    if (strncmp(line, "\t\t\tuuid=", strlen("\t\t\tuuid=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(thread->uuid, array[1]);
    if (strncmp(line, "\t\t\tuuid_creator=",
    strlen("\t\t\tuuid_creator=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(thread->uuid_creator, array[1]);
    if (strncmp(line, "\t\t\tname=", strlen("\t\t\tname=")) == 0 &&
        strlen(array[1]) < MAX_NAME_LENGTH)
        strcpy(thread->name, array[1]);
    if (strncmp(line, "\t\t\tdescription=", strlen("\t\t\tdescription=")) == 0
        && strlen(array[1]) < MAX_DESCRIPTION_LENGTH)
        strcpy(thread->description, array[1]);
    if (strncmp(line, "\t\t\ttimestamp=", strlen("\t\t\ttimestamp=")) == 0)
        thread->timestamp = my_get_timestamp(line);
    if (strncmp(line, "\t\t\tthread_message=",
        strlen("\t\t\tthread_message=")) == 0)
        fill_thread_message(thread, array);
}

static bool is_team_line(int *is_user, char *line,
    my_teams_t *teams, team_t **team)
{
    if (strcmp(line, "team:\n") == 0) {
        *is_user = 1;
        *team = malloc(sizeof(team_t));
        TAILQ_INSERT_TAIL(&teams->team_head, *team, team_entries);
        TAILQ_INIT(&(*team)->channel_head);
        return true;
    }
    return false;
}

static bool is_channel_line(char *line, team_t *team, channel_t **channel)
{
    if (strcmp(line, "\tchannel:\n") == 0) {
        *channel = malloc(sizeof(channel_t));
        TAILQ_INSERT_TAIL(&team->channel_head, *channel, channel_entries);
        TAILQ_INIT(&(*channel)->thread_head);
        return true;
    }
    return false;
}

static bool is_thread_line(char *line, channel_t *channel, thread_t **thread)
{
    if (strcmp(line, "\t\tthread:\n") == 0) {
        *thread = malloc(sizeof(thread_t));
        TAILQ_INSERT_TAIL(&channel->thread_head, *thread, thread_entries);
        TAILQ_INIT(&(*thread)->thread_msg_head);
        return true;
    }
    return false;
}

void parse_teams(my_teams_t *teams, char *line, int *is_user)
{
    static team_t *team;
    static channel_t *channel;
    static thread_t *thread;
    static enum TEAM_CONTEXT data = TEAM;
    char **array = word_array(line, "\t\n=,:");

    fill_channel(data, line, channel, array);
    fill_thread(data, line, thread, array);
    if (is_team_line(is_user, line, teams, &team))
        data = TEAM;
    if (is_channel_line(line, team, &channel))
        data = CHANNEL;
    if (is_thread_line(line, channel, &thread))
        data = THREAD;
    if (array_size(array) < 2 || *is_user != 1) {
        free(array);
        return;
    }
    fill_team(data, line, team, array);
}
