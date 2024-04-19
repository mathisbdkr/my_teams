/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-yanis.harkouk
** File description:
** word_array
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t array_size(char **array)
{
    size_t size = 0;

    while (array[size] != NULL)
        size += 1;
    return size;
}

void print_array(char **array)
{
    for (size_t i = 0; array[i] != NULL; i += 1)
        printf("word:[%s]\n", array[i]);
}

void free_array(char **array)
{
    for (size_t i = 0; array[i] != NULL; i += 1)
        free(array[i]);
    free(array);
}
