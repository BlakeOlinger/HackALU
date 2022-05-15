# Hack Computing Platform ALU
An ALU implementing the specification of the Hack Computing Platform.[1]

## Table of contents
* [API](#api)
* [Specification](#specification)
* [Technologies](#technologies)
* [Setup](#setup)
* [Sources](#sources)

### API
```c
void alu_compute(uint16_t x,
                 uint16_t y,
                 bool zx,
                 bool nx,
                 bool ny,
                 bool f,
                 bool no,
                 uint16_t *out,
                 bool *zr,
                 bool *ng
                );
```

### Specification
See [1] for more information:

* Notes:
...Overflow is not detected or handled.
...Overflow behaves as expected for a 16 bit unsigned integer.

###### Inputs
...x	:	16 bit unsigned int
...y	:	16 bit unsigned int
...zx	:	zero x input flag
...nx	:	negate (bitwise) x input flag
...zy	:	zero y input flag
...ny	:	negate (bitwise) y input flag
...f	:	set for addition, else bitwise AND
...no	:	negate (bitwise) output flag
###### Outputs
...out	:	16 bit unsigned int
...zr	:	zero flag, set iff out == 0
...ng	:	negative flag, set iff out < 0

### Technologies
* C
* Clang
* Make
* Bash

### Setup
* Build lib
...make build-lib

* Build Tests
...make build-tests

* Run Tests
...make run-tests

### Sources
1. Nisan, N., & Schocken, S. (2005). *The Elements of Computing Systems:
    Building a Modern Computer from First Principles.* The MIT Press.
