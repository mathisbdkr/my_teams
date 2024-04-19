/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myteams-yanis.harkouk
** File description:
** display_multiple_print
*/

#include "struct_loop_print.h"
#include "client.h"

static int check_str(char *str)
{
    char *tmp;

    tmp = malloc(sizeof(char) * 4);
    strncpy(tmp, str, 3);
    tmp[3] = '\0';
    if (strcmp(tmp, "101") == 0) {
        return 1;
    }
    return 0;
}

static int pass_or_continue(char **tab, int i, int size)
{
    if (check_str(tab[i]) == 1) {
        return -1;
    }
    if (array_size(tab) - i < size) {
        return -1;
    }
    if (strcmp(tab[i], CODE_101) == 0 && array_size(tab) - i > size) {
        return (i + 1);
    } else if (strcmp(tab[i], CODE_101) == 0) {
        return - 1;
    }
    return i;
}

static void loop_display_users(char **tab, int y)
{
    for (int i = 0; tab[i] != NULL; i += 3) {
        i = pass_or_continue(tab, i, 3);
        if (i < 0) {
            return;
        }
        display_users[y].ptr(tab[i], tab[i + 1], atoi(tab[i + 2]));
    }
}

static void loop_display_team(char **tab, int y)
{
    for (int i = 0; tab[i] != NULL; i += 3) {
        i = pass_or_continue(tab, i, 3);
        if (i < 0) {
            return;
        }
        display_team_channel[y].ptr(tab[i], tab[i + 1], tab[i + 2]);
    }
}

static void loop_display_thread(char **tab, int y)
{
    for (int i = 0; tab[i] != NULL; i += 5) {
        i = pass_or_continue(tab, i, 5);
        if (i < 0) {
            return;
        }
        display_thread[y].ptr(tab[i], tab[i + 1], (time_t) atoi(tab[i + 2]),
            tab[i + 3], tab[i + 4]);
    }
}

void loop_display_thread_replies(char **tab, int y)
{
    for (int i = 0; tab[i] != NULL; i += 4) {
        i = pass_or_continue(tab, i, 4);
        if (i < 0) {
            return;
        }
        print_reply[y].ptr(tab[i], tab[i + 1], (time_t) atoi(tab[i + 2]),
            tab[i + 3]);
    }
}

int display_users_team(char **tab, char *first_word)
{
    for (size_t y = 0; display_users[y].str != NULL; y++) {
        if (strcmp(display_users[y].str, first_word) == 0) {
            loop_display_users(tab, y);
            return 1;
        }
    }
    for (size_t y = 0; display_team_channel[y].str != NULL; y++) {
        if (strcmp(display_team_channel[y].str, first_word) == 0) {
            loop_display_team(tab, y);
            return 1;
        }
    }
    return 0;
}

int display_thread_loop(char **tab, char *first_word)
{
    for (size_t y = 0; display_thread[y].str != NULL; y++) {
        if (strcmp(display_thread[y].str, first_word) == 0) {
            loop_display_thread(tab, y);
            return 1;
        }
    }
    return 0;
}

int display_thread_reply(char **tab, char *first_word)
{
    for (size_t y = 0; print_reply[y].str != NULL; y++) {
        if (strcmp(print_reply[y].str, first_word) == 0) {
            loop_display_thread_replies(tab, y);
            return 1;
        }
    }
    return 0;
}

int display_help(char **tab, char *first_word)
{
    if (strcmp(first_word, "224") != 0) {
        return 0;
    }
    for (int i = 0; tab[i] != NULL; i += 1) {
        i = pass_or_continue(tab, i, 1);
        if (i < 0) {
            return 1;
        }
        printf("%s\n", tab[i]);
    }
    return 1;
}
