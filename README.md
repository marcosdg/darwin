darwin
======

(development)

This academic project aims to offer a comparative view, regarding performance, between two implementations of a simple Genetic Algorithm: one using a self-[adaptative](https://en.wikipedia.org/wiki/Genetic_algorithm#Adaptive_GAs) strategy
and one which does not. 

Given the complexity of the role that play [Evolution Strategies](https://en.wikipedia.org/wiki/Evolution_strategy), as one of the subcategories of [Meta-heuristics](http://www.scholarpedia.org/article/Metaheuristic_Optimization), in Genetic Algorithms, the study here presented focuses on answering the following question: 

    how significant is the gain in performance that a Genetic Algorithm can achieve just by
    considering an adaptative mutation operator?

## Warning!

* Currently, is not not fully portable. It is not guaranteed to work in other systems than GNU/Linux, namely Windows or Mac OS.
* Currently, is not optimized for peak performance.

## Installation

### Requirements

Please, make sure you have previously installed the following:

* [GNU Autoconf](https://www.gnu.org/software/autoconf/) (version 2.68 or greater)
* [GNU Automake](https://www.gnu.org/software/automake/) (version 1.11 or greater)

By default, almost all general purpose operative systems come with C compiler installed, so this should not be a problem.

### Process

You either can `git clone` (if you have [git](http://git-scm.com/))  the repo or download the zip archive here. Afterwards, you have various options:

##### Giving it a try

1. Extract the zip archive, in case you chose to download it
2. Open up a terminal and `$ cd` into the unzipped folder
3. `$ ./autogen.sh` to bootstrap darwin
4. `$ ./configure` to generate configuration files
5. `$ make` to generate the binary image
6. Done

This will create the executable inside the unzipped folder, so it will not "mess" your system folder hierarchy (`/usr/local/`), although it will "mess" the source tree. If you want to clean the files generated by `make` do`make clean`

##### The full installation

Use `make install` instead of `make`, but this will "mess" the system folder hierarchy. Alternatively, you can select the target folder for installation. Example:
`$ DESTDIR="~/Desktop/my_installation_folder" make install`.

## Phylosophy

Here are some of the core values that darwin wants to deliver:

* Readability
* Simplicity
* Modularity
* Usability
* Extensibility
* Maintainability

