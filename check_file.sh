#!/bin/sh

echo "The check_file script $0 is now running"
x=0

# source file

for source_file in $( ls ./src); do
    echo "checking $source_file ..."
    diff ./src/$source_file ./code/$soure_file
done
exit 0



