#!/bin/bash


name=$(basename $1 .py)

astexport < "$1" > "${name}AST.json"