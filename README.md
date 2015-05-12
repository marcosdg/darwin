darwin
======

(development)

This academic project aims to offer a comparative view, regarding performance, between two implementations of a simple Genetic Algorithm: one using a self-[adaptative](https://en.wikipedia.org/wiki/Genetic_algorithm#Adaptive_GAs) strategy
and one which does not. 

Given the complexity of the role that play [Evolution Strategies](https://en.wikipedia.org/wiki/Evolution_strategy), as one of the subcategories of [Meta-heuristics](http://www.scholarpedia.org/article/Metaheuristic_Optimization), in Genetic Algorithms, the study here presented focuses on answering the following question: 

    how significant is the gain in performance that a Genetic Algorithm can achieve just by
    considering an adaptative mutation operator?

Please, see the [wiki](https://github.com/marcosdg/darwin/wiki) for more information.

## Warning!

* Currently, is not fully portable. It is not guaranteed to work in systems other than GNU/Linux.
* Currently, is not optimized for peak performance.

## Installation

### Requirements

Please, make sure you have previously installed the following:

* [GNU Autoconf](https://www.gnu.org/software/autoconf/) (version 2.68 or greater)
* [GNU Automake](https://www.gnu.org/software/automake/) (version 1.11 or greater)

By default, almost all modern desktop operative systems come with C compiler installed, so this should not be a problem.

### Process

##### Downloading

* If you already have [git](http://git-scm.com/):
`git clone https://github.com/marcosdg/darwin.git`

* If you don't have git: download the zip archive [here](https://github.com/marcosdg/darwin)

##### The quick dirty way

1. Open up a terminal and `cd` into the (unzipped) darwin folder
2. `./autogen.sh` to bootstrap darwin
3. `./configure` to generate configuration files
4. `make` to generate the binary image
5. Done

##### A cleaner way

If you do not want to mess the source tree you can create a subfolder where execute the configure script, so all the generated files will be placed there instead:

1. Open up a terminal and `cd` into the (unzipped) folder
2. `./autogen.sh`
3. `mkdir build && cd !$`
4. `../configure`
5. `make`
6. Done

##### The full installation

For a **default** installation just use `make install` instead of `make`. This will use the system root folder (/usr/local). If you do not want to mess it use the custom installation.

For a **custom** installation you can select the target folder  `./configure --prefix=/the/path/to/my/folder` instead of `./configure`.

## Phylosophy

Here are some of the core values that darwin wants to deliver:

* Readability
* Simplicity
* Modularity
* Usability
* Extensibility
* Maintainability

