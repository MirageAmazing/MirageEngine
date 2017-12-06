#!/bin/sh
echo ****************************************  
echo MirageEngine build begin  
echo ****************************************  

buildPath = "Build"

if [ ! -d "${buildPath}" ]; then
mkdir "${buildPath}"
fi
cd "${buildPath}"
cmake ../Src

echo ****************************************  
echo MirageEngine build over  
echo ****************************************  
pause  