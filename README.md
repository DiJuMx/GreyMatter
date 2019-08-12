# Grey Matter

Grey Matter is intended to be an extensible neural network library written in C.

It is *not* intended to be:
* Fast
* Memory Efficient
* User Friendly

There are likely many bugs and issues with this fledgling project.
In addition, the API is not guaranteed to be stable.

## Architecture

### (Almost) Everything is a Unit

In GreyMatter, the core concept is that everything is a "Unit".

A Unit is effectively a black box system consisting of:
* An output
* A functional body
* Zero or more inputs

Since a network of Units also has the same properties, a network can also be a Unit.

This means:
* Units are interchangeable.
* Units are composable.
* Units are extensible.

### Framework

The framework of GreyMatter refers to the supporting structure which wraps the Units of the network
into a usable format.

As with any neural network, there are typically two stages:
1. A training stage
2. An execution stage

GreyMatter places a slight emphasis on the execution stage. 
It is possible to build and run a neural network using pre-determined parameters;
training is not a necessity.
