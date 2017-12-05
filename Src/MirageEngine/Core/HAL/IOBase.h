#pragma once

#include <future>
#include <functional>
#include <stdio.h>
using namespace std;

typedef unsigned int FileUid;
typedef function<void(void*, size_t)> FileIOLoadCallBack;
typedef function<void(bool)> FileIOSaveCallBack;

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
	void LoadFileAsync(const char* filePath, void* pBuff, size_t buffSize, size_t& dataSize, FileIOLoadCallBack callback = nullptr)
	{
		std::async(std::launch::async, [=, &dataSize](){
			size_t size = 0;
			void* buff = nullptr;

			if (LoadFile(filePath, pBuff, buffSize, dataSize))
			{
				buff = pBuff;
				size = dataSize;
			}
			if (callback != nullptr)
				callback(nullptr, size);
		});
	}
	void LoadFileAsync(char* filePath, void* pBuff, size_t buffSize, FileIOLoadCallBack callback)
	{
		std::async(std::launch::async, [=]() {
			size_t dataSize = 0;
			void* buff = nullptr;

			if (LoadFile(filePath, pBuff, buffSize, dataSize))
				buff = pBuff;
			if (callback != nullptr)
				callback(nullptr, dataSize);
		});
	}
	bool LoadFile(const char* filePath, void* pBuff, size_t buffSize, size_t& dataSize)
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
	void SaveFileAsync(const char* filePath, void* pBuff, size_t buffSize, FileIOSaveCallBack callback = nullptr)
	{
		std::async(std::launch::async, [=]() {
			bool r = SaveFile(filePath, pBuff, buffSize);

			if (callback != nullptr)
				callback(r);
		});
	}
	bool SaveFile(const char* filePath, void* pBuff, size_t buffSize)
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