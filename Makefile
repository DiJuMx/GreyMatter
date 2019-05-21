## Settings here
CFLAGS := -fPIC
CFLAGS += -MMD
CFLAGS += -std=c99
CFLAGS += -Wall -Wextra -Werror -Wpedantic

# To be removed for release builds
CFLAGS += -g

LDFLAGS:=

INC_DIR := include
SRC_DIR := src
BLD_DIR := build
BIN_DIR := bin
DOC_DIR := docs

INC := $(addprefix -I,$(INC_DIR))
LIB_SRCS := unit.c summation.c NEAT.c
TST_SRCS := test.c

ALL_SRCS := $(LIB_SRCS) $(TST_SRCS)

LIB_OBJS := $(LIB_SRCS:%.c=$(BLD_DIR)/%.o)
TST_OBJS := $(TST_SRCS:%.c=$(BLD_DIR)/%.o)

ALL_OBJS := $(ALL_SRCS:%.c=$(BLD_DIR)/%.o)

DEPS := $(ALL_OBJS:.o=.d)

DOXYGEN:= $(shell command -v doxygen 2> /dev/null)

## Targets below
.PHONY: all cleanall
.PHONY: clean cleandep
.PHONY: docs cleandoc
.PHONY: tests cleantest
.PHONY: help
.PHONY: Makefile

all: lib/libGM.so

lib/libGM.so: $(LIB_OBJS) $(LIB_DIR)
	@$(CC) $(CFLAGS) -shared -o $@ $^ $(LDFLAGS)

-include $(DEPS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c $(BLD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

cleanall: clean cleandep cleandoc

clean:
	rm -f $(ALL_OBJS) lib/libGM.so bin/test
cleandep:
	rm -f $(DEPS)


$(BIN_DIR) $(LIB_DIR) $(BLD_DIR):
	@mkdir -p $@

docs:
ifndef DOXYGEN
	$(error "Doxygen not installed. Not generating documentation")
else
	doxygen
endif
cleandoc:
	rm -rf $(DOC_DIR)
	
tests: bin/test
	@echo "Running Tests..."
	@LD_LIBRARY_PATH=lib ./bin/test
debug: bin/test
	@LD_LIBRARY_PATH=lib gdb ./bin/test
bin/test: lib/libGM.so $(TST_OBJS) $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $@ $(TST_OBJS) -Llib -lGM -lm

help:
	@echo "Available targets are:"
	@echo "\tall\t- Builds this project and tests"
	@echo "\tclean\t- Removes build objects and lib"
	@echo "\tcleandep\t- Removes dependency artifacts"
	@echo "\tdocs\t- Build documentation"
	@echo "\tcleandoc\t- Removes documentation"
	@echo "\ttests\t- Builds and runs the test suite"
	@echo "\tcleantest\t- Removes test suite artifacts"
