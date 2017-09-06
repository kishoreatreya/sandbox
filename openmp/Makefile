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
	CXXFLAGS := -iquote inc -g -MMD -MP -Wall -Werror -x c++ -fopenmp
	CXX := g++-4.8
	LD := g++-4.8
else
	CXXFLAGS := -iquote inc -g -MMD -MP -Wall -Werror -fopenmp
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
BIN := dist/mp

###############################################################################
# 
# This section lists all of the sources to be compiled 
#
###############################################################################
SRCS := \
	$(SRCDIR)/mp.c

# Objects Variable
OBJS := $(SRCS:.cpp=.o)
OBJS := $(SRCS:.c=.o)

# Dependencies Variable
DEPS := $(OBJS:.o=.d)

###############################################################################
#
# Targets
#
###############################################################################

.PHONY : all
all : $(BIN) cscope

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

.PHONY : cscope
cscope :
	source ../../csfiles.sh

.PHONY : cscope_clean
cscope_clean :
	$(RM) -f cscope.*

# Include dependcies
-include $(DEPS)

