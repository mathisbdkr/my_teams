/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-yanis.harkouk
** File description:
** str_is_number
*/

#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

static bool str_is_number(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i += 1)
        if (isdigit(str[i]) == 0)
            return false;
    return true;
}

bool array_is_number(char **array)
{
    for (size_t i = 0; array[i] != NULL; i += 1)
        if (!str_is_number(array[i]))
            return false;
    return true;
}
