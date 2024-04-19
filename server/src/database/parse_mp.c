/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_mp
*/

#include "teams.h"
#include "my.h"

static void fill_mp(char *line, private_msg_t *dm, char **array)
{
    if (strncmp(line, "\tuuid_sender=", strlen("\tuuid_sender=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(dm->uuid_sender, array[1]);
    if (strncmp(line, "\tuuid_other=", strlen("\tuuid_other=")) == 0 &&
        strlen(array[1]) < MAX_UUID_LENGTH)
        strcpy(dm->uuid_other, array[1]);
    if (strncmp(line, "\tbody=", strlen("\tbody=")) == 0 &&
        strlen(array[1]) < MAX_BODY_LENGTH)
        strcpy(dm->body, array[1]);
    if (strncmp(line, "\ttimestamp=", strlen("\ttimestamp=")) == 0)
        dm->timestamp = my_get_timestamp(array[1]);
}

void parse_mp(my_teams_t *teams, char *line, int *is_user)
{
    static private_msg_t *dm;
    char **array = word_array(line, "\t\n=,:");

    if (strcmp(line, "private_msg:\n") == 0) {
        dm = malloc(sizeof(private_msg_t));
        TAILQ_INSERT_TAIL(&teams->priv_msg_head, dm, private_msg_entries);
        *is_user = 2;
    }
    if (*is_user != 2 || array_size(array) < 2) {
        free(array);
        return;
    }
    fill_mp(line, dm, array);
}
