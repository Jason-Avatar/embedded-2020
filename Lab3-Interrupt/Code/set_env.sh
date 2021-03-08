#!/bin/sh

echo "The set_env script $0 is now running"

# if Code exists , echo the Code exists  
if [ -e ./code ]
then 
  echo "lab exists"
# if code folder of lab04 does not exists , make the code folder of lab-04
else
  cp -rf ./.src ./code
  echo "lab builded !"
  chmod 664 ./code/*
fi

#export PATH=/usr/src/opt/microtime/pro/devkit/arm/pxa270/gcc-4.0.2-glibc-2.3.3/arm-unknown-linux-gnu/bin:$PATH
#echo "PATH is done !"

echo "The script is now complete"

