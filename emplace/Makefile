###############################################################################
#
# Generic Makefile, vary the variables and move this around the filesystem 
#
###############################################################################

###############################################################################
#
# This section lists all of the variables used in the Make
#
###############################################################################

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	CXXFLAGS := -iquote inc -g -MMD -MP -Wall -Werror -std=c++11
	CXX := g++
	LD := g++
else
	CXXFLAGS := -iquote inc -g -MMD -MP -Wall -Werror -std=c++11
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

# Name of the Binary
BIN := dist/emplace

###############################################################################
# 
# This section lists all of the sources to be compiled 
#
###############################################################################
SRCS := \
	$(SRCDIR)/emplace.cpp

# Objects Variable
OBJS := $(addsuffix .o,$(basename $(SRCS)))

$(warning $(OBJS))

# Dependencies Variable
DEPS := $(OBJS:.o=.d)

###############################################################################
#
# Targets
#
###############################################################################

.PHONY : all
all : $(BIN) 

$(BIN) : $(OBJS)
	$(MKDIR) -p dist
	$(LD) -o $@ $(OBJS) $(LDFLAGS)
	@$(ECHO)
	@$(ECHO) "$@ has been built"
	@$(ECHO)

%.o : %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY : clean
clean : 
	$(RM) -f src/*.o src/*.d $(BIN) 
	$(RM) -rf src/*.dSYM
	$(RM) -rf dist

.PHONY : cscope
cscope :
	source ../../csfiles.sh

.PHONY : cscope_clean
cscope_clean :
	$(RM) -f cscope.*

# Include dependcies
-include $(DEPS)

