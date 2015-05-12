/*  parse.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a self-adaptative
    strategy.

    Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*
    Common parse utility functions.
*/
#include <assert.h>
#include <stdio.h>  /* fgets */
#include <stdlib.h> /* atoi, malloc, NULL */
#include <string.h> /* strcat, strdup, strlen, strsep */
#include "parse.h"

/*
char *
get_path(
        const char *instance_name
) {

    // DATADIR '/' instance_name '\0'

    size_t length = (strlen(DATADIR) + 1 + strlen(instance_name)) + 1;
    char *path = (char *) malloc(length * sizeof(char));
    strcat(path, DATADIR);
    strcat(path, "/");
    strcat(path, instance_name);

    return path;
}
*/

char *
get_line(
        char *buffer,
        size_t size,
        FILE *stream
) {
    size_t len = 0;
    /*
        EOF or '\n'?
    */
    if (fgets(buffer, size, stream) == NULL) {
        return NULL;
    }
    /*
        Remove trailing '\n'.
    */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}

char *
str_chop(
        const char *str,
        const char *delim
) {
    size_t length = strlen(str) + 1;                        /* count '\0' */
    char *chunks = malloc(length * sizeof(char));
    char *copy = strdup(str);                               /* be safe */
    int i = 0;
    if (copy == NULL || chunks == NULL) {
        return NULL;
    }
    while (*copy) {
        chunks[i] = *(strsep(&copy, delim));
        i += 1;
    }
    return chunks;
}
