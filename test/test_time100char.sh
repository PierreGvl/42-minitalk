#!/bin/bash

MESSAGE=$(printf '%100s' | tr ' ' 'X')

time ../client $1 "$MESSAGE"