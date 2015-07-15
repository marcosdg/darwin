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
/*
    #included

    <stdio.h> fgets, NULL
    <stdlib.h> free
    <string.h> strlen, strsep
    "../base/xmem.h" xmalloc, xstrdup
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../base/xmem.h"
#include "parse.h"

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
    assert(str != NULL);
    assert(delim != NULL);

    size_t length = strlen(str) + 1; /* Count the '\0'. */
    char *chunks = xmalloc(length * sizeof(char));
    /*
        strsep alters its first string argument; we need a copy of 'str' and the
        pointer to its first address, since otherwise we would be freeing a
        different address of the malloc'ed one.
    */
    char *copy = xstrdup(str);
    char *fresh_copy = copy;
    int i = 0;

    while (*copy) {
        chunks[i] = *(strsep(&copy, delim));
        i += 1;
    }
    free(fresh_copy);
    return chunks;
}
