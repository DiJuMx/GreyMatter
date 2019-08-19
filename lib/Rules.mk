# Create a stack to enable traversal of
# makefile fragements

# Current stack pointer
sp		:= $(sp).x
# Current stack
dirstack_$(sp)	:= $(d)
# Current Directory
d		:= $(dir)

# List subdirectories

#dir 	:= $(d)/sub
#include $(dir)/Rules.mk

# Local Variables

# Choose, targets vs objects.

TGTS_$(d)	:= $(d)/libGM.so
OBJS_$(d)	:= $(d)/unit.o $(d)/summation.o

DEPS_$(d)	:= $(TGTS_$(d):%=%.d) $(OBJS_$(d):%=%.d)

TGT_BIN		:= $(TGT_BIN) $(TGTS_$(d))
CLEAN		:= $(CLEAN) $(TGTS_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# Local Rules
$(TGTS_$(d)):	| $(d)/Rules.mk

$(TGTS_$(d)):	LF_TGT := -shared

$(OBJS_$(d)):	CF_TGT := -fPIC -I$(d)

$(d)/libGM.so:	$(OBJS_$(d))
		$(LINK)

# Include auto generated dependencies
-include 	$(DEPS_$(d))

# Pop stack
d	:= $(dirstack_$(sp))
sp 	:= $(basename $(sp))
