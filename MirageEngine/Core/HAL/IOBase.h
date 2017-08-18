#pragma once

#include <future>
#include <stdio.h>
using namespace std;

typedef unsigned int FileUid;

struct FileInfo
{

};

class FileIOSystem
{
public:
	static FileIOSystem& Get()
	{
		return Instance;
	}
private:
	FileIOSystem() {}
	~FileIOSystem() {}
	static FileIOSystem Instance;

public:
	void LoadFileAsync(char* name) 
	{
		std::async(std::launch::async, [](){
			
		});
	}
	bool LoadFile(char* filePath, void* pBuff, size_t buffSize, size_t& dataSize)
	{
		FILE* pFile = nullptr;
		pFile = fopen(filePath, "r");
		if (pFile != nullptr)
		{
			fseek(pFile, 0, SEEK_END);
			dataSize = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);

			if (buffSize >= dataSize)
			{
				fread(pBuff, 1, dataSize, pFile);
			}

			fclose(pFile);
		}
		
		return pFile != nullptr;
	}
	bool SaveFile(char* filePath, void* pBuff, size_t buffSize)
	{
		FILE* pFile = nullptr;
		pFile = fopen(filePath, "w");
		if (pFile != nullptr)
		{
			fwrite(pBuff, 1, buffSize, pFile);
			fclose(pFile);
		}
		
		return pFile != nullptr;
	}
};

FileIOSystem FileIOSystem::Instance;