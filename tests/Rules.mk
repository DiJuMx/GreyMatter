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

TGTS_$(d)	:= $(d)/tests
DEPS_$(d)	:= $(OBJS_$(d):%=%.d) $(TGTS_$(d):%=%.d)

# TGT_BIN gets installed! Don't want to install tests
#TGT_BIN		:= $(TGT_BIN) $(TGTS_$(d))
TGT_TEST	:= $(TGT_TEST) $(TGTS_$(d))
	# Run tests?

CLEAN		:= $(CLEAN) $(TGTS_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# Local Rules
$(TGTS_$(d)):	lib/libGM.so
$(TGTS_$(d)):	| $(d)/Rules.mk

#$(TGTS_$(d)):	CF_TGT := -Icommon -DRADDB=\"$(DIR_ETC)\"
#$(TGTS_$(d)):	LL_TGT := $(S_LL_INET) common/common.a
#$(TGTS_$(d)):	$(d)/radclient.c common/common.a
#		$(COMPLINK)

$(d)/tests:	private LL_TGT := -Llib -lGM -lm

$(d)/tests:	$(d)/test.c
		$(COMPLINK)

#$(OBJS_$(d)):	CF_TGT := -I$(d)

# Include auto generated dependencies
-include 	$(DEPS_$(d))

# Pop stack
d	:= $(dirstack_$(sp))
sp 	:= $(basename $(sp))
