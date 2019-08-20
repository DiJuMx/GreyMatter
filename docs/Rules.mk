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

ifeq ($(DOXYGEN),)
docs:
	@echo Doxygen is not available. Not generating Documentation
else
# Local Variables

# Choose, targets vs objects.

TGTS_$(d)	:= 
DEPS_$(d)	:= 

TGT_DOCS	:= $(TGT_DOCS) $(TGTS_$(d))
	# Run tests?

CLEAN		:= $(CLEAN) $(TGTS_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# Local Rules

# Include auto generated dependencies
-include 	$(DEPS_$(d))

endif

# Pop stack
d	:= $(dirstack_$(sp))
sp 	:= $(basename $(sp))
