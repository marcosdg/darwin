# Autoconf script for darwin.
#
# This is part of the darwin program.
#
# darwin. A simple genetic algorithm implementation with a self-adaptative
# strategy.
#
# Copyright (C) 2015 Marcos Diez García <marcos.diez.garcia@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

###############################################################################
# AUTOCONF AND AUTOMAKE SETUP
###############################################################################
# Force autoconf to be, at least, this version number.
AC_PREREQ([2.68])
AC_INIT([darwin], [0.0.1], [marcos.diez.garcia@gmail.com])
AC_COPYRIGHT([Copyright (C) 2015 Marcos Diez García])

# Safety check: list a source file that would not be in other directories.
AC_CONFIG_SRCDIR([src/genome.h])

# Place configuration results here, so we can easily #include them.
AC_CONFIG_HEADERS([config.h])

# Place autotools auxiliary files in a subdir, not to clutter top dir.
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# Enable 'automake' to simplify creating Makefiles. The 'subdir-objects'
# options allows us to organize source files in subdirectories.
AM_INIT_AUTOMAKE([1.11 subdir-objects -Wall -Werror])

# Darwin configuration features:
#   1. Debugging mode
AC_ARG_ENABLE([darwin-debug-mode],
              [AS_HELP_STRING([--enable-darwin-debug-mode],
                              [Enable darwin debug mode. Disabled by default.])],
              [AC_DEFINE([DARWIN_DEBUG_MODE], [1], [Enabled is 1. Disabled is 0.])],
              [AC_DEFINE([DARWIN_DEBUG_MODE], [0], [Enabled is 1. Disabled is 0.])])
###############################################################################
# PERL
###############################################################################
AC_CHECK_PROG(PERL, perl, perl, no)
if test "$PERL" = no; then
    AC_MSG_ERROR(Could not find Perl. Perl is required by darwin to generate
                 certain data files. Please make sure is installed in your system)
fi
###############################################################################
# C
###############################################################################
# Compiler.
AC_PROG_CC
AM_PROG_CC_C_O

# Libraries.
AC_CHECK_LIB([m], [exp])
AC_CHECK_LIB([rt], [clock_gettime])

# Header files.
AC_CHECK_HEADERS([float.h limits.h stddef.h stdlib.h string.h])

# Typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([clock_gettime memset strdup strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
