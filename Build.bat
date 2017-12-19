@echo off  
echo ****************************************  
echo MirageEngine build begin  
echo ****************************************  

cd ../

if not exist ME_Build_Windows md ME_Build_Windows
rd /s /Q ME_Build_Windows
md ME_Build_Windows
cd ME_Build_Windows

cmake -G "Visual Studio 15 Win64" ../MirageEngine/Src

echo ****************************************  
echo MirageEngine build over  
echo ****************************************  
pause  