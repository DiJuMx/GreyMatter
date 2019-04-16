.PHONY: all clean tests docs help

all: lib/libGM.so

clean:

docs:
ifndef DOXYGEN
	$(error "Doxygen not installed. Not generating documentation")
else
	doxygen
endif
	
tests:
	@echo "${TEST}"

help:
	@echo "Available targets are:"
	@echo "\tall\t- Builds this project and tests"
	@echo "\tclean\t- Removes all build artifacts"
	@echo "\tdocs\t- Build documentation"
	@echo "\ttests\t- Builds and runs the test suite"

## Main targets should exist below here
lib:
	@mkdir lib
lib/libGM.so: | lib

## General settings and flags here
CFLAGS=

LDFLAGS=

DOXYGEN:= $(shell command -v doxygen 2> /dev/null)

TEST:="Goodbye"

TEST="HI THERE"

TEST+="HELLO"
