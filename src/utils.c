/*
  darwin. A simple genetic algorithm implementation with a
  self-adaptative strategy.

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
  utils.c
  29-12-14
  Marcos Díez García

  Some miscellaneous functions.

*/
#include <stdlib.h>
#include <stdio.h>


void error(char *details)
{
    fputs("darwin Error: ", stderr);
    fputs(details, stderr);
    fputc('\n', stderr);
    exit(1);
}

void error_verbose(char *file_name, char *function_name, char *details)
{
    fputs("darwin Error: ", stderr);
    fprintf(stderr, "[FILE %s]", file_name);
    fprintf(stderr, "(FUNCTION %s) ", function_name);
    fputs(details, stderr);
    fputc('\n', stderr);
    exit(1);
}

