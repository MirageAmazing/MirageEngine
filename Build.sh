#!/bin/bash
echo "************************************"
echo MirageEngine build begin on Linux
echo "************************************"

str="ME_Build_Linux"

cd ../

if [ ! -e $str ]
then
mkdir $str
fi
cd $str

cmake ../MirageEngine/Src

echo "************************************"
echo MirageEngine build over on Linux
echo "************************************"
exit 0
