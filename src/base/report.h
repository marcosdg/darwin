/*  report.h

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
    strategy.

    Copyright (C) 2015 Marcos Diez García <marcos.diez.garcia@gmail.com>

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
    Common error-reporting utility functions.
*/
/*
    #included

    <stdio.h> fflush, fprintf
    <stdlib.h> exit, EXIT_FAILURE
    "../../config.h" DARWIN_DEBUG_MODE
*/
#ifndef REPORT_H_INCLUDED
#define REPORT_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "../../config.h"
#endif /* HAVE_CONFIG_H */
#include <stdio.h>
#include <stdlib.h>
/*
    For compatibility with older versions of GCC (__FUNCTION__ is not
    standardized).
*/
#if __STDC_VERSION__ < 199901L
#   if __GNUC__ >= 2
#       define __func__ __FUNCTION__
#   else
#       define __func__ "<unknown function>"
#   endif
#endif

#define DARWIN_ERROR(details)                                           \
    do {                                                                \
        if (DARWIN_DEBUG_MODE) {                                        \
            fprintf(stderr, "darwin error: in %s: %s (%s at line %i)\n",\
                    __FILE__, (details), __func__, __LINE__);           \
        } else {                                                        \
            fprintf(stderr, "darwin error: %s\n", (details));           \
        }                                                               \
        fflush(stderr);                                                 \
        exit(EXIT_FAILURE);                                             \
    } while (0)

#endif /* REPORT_H_INCLUDED */
