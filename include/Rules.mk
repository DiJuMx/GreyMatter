# Create a stack to enable traversal of
# makefile fragements

sp		:= $(sp).x	# Current stack pointer
dirstack_$(sp)	:= $(d)		# Current stack
d		:= $(dir)	# Current Directory

# List subdirectories

#dir 	:= $(d)/sub
#include $(dir)/Rules.mk

# Local Variables

# Choose, targets vs objects.

#TGTS_$(d)	:= $(d)/client
#OBJS_$(d)	:= $(d)/debug.o
#DEPS_$(d)	:= $(OBJS_$(d):%=%.d) $(TGTS_$(d):%=%.d)

#TGT_BIN		:= $(TGT_BIN) $(TGTS_$(d))
#CLEAN		:= $(CLEAN) $(TGTS_$(d)) $(OBJS_$(d)) $(DEPS_$(d))

# Local Rules
$(TGTS_$(d)):	| $(d)/Rules.mk

#$(TGTS_$(d)):	CF_TGT := -Icommon -DRADDB=\"$(DIR_ETC)\"
#$(TGTS_$(d)):	LL_TGT := $(S_LL_INET) common/common.a
#$(TGTS_$(d)):	$(d)/radclient.c common/common.a
#		$(COMPLINK)


#$(OBJS_$(d)):	CF_TGT := -I$(d)

# Include auto generated dependencies
-include 	$(DEPS_$(d))

# Pop stack
d	:= $(dirstack_$(sp))
sp 	:= $(basename $(sp))
