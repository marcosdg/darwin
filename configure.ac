dnl Autoconf script for darwin.
dnl
dnl This is part of the darwin program.
dnl
dnl darwin. A simple genetic algorithm implementation with a self-adaptative
dnl strategy.
dnl
dnl Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
dnl GNU General Public License for more details.
dnl You should have received a copy of the GNU General Public License
dnl along with this program. If not, see <http://www.gnu.org/licenses/>.

dnl Force autoconf to be, at least, this version number.
AC_PREREQ([2.68])
AC_INIT([darwin], [0.01], [marcos.diez.garcia@gmail.com])
dnl Safety check: list a source file that would not be in other directories.
AC_CONFIG_SRCDIR([src/genome.h])
dnl Place configuration results here, so we can easily #include them.
AC_CONFIG_HEADERS([config.h])
dnl Place autotools auxiliary files in a subdir, not to clutter top dir.
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
dnl Enable 'automake' to simplify creating Makefiles. The 'subdir-objects'
dnl options allows us to organize source files in subdirectories.
AM_INIT_AUTOMAKE([1.11 subdir-objects -Wall -Werror])
AC_CONFIG_FILES([Makefile])

dnl Look for a C compiler.
AC_PROG_CC
AM_PROG_CC_C_O

dnl Checks for libraries.
AC_CHECK_LIB([m], [exp])
AC_CHECK_LIB([rt], [clock_gettime])

dnl Checks for header files.
AC_CHECK_HEADERS([float.h limits.h stdlib.h string.h])
dnl Checks for typedefs, structures, and compiler characteristics.
dnl Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([clock_gettime memset])

AC_OUTPUT
