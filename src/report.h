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
  report.h
  29-12-14
  Marcos Díez García

  Error reporting functions.

*/
#ifndef REPORT_H_INCLUDED
#define REPORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/*
    For compatibility with older versions of GCC.
    (__FUNCTION__ is not standardized)
*/
#if __STDC_VERSION__ < 199901L
#   if __GNUC__ >= 2
#       define __func__ __FUNCTION__
#   else
#       define __func__ "<unknown>"
#   endif
#endif


#define ERROR(details)                                      \
    do {                                                    \
        fprintf(stderr, "darwin error: %s\n", (details));   \
        exit(EXIT_FAILURE);                                 \
    } while(0)

#define ERROR_VERBOSE(details)                                              \
    do {                                                                    \
        fprintf(stderr, "darwin error: [%s:%s] %s\n", __FILE__, __func__,   \
                (details));                                                 \
        exit(EXIT_FAILURE);                                                 \
    } while(0)

#endif /* REPORT_H_INCLUDED */
