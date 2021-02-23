#!/bin/sh

echo "The check_file script $0 is now running"
x=0

# source file

for source_file in $( ls ./code); do
 
    if [ -e code ];
    then
        echo " $source_file exist "
    else
        echo " $source_file does not exist "
    fi
done

# source file

# common_file

#for common_file in $( ls ../Source/Lab-04/Code/common);do
 	
   #if [ -e Code/common ];
   #then 
   #    echo " $common_file directory exist "
   #else   
   #    echo "$common_file directory not exist"
   #fi
#done

#echo "The script is now complete"

exit 0



