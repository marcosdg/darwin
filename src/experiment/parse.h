/*  parse.h

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
#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

/*
extern char *
get_path(
        const char *instance_name
);
*/
extern char *
get_line(
        char *buffer,
        size_t size,
        FILE *stream
);
extern char *
str_chop(
        const char *str,
        const char *delim
);
#endif /* PARSE_H_INCLUDED */