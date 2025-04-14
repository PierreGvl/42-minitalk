#!/bin/bash

for ((i=0; i<100; i++)); do
    ../client $1 "Test loop"
done