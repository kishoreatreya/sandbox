#!/bin/bash

g++ -c XpBitVector.cpp -o XpBitVector.o
g++ -c dfs.cpp -o dfs.o
g++ XpBitVector.o dfs.o -o dfs

