/*  result-generic-defs.h

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
    The X-Macro header of 'result.c' and the counterpart of
    'result-generic-protos.h'.

    This is part of a mechanism implemented via the C preprocessor to allow us to
    write 'generic' code via C macros.

    The job of this header is to store all the macro invocations of the macros
    defined in 'result.c', which in turn DEFINE all the 'generic' functions. The
    appropriate macro invocation will be selected at compilation time by the user
    via the compiler option 'CPPFLAGS'.
*/
#ifndef RESULT_GENERIC_DEFS_H_INCLUDED
#define RESULT_GENERIC_DEFS_H_INCLUDED

#if defined(DARWIN_USE_HAMPATH)
    DARWIN_DEFINE_FUNC_BEST_PHENOTYPE(Hampath, hampath)
#elif defined(DARWIN_USE_NQUEENS)
    DARWIN_DEFINE_FUNC_BEST_PHENOTYPE(NQueens, nqueens)
#elif defined(DARWIN_USE_SUBSETSUM)
    DARWIN_DEFINE_FUNC_BEST_PHENOTYPE(Subsetsum, subsetsum)

#else /* default */
    DARWIN_DEFINE_FUNC_BEST_PHENOTYPE(Subsetsum, subsetsum)
#endif

#endif /* RESULT_GENERIC_DEFS_H_INCLUDED */
