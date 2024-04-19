/*
** EPITECH PROJECT, 2024
** test
** File description:
** struct_client
*/

#ifndef STRUCT_CLIENT_H_
    #define STRUCT_CLIENT_H_

    #include "logging_client.h"

    #define NB_CODE 2

static char *const other_code[NB_CODE] = {
    "206",
    "210"
};

typedef struct client_buf_s {
    char *code;
    int pass;
    int loop_read;
    char *all_reponse;
} client_buf_t;

#endif /* !STRUCT_CLIENT_H_ */
