###############################################################################
#
# XDK Profile Makefile
#
# This Makefile is used to compile profile specific code outside the XDK
# Main directory structure
#
# This Makefile will create the following:
# 	- libProfile.so
# 	- libProfile.a
#
# Where the "Profile" name can either come from the name of the directory
# or from a profile.mk file located in this directory
# 
# Profile sources include the following:
# 	- Pipeline Builders
# 	- Pipeline Entry classes
# 	- Pipeline Packer classes
#
# This libProfile will be dependent on the xdk library (or granular libs)
# so in the final binary link order ensure that libXdk (or granular libs)
# is linked after the libProfile for the linker to resolve the symbols
# correctly
#
# Copyright (C) Cavium Inc 2018
#
###############################################################################

###############################################################################
#
# This section lists all of the variables used in the Make
#
###############################################################################

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	CXXFLAGS := -g -MMD -MP -Wall -Werror -std=c++11
	CXX := g++
	LD := g++
else
	CXXFLAGS := -g -MMD -MP -Wall -Werror -std=c++11
	CXX := g++
	LD := g++
endif

SHELL := /bin/bash
RM  := rm
ECHO := echo
LDFLAGS :=
MAKE := make
MKDIR := mkdir
SRCDIR := src
DIST := dist
OBJSDIR := objs

###############################################################################
#
# Include the profile specific configurations
#
###############################################################################
-include profile.mk

###############################################################################
# 
# This section includes the sources files and includes files
#
###############################################################################
-include srcs.mk
-include includes.mk

###############################################################################
#
# Canned recipes used as functions
#
###############################################################################
ifeq ($(UNAME),Darwin)
define PROFILE_MAKE_SHARED_LIB =
	$(CXX) -fPIC $(filter %.o, %^) ${LDFLAGS} -shared -o $@
endef
else
define PROFILE_MAKE_SHARED_LIB =
	$(CXX) -fPIC -rdynamic $(filter %.o, %^) ${LDFLAGS} -shared -o $@
endef
endif
define PROFILE_MAKE_STATIC_LIB =
	$(RM) -f $@
	$(AR) $(ARFLAGS) $@ $(filter %.0, $^)
endef

###############################################################################
#
# Library name generation
#
###############################################################################

define upper_first 
	$(shell ./to_upper.sh $(1))
endef

ifneq ($(XP_LIBNAME),)
XP_LIB := $(DIST)/$(addprefix $(XP_PRFX),$(XP_LIBNAME))
else
XP_LIB_TMP := $(strip $(call upper_first, $(notdir $(shell pwd))))
XP_LIB := $(DIST)/$(addprefix $(XP_PRFX),$(XP_LIB_TMP))
endif

###############################################################################
# 
# Objects Variable
#
###############################################################################
OBJS := $(foreach src, $(SRCS),$(OBJSDIR)/$(basename $(src)).o) 

###############################################################################
#
# Dependencies Variable
#
###############################################################################
DEPS := $(OBJS:.o=.d)

###############################################################################
#
# Targets
#
###############################################################################

.PHONY : all
all : lib install

.PHONY : install
install :
	@$(ECHO)
	@$(ECHO) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	@$(ECHO)
	@$(ECHO) Installing $(XP_LIB) at `readlink -f $(XP_LIB_PATH)`
	@$(ECHO)
	@$(ECHO) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	$(shell \
	if [ `readlink -f "$(DIST)"` != `readlink -f "$(XP_LIB_PATH)"` ]; then\
		cp $(DIST)/* $(XP_LIB_PATH); \
	fi\
	)

.PHONY : lib
lib : lib_shared lib_static

.PHONY : lib_shared
lib_shared : $(XP_LIB).so

.PHONY : lib_static
lib_static : $(XP_LIB).a

$(DIST) : 
	@$(MKDIR) -p $(DIST)

$(OBJSDIR) : 
	@$(MKDIR) -p $(OBJSDIR)

$(XP_LIB).so : $(OBJS) $(DIST)
	@$(ECHO)
	@$(ECHO) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	@$(ECHO) 
	@$(ECHO) Building $(XP_LIB).so
	@$(ECHO)
	@$(ECHO) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	$(CXX) -fPIC $(filter %.o, $^) ${LDFLAGS} -shared -o $@

$(XP_LIB).a : $(OBJS) $(DIST)
	@$(ECHO)
	@$(ECHO) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	@$(ECHO) 
	@$(ECHO) Building $(XP_LIB).a
	@$(ECHO)
	@$(ECHO) ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	@$(RM) -f $@
	$(AR) $(ARFLAGS) $@ $(filter %.o, $^)

.PRECIOUS : $(OBJSDIR)/*.o
$(OBJSDIR)/%.o : %.cpp $(OBJSDIR) $(MAKEFILE_LIST) 
	@$(MKDIR) -p $(dir $@)
	$(CXX) $(XDK_INC_PATHS) $(PROFILE_INCLUDES) $(CXXFLAGS) -c $< \
	-o $@

.PHONY : clean
clean : 
	$(RM) -f src/*.o src/*.d 
	$(RM) -rf src/*.dSYM
	$(RM) -rf objs
	$(RM) -rf dist

# Include dependcies
-include $(DEPS)

