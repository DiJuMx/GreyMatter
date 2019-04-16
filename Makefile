.PHONY: all clean tests docs help

all: lib/libGM.so

clean:

docs:

tests:
	@echo "${TEST}"

help:
	@echo "Available targets are:"
	@echo "\tall\t- Builds this project and tests"
	@echo "\tclean\t- Removes all build artifacts"
	@echo "\tdocs\t- Build documentation"
	@echo "\ttests\t- Builds and runs the test suite"

## Main targets should exist below here
lib/libGM.so:

## General settings and flags here
CFLAGS=

LDFLAGS=

TEST:="Goodbye"

TEST="HI THERE"

TEST+="HELLO"
