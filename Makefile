# Makefile

# This is part of the darwin program.

# darwin. A simple genetic algorithm implementation with a self-adaptative
# strategy.

# Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>

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

CFLAGS = -Wall -Wextra
LDLIBS = -lm -lrt

test_random_SOURCES = src/lib/random.c src/test_random.c
test_operators_SOURCES = src/lib/random.c src/genome.c src/operators.c \
						 src/test_operators.c

all: tests

tests: test_random test_operators
test_random:
	$(CC) $(CFLAGS) $(test_random_SOURCES) -o $@ $(LDLIBS)
test_operators:
	$(CC) $(CFLAGS) $(test_operators_SOURCES) -o $@ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) test_random test_operators
