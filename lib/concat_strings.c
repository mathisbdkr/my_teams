/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** concat_strings
*/

#include <stdlib.h>
#include <string.h>

char *concat_strings(char *str1, char *str2, char *delim)
{
    char *tmp = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 2));

    if (tmp == NULL)
        return NULL;
    *tmp = '\0';
    strcpy(tmp, str1);
    tmp = strcat(tmp, delim);
    tmp = strcat(tmp, str2);
    return tmp;
}
