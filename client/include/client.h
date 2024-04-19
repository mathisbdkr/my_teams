/*
** EPITECH PROJECT, 2024
** test
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <sys/select.h>
    #include "struct_client.h"

int array_size(char **array);
void print_array(char **array);
void free_array(char **array);
char *concat_strings(char *str1, char *str2, char *delim);
bool array_is_number(char **array);
char **word_array(char const *str, char *delim);

int client(const char **av);

int select_display_methode(client_buf_t buf_struct);
int display_thread_loop(char **tab, char *first_word);
int display_users_team(char **tab, char *first_word);
int display_thread_reply(char **tab, char *first_word);
int display_help(char **tab, char *first_word);

#endif /* !CLIENT_H_ */
