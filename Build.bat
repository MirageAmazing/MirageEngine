@echo off  
echo ****************************************  
echo MirageEngine build begin  
echo ****************************************  

if not exist Build md Build
rd /s /Q Build
md Build
cd Build

cmake -G "Visual Studio 15 Win64" ../Src

echo ****************************************  
echo MirageEngine build over  
echo ****************************************  
pause  