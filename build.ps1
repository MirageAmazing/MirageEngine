Write-Host '****************************************'
Write-Host 'Mirage build begin'
Write-Host '****************************************'

Set-Location ../

if( -not (Test-Path Mirage_Build_Windows) )
{
    Write-Host 'This dictionary not here!'
    New-Item ./Mirage_Build_Windows -ItemType Directory
}
Set-Location ./Mirage_Build_Windows

cmake -G "Visual Studio 15 2017 Win64" ../MirageEngine/Src
#cmake -G "Visual Studio 14 2015 Win64" ../MirageEngine/Src

Write-Host '****************************************'
Write-Host 'Mirage build over'
Write-Host '****************************************'

Set-Location ../MirageEngine
