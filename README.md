darwin
======

(development)

This academic project aims to offer a comparative view, regarding performance, between two implementations of a simple [Genetic Algorithm](http://www.scholarpedia.org/article/Genetic_algorithms): one using a self-[adaptative](https://en.wikipedia.org/wiki/Genetic_algorithm#Adaptive_GAs) strategy and one which does not.

Given the complexity of the role that play [Evolution Strategies](https://en.wikipedia.org/wiki/Evolution_strategy), as one of the subcategories of [Meta-heuristics](http://www.scholarpedia.org/article/Metaheuristic_Optimization), in Genetic Algorithms, the study here presented focuses on answering the following question:

    how significant is the gain in performance that a Genetic Algorithm can achieve just by
    considering an adaptative mutation operator?

To that end, darwin provides [several instances](https://github.com/marcosdg/darwin/tree/master/data) of well known [NP-problems](http://mathworld.wolfram.com/NP-Problem.html) on which it can be run to evaluate performance.

Please, see the [wiki](https://github.com/marcosdg/darwin/wiki) for more information.

## Disclaimer

* Currently, darwin is not fully portable. It is not guaranteed to work in systems other than GNU/Linux.
* Currently, darwin is not optimized for peak performance regarding both memory consumption and computing time.

## Requirements

Please, make sure you have installed the following:

* [GNU Autoconf](https://www.gnu.org/software/autoconf/) (version 2.68 or greater)
* [GNU Automake](https://www.gnu.org/software/automake/) (version 1.11 or greater)

By default, almost all modern desktop operative systems come with a **C compiler** installed, so this should not be a problem. Additionally, it might help to have installed [Perl](http://www.perl.org/), as darwin comes with various perl scripts (see [data](https://github.com/marcosdg/darwin/tree/master/data)) to help you make your custom problem tests.

## Quick and easy

After downloading darwin (.zip) or cloning it (`git clone https://github.com/marcosdg/darwin.git`):

1. Open up a terminal and `cd` into the (unzipped) darwin directory
2. `./autogen.sh` to bootstrap darwin
3. `./configure` to generate configuration files
4. `make` to generate the binary image
5. Done

**Tip**: Just after `./autogen.sh` do `mkdir build && cd !$` followed by `../configure`, then `make`. This will build darwin in the subdirectory called *build*, avoiding messing up the darwin's source tree.

## Installation

#### Darwin build options

Darwin allows you to choose among several options during the building process:

* `./configure` script options:
    1. `--enable-darwin-debug-mode`
* `make` options:
    1. `DARWIN_FLAGS="-DDARWIN_USE_HAMPATH"`
    2. `DARWIN_FLAGS="-DDARWIN_USE_NQUEENS"`
    3. `DARWIN_FLAGS="-DDARWIN_USE_SUBSETSUM"`

#### The default install

* __Install directory__: root (/usr/local)
* __Debug mode__: disabled
* __Problem set__: Subset-sum

Inside the (unzipped) darwin directory:

1. `./autogen.sh`
2. `./configure`
3. `make install`
4. Done

#### A custom install

* __Install directory__: /home/alice/Desktop/test
* __Debug mode__: enabled
* __Problem set__: Hamiltonian Path (undirected version)

Inside the (unzipped) darwin directory:

1. `./autogen.sh`
2. `./configure --enable-darwin-debud-mode --prefix=/home/alice/Desktop/test`
3. `make DARWIN_FLAGS="-DDARWIN_USE_HAMPATH" install`
4. Done

## Phylosophy

Here are some of the core values upon which darwin is built:

* Readability
* Simplicity
* Modularity
* Usability
* Extensibility
* Maintainability

Have fun :smile:
