# XDK Profile Library Compilation

This directory provides a template directory structure that can be used to build a library of all profile code living outside of the XDK hierarchy

## Getting Started

###Included files:

* Makefile
* profile.mk
* srcs.mk
* includes.mk
* to\_upper.sh
* README.md

###Directory Structure:

* src
    * entries
        * include
    * packers
        * include
    * profiles
        * lde
            * include
        * parser
            * include
        * hdr
            * include
        * table
            * include
        * range
            * include
        * acm
            * include
    * pipeline-builders
            * include
    
After using the code generators provided as a part of the xdk
    - XPC 12.x or newer
    - FAL-PL plGenMaster
    - Parser Profile Generator
    
Take the generated code and place them into the appropriate location in the directory hierarchy and update the _srcs.mk_ file to compile in the cpps

Once the _srcs.mk_ file has been updated, ensure that the _includes.mk_ file lists the correct include directory paths


### Building

To build the .so and .a libraries:

```
make
```

To install the .so and .a libraries:

```
make install
```

### Build Configuration

The _profile.mk_ file that has been provided as a part of the directory structure contains make variables that can be set to configure the build options or install options

By default the **XDK\_PATH** variable has been set to 'xdk'. This will need to be set to the correct path to the 'xdk' release. This variable is used later to set up required 'xdk' include paths

Other variables include:

* **XP\_DEV**
    - Variable used to set the device type that this profile is built for, default XP100
    
* **XP\_LIB\_PATH**
    - Variable used to set the install location for the built profile libraries
    
* **XP\_PRFX**
    - Variable used to configure the libname prefix. Default is libXdk$(XP\_DEV)
        ex: libXdk\<libname\>
    
* **XP\_LIBNAME**
    - Variable used to explicitly set the full library name for this profile
    
**NOTE: If the XP\_LIBNAME variable is empty, the library name will be constructed using the current working directory dirname**
**ex: If the current working directory dirname is 'default' and the XP\_PRFX is libXdk$(XP\_DEV), the name of the library generated will be libXdkXp100Default.so/.a**

Additionally, there is a variable **XDK\_INC\_PATHS** which is prefilled with include paths for header files defined within the 'xdk' hierarchy that are required for compilation of the profile library. Please do not modify this variable unless explicitly asked

### Command Line Build Configurations

Any of the variables defined in _profile.mk_ can be defined at the command line when invoking 'make'

EX: This will set the device type to Xp80 and the install location to /usr/local/lib64

```
make XP_DEV=Xp80 XP_LIB_PATH=/usr/local/lib64
make install
```

EX: This will set the libname to libXdkFoobar

```
make XP_LIBNAME=libXdkFoobar
make install
```

You can use any combination of the _profile.mk_ variables on the command line if you choose

## Copyright

Copyright Cavium Inc (C) 2018
