/*
** EPITECH PROJECT, 2024
** test
** File description:
** struct_redirect_print
*/

#ifndef STRUCT_REDIRECT_PRINT_H_
    #define STRUCT_REDIRECT_PRINT_H_

    #include "logging_client.h"

    #define NB_CODE 2
    #define CODE_101 "101 End of transmmission"

typedef struct {
    char *str;
    int (*ptr)(const char *str);
} display_err_exist_t;

typedef struct {
    char *str;
    int (*ptr)(void);
} display_err_access_t;

typedef struct {
    char *str;
    int (*ptr)(const char *str, const char *str2);
} client_user_event_t;

display_err_exist_t display_err_exist[] = {
    {"401", &client_error_unknown_user},
    {"402", &client_error_unknown_team},
    {"403", &client_error_unknown_channel},
    {"404", &client_error_unknown_thread},
    {'\0', NULL}
};

display_err_access_t display_err_access[] = {
    {"301", &client_error_unauthorized},
    {"302", &client_error_already_exist},
    {'\0', NULL}
};

client_user_event_t client_user_event[] = {
    {"201", &client_event_logged_in},
    {"202", &client_event_logged_out},
    {"205", &client_event_private_message_received},
    {"207", &client_print_subscribed},
    {"209", &client_print_unsubscribed},
    {'\0', NULL}
};

#endif /* !STRUCT_REDIRECT_PRINT_H_ */
