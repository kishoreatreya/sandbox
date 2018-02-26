#!/bin/bash

TMP=$1

TMP=$(tr '[:lower:]' '[:upper:]' <<< ${TMP:0:1})${TMP:1}

echo $TMP
