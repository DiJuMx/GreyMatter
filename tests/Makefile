## Settings here
CFLAGS := -std=c99
CFLAGS += -Wall -Wextra -Werror -Wpedantic

LDFLAGS:= -L../lib -lGM
INC := -I../include

SRC_DIR := src
BLD_DIR := build

TESTS := NEAT
EXES := $(TESTS:%=$(BLD_DIR)/%)

## Targets below
.PHONY: all
.PHONY: Makefile

all: $(EXES)

$(BLD_DIR):
	@mkdir -p $@

$(BLD_DIR)/%: main.c $(SRC_DIR)/%.c | ../lib/libGM.so $(BLD_DIR)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

../lib/libGM.so:
	@make -C .. lib/libGM.so

clean:
	@rm -f $(EXES)
