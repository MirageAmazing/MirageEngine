buildPath = "Build"

if [ ! -d "$buildPath"];then
    mkdir "$buildPath"
fi
cd "$buildPath"
cmake ../Src