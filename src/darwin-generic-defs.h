/*  darwin-generic-defs.h

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
    The X-Macro header of 'darwin.c'.

    This is part of a mechanism implemented via the C preprocessor to allow us to
    write 'generic' code via C macros.

    The job of this header is to store all the macro invocations of the macros
    defined in 'darwin.c', which in turn DEFINE all the 'generic' functions. The
    appropriate macro invocation will be selected at compilation time by the user
    via the compiler option 'CPPFLAGS'.
*/
#ifndef DARWIN_GENERIC_DEFS_H_INCLUDED
#define DARWIN_GENERIC_DEFS_H_INCLUDED

#if defined(DARWIN_USE_HAMPATH)
    DARWIN_DEFINE_FUNC_RUN(Hampath, hampath)
#elif defined(DARWIN_USE_NQUEENS)
    DARWIN_DEFINE_FUNC_RUN(NQueens, nqueens)
#elif defined(DARWIN_USE_SUBSETSUM)
    DARWIN_DEFINE_FUNC_RUN(Subsetsum, subsetsum)

#else /* default */
    DARWIN_DEFINE_FUNC_RUN(Subsetsum, subsetsum)
#endif

#endif /* DARWIN_GENERIC_DEFS_H_INCLUDED */
