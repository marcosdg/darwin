# Automake script for darwin.
#
# This is part of the darwin program.
#
# darwin. A simple genetic algorithm implementation with a self-adaptative
# strategy.
#
# Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>
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


ACLOCAL_AMFLAGS = -I m4 --install
AM_LDFLAGS = -lrt -lm


bin_PROGRAMS = testsubsetsum
testsubsetsum_SOURCES = ./src/base/report.h ./src/base/report.c \
						./src/base/random.h ./src/base/random.c ./src/genome.h \
						./src/genome.c ./src/experiment/subset_sum.h \
						./src/experiment/subset_sum.c ./src/test_subset_sum.c

##bin_PROGRAMS = testnqueens
##testnqueens_SOURCES = ./src/base/report.h ./src/base/report.c ./src/base/random.h \
##					  ./src/base/random.c ./src/base/bits.h ./src/base/bits.c \
##					  ./src/genome.h ./src/genome.c ./src/experiment/queen.h \
##					  ./src/experiment/queen.c ./src/experiment/nqueens.h \
##					  ./src/experiment/nqueens.c ./src/test_nqueens.c

##bin_PROGRAMS = testoperators testrandom
##testrandom_SOURCES = ./src/base/report.h ./src/base/report.c ./src/base/random.h \
##					 ./src/base/random.c ./src/test_random.c
##testoperators_SOURCES = ./src/base/report.h ./src/base/report.c \
##						./src/base/random.h ./src/base/random.c ./src/genome.h \
##						./src/genome.c ./src/operators.h ./src/operators.c \
##						./src/test_operators.c

EXTRA_DIST = m4/NOTES # autoreconf -i bug (v.268)
