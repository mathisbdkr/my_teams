/*
** EPITECH PROJECT, 2024
** test
** File description:
** redirect_print
*/

#include "client.h"
#include "struct_redirect_print.h"

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

static int display_msg(char **tab, int nb)
{
    if (nb == 1) {
        client_event_thread_reply_received(tab[0], tab[1], tab[2], tab[3]);
        return 1;
    }
    if (nb != 0) {
        return 1;
    }
    for (int i = 0; tab[i] != NULL; i += 3) {
        i = pass_or_continue(tab, i, 3);
        if (i < 0) {
            return 1;
        }
        client_private_message_print_messages(tab[i], atoi(tab[i + 1]),
        tab[i + 2]);
    }
    return 1;
}

static int display_no_loop_print(char **tab, char *first_word)
{
    for (size_t y = 0; display_err_exist[y].str != NULL; y++) {
        if (strcmp(display_err_exist[y].str, first_word) == 0) {
            display_err_exist[y].ptr(tab[0]);
            return 1;
        }
    }
    for (size_t y = 0; display_err_access[y].str != NULL; y++) {
        if (strcmp(display_err_access[y].str, first_word) == 0) {
            display_err_access[y].ptr();
            return 1;
        }
    }
    for (size_t y = 0; client_user_event[y].str != NULL; y++) {
        if (strcmp(client_user_event[y].str, first_word) == 0) {
            client_user_event[y].ptr(tab[0], tab[1]);
            return 1;
        }
    }
    return 0;
}

static int redirect_print(char **tab, client_buf_t buf_struct)
{
    int pass = 0;
    char *first_word = strdup(buf_struct.code);

    pass += display_no_loop_print(tab, first_word);
    pass += display_thread_reply(tab, first_word);
    pass += display_thread_loop(tab, first_word);
    pass += display_users_team(tab, first_word);
    pass += display_help(tab, first_word);
    for (size_t i = 0; i < NB_CODE; i++) {
        if (strcmp(other_code[i], first_word) == 0) {
            display_msg(tab, i);
            pass += 1;
        }
    }
    return pass;
}

static bool is_end(char *msg, char **tab)
{
    char *tmp;

    if (strlen(msg) < 1) {
        return true;
    }
    for (int i = 0; tab[i] != NULL; i++) {
        tmp = malloc(sizeof(char) * 4);
        strncpy(tmp, tab[i], 3);
        tmp[3] = '\0';
        if (strcmp(tmp, "101") == 0) {
            return 1;
        }
    }
    return false;
}

int select_display_methode(client_buf_t buf_struct)
{
    char **tab = word_array(buf_struct.all_reponse, "\n");
    int return_status = is_end(strdup(buf_struct.all_reponse), tab);

    if (buf_struct.pass > 1) {
        free(buf_struct.code);
    }
    if (strlen(buf_struct.all_reponse) <= 0) {
        return 1;
    }
    if (redirect_print(tab, buf_struct) == 0) {
        return 1;
    }
    return return_status;
}
