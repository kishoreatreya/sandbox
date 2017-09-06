#!/bin/bash

UNAME=`uname`

find "$PWD" -path "$PWD/include/boost" -prune -o -name "*.cpp" -exec echo \"{}\" \; > cscope.files
find "$PWD" -path "$PWD/include/boost" -prune -o -name "*.c" -exec echo \"{}\" \; > cscope.files
find "$PWD" -path "$PWD/include/boost" -prune -o -name "*.hpp" -exec echo \"{}\" \; >> cscope.files
find "$PWD" -path "$PWD/include/boost" -prune -o -name "*.h" -exec echo \"{}\" \; >> cscope.files
    
cscope -b -q -k
    
