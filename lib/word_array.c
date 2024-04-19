/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** word_array
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int is_delimiter(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i])
            return (0);
    }
    return (1);
}

static int cut_str_pt2(char const *str, char *delim,
    int check1, int nb_of_spaces)
{
    int check2 = 2;
    int last_space = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1)
            last_space += 1;
        if (last_space == nb_of_spaces)
            return (i);
    }
    return (0);
}

static int cut_str(char const *str, char *delim)
{
    int nb_of_spaces = 0;
    int check1 = 2;
    int check2 = 2;

    for (int i = 0; str[i] != '\0'; i++) {
        check1 = is_delimiter(str[i], delim);
            if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1)
            nb_of_spaces += 1;
    }
    return cut_str_pt2(str, delim, check1, nb_of_spaces);
}

static int check_character(char const *str, char *delim, int cut_here)
{
    int count_w = 0;
    int check2 = 2;
    int check1 = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1
        && i != 0 && i < cut_here) {
            count_w += 1;
        }
    }
    return (count_w);
}

static void word_array1(char const *str, char **tab, char *delim, int cut_here)
{
    int i = 0;
    int x = 0;
    int number_of_characters = 0;
    int check2 = 2;
    int check1 = 0;

    for (i = 0; str[i] != '\0'; i++) {
        check1 = is_delimiter(str[i], delim);
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (check1 == 0 && check2 == 1
        && i != 0 && i < cut_here) {
            tab[x] = malloc(sizeof(char) * (number_of_characters + 1));
            number_of_characters = 0;
            x++;
        }
        if (check1 == 1)
            number_of_characters++;
    }
    tab[x] = malloc(sizeof(char) * (number_of_characters + 1));
}

void word_array2(char const *str, char **tab, char *delim, int cut_here)
{
    int x = 0;
    int y = 0;
    int check2 = 2;

    for (int i = 0; str[i] != '\0'; i++) {
        if (i > 0)
            check2 = is_delimiter(str[i - 1], delim);
        if (is_delimiter(str[i], delim) == 0 &&
        check2 == 1 && i != 0 && i < cut_here) {
            tab[x][y] = '\0';
            y = 0;
            x++;
        }
        if (is_delimiter(str[i], delim) == 1) {
            tab[x][y] = str[i];
            y++;
        }
    }
    tab[x][y] = '\0';
    tab[x + 1] = NULL;
}

char **start_word_array(char const *str, char *delim, int cut_here)
{
    int number_of_words = check_character(str, delim, cut_here) + 1;
    char **tab = malloc(sizeof(char *) * (number_of_words + 1));

    word_array1(str, tab, delim, cut_here);
    word_array2(str, tab, delim, cut_here);
    return tab;
}

char **word_array(char const *str, char *delim)
{
    int cut_here = strlen(str);
    int check = is_delimiter(str[strlen(str) - 1], delim);

    if (check == 0) {
        cut_here = cut_str(str, delim);
    }
    return (start_word_array(str, delim, cut_here));
}
