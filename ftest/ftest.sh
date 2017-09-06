#!/bin/bash

if [ ! -e $1 -o "$(head -n 1 $1)" != "$($1)" ]; then
    echo "FOO NOT FOUND"
else
    echo "FOO FOUND"
fi




