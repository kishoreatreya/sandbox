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

Once the srcs.mk file has been updated, ensure that the _includes.mk_ file lists the correct include directory paths




### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Deployment

Add additional notes about how to deploy this on a live system

## Copyright

Copyright Cavium Inc (C) 2018