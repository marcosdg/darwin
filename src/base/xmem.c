/*  xmem.c

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
    Wrappers for the standard memory manipulation functions.

    Generally, one of the main purposes behind any error-recovery mechanism is
    to prevent the user from loosing any relevant data generated during the
    execution of the program. However, darwin, currently, does not implement any
    mechanism to recover from errors caused either by bad user input or system
    failure. The reason behind is that darwin's execution is intended to either
    succeed or fail, as darwin will only output relevant data to the user at the
    end of its execution.
*/
/*
    #includes

    <string.h> strdup
    "report.h" <stdio.h>, <stdlib.h>
*/
#include <string.h>
#include "report.h"
#include "xmem.h"

void *
xmalloc(
        size_t size
) {
    void *mem_chunk = malloc(size);

    if (mem_chunk == NULL) {
        DARWIN_ERROR("Out of memory");
    }
    return mem_chunk;
}

char *
xstrdup(
        const char *s
) {
    char *copy = strdup(s);

    if (copy == NULL) {
        DARWIN_ERROR("Out of memory");
    }
    return copy;
}
