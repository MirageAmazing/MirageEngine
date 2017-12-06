#!/bin/bash
echo "************************************"
echo MirageEngine build begin on Linux
echo "************************************"

str="Build"

if [ ! -e $str ]
then
mkdir $str
fi
cd $str

cmake ../Src

echo "************************************"
echo MirageEngine build over on Linux
echo "************************************"
exit 0
