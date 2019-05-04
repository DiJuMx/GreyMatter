## Settings here
CFLAGS := -fPIC
CFLAGS += -MMD
CFLAGS += -std=c99
CFLAGS += -Wall -Werror -Wpedantic

LDFLAGS:=

INC_DIR := include
SRC_DIR := src
BLD_DIR := build
DOC_DIR := docs

INC := $(addprefix -I,$(INC_DIR))
SRCS := NEAT.c
SRCS := $(addprefix src/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BLD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

DOXYGEN:= $(shell command -v doxygen 2> /dev/null)

## Targets below
.PHONY: all cleanall
.PHONY: clean cleandep
.PHONY: docs cleandoc
.PHONY: tests cleantest
.PHONY: help
.PHONY: Makefile

all: lib/libGM.so

lib/libGM.so: $(OBJS) | lib_dir
	@$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS)

-include $(DEPS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | bld_dir
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

cleanall: clean cleandep cleandoc

clean:
	rm -f $(OBJS) lib/libGM.so
cleandep:
	rm -f $(DEPS)

bld_dir:
	@mkdir -p $(BLD_DIR)
lib_dir:
	@mkdir -p lib

docs:
ifndef DOXYGEN
	$(error "Doxygen not installed. Not generating documentation")
else
	doxygen
endif
cleandoc:
	rm -rf $(DOC_DIR)
	
tests:
	@echo "${TEST}"

help:
	@echo "Available targets are:"
	@echo "\tall\t- Builds this project and tests"
	@echo "\tclean\t- Removes build objects and lib"
	@echo "\tcleandep\t- Removes dependency artifacts"
	@echo "\tdocs\t- Build documentation"
	@echo "\tcleandoc\t- Removes documentation"
	@echo "\ttests\t- Builds and runs the test suite"
	@echo "\tcleantest\t- Removes test suite artifacts"
