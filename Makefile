####################################################
# This Makefile and the various makefile fragements
# are based on the system by Emile van Bergen
# http://sites.e-advies.nl/nonrecursive-make.html
####################################################

# Common build flags for all targets
CF_ALL ?= -Wall -Wextra -Wpedantic
CF_ALL += -MMD -std=c99
CF_ALL += -Iinclude
LF_ALL = 
LL_ALL = 



# Build tools
CC 		?= gcc
INST 		?= install
COMP 		= $(CC) $(CF_ALL) $(CF_TGT) -o $@ -c $<
LINK 		= $(CC) $(LF_ALL) $(LF_TGT) -o $@ $^ $(LL_TGT) $(LL_ALL)
COMPLINK 	= $(CC) $(CF_ALL) $(CF_TGT) $(LF_ALL) $(LF_TGT) -o $@ $< $(LL_TGT) $(LL_ALL)

# Project rules
include Rules.mk
