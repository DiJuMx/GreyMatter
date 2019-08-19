# Clear and reset suffix list
.SUFFIXES:		#Clear
#.SUFFIXES: .c .o	#Reset

all: 	targets

# Subdirectories
dir := lib
include $(dir)/Rules.mk
dir := src
include $(dir)/Rules.mk
dir := test
include $(dir)/Rules.mk

# Directory independent rules
%.o:	%.c
	$(COMP)

%:	%.o
	$(LINK)

%:	%.c
	$(COMPLINK)

# Makefile fragments are free to define the
# TGT_*, CLEAN, and CMD_INST* variables

.PHONY:		targets
targets:	$(TGT_BIN) $(TGT_SBIN) $(TGT_ETC) $(TGT_LIB)

.PHONY:		tests
tests:		$(TGT_TEST)

.PHONY:		clean
clean:
		rm -f $(CLEAN)

.PHONY:		install
install:	targets 
		$(INST) $(TGT_BIN) -m 755 -d $(DIR_BIN)
		$(CMD_INSTBIN)
		$(INST) $(TGT_SBIN) -m 750 -d $(DIR_SBIN)
		$(CMD_INSTSBIN)
ifeq ($(wildcard $(DIR_ETC)/*),)
		$(INST) $(TGT_ETC) -m 644 -d $(DIR_ETC)
		$(CMD_INSTETC)
else
		@echo Configuration directory $(DIR_ETC) already present -- skipping
endif
		$(INST) $(TGT_LIB) -m 750 -d $(DIR_LIB)
		$(CMD_INSTLIB)


# Prevent make from removing any build targets, including intermediate ones

.SECONDARY:	$(CLEAN)
