###############################################################################
#
# XDK Profile Makefile: profile.mk config file
#
# The profile.mk file is used to configure the outside XDK profile make 
# infrastructure to search for header files provided by the XDK that are 
# required by the auto-generated profile code
#
# This file also is used to derive the library name either baseed on a config
# or taken directly from the name of the directory
#
# Copyright (C) Cavium Inc 2018
#
###############################################################################


###############################################################################
#
# Path to XDK. Can be changed either via command line or using an environment
# variable. Can also be updated here and checked in.
#
# export XDK_PATH=path to xdk
#
# or
#
# make XDK_PATH=path to xdk profile
#
###############################################################################
XDK_PATH := xdk

###############################################################################
#
# Device type variable. Can be changed either via command line or using an
# environment variable. Can also be updated here and checked in
#
# export XP_DEV=XP80 or export XP_DEV=XP100
# 
# or
# 
# make XP_DEV=XP70 
#
# Default is XP100
#
###############################################################################
XP_DEV := XP100


###############################################################################
#
# Path to dump libaries, default ./dist
#
# Can be changed either via command line or using an environment variable.
# Can also be updated here and checked in
#
# export XP_LIB_PATH=/usr/local/lib64
#
# or make XP_LIB_PATH=/usr/local/lib64
#
###############################################################################
XP_LIB_PATH := ./dist

###############################################################################
#
# Library prefix variable, default libXdk_$(XP_DEV)_
#
# Can be changed either via command line or using an environment variable.
# Can also be updated here and checked in
#
# export XP_PRFX=libFooBar
# 
# or make XP_PRFX=libFooBar
#
# NOTE: If XP_LIBNAME is defined and nonempty, the XP_LIBNAME will be used as
# 		the name of the library, and the prefix will be ignored
#
###############################################################################
XP_PRFX := libXdk_$(XP_DEV)_

###############################################################################
#
# Library name, default defined with an empty value
#
# Can be changed either via command line or using an environment variable.
# Can also be updated here and checked in
#
# export XP_LIBNAME=libXp80DefaultProfile
#
# or make XP_LIBNAME=libXp70RouteCentricProfile
#
# NOTE: If XP_LIBNAME is undefined, the library name will be constructed using
# 		the XP_PRFX and the name of the current directory
#
# 		ex: [bash-4.2]# pwd
# 			/home/eng/xp-profiles/default/
# 			[bash-4.2]# echo $XP_DEV
# 			XP80
#
# 			The 'default' will be scraped and used in the library name
# 			generation. The libraries will be called:
#
# 			libXdk_XP80_Default.so and libXdk_XP80_Default.a
#
###############################################################################
XP_LIBNAME :=

###############################################################################
#
# Include path variables (do not change; these are relative paths)
#
###############################################################################

XDK_INC_PATHS := \
	-iquote $(XDK_PATH)/pipeline-profiles/common/include \
	-iquote $(XDK_PATH)/pipeline-profiles/common/profile/include \
	-iquote $(XDK_PATH)/utils/xp/include \
	-iquote $(XDK_PATH)/device/sdksrc/xp/dm/devices/include \
	-iquote $(XDK_PATH)/device/sdksrc/xp/dm/devices/common/config/include \




