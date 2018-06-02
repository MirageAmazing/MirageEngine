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
	void LoadFileAsync(const char* filePath, void* pBuff, size_t buffSize, size_t& dataSize, FileIOLoadCallBack callback = nullptr);
	void LoadFileAsync(char* filePath, void* pBuff, size_t buffSize, FileIOLoadCallBack callback);
	bool LoadFile(const char* filePath, void* pBuff, size_t buffSize, size_t& dataSize);
	void SaveFileAsync(const char* filePath, void* pBuff, size_t buffSize, FileIOSaveCallBack callback = nullptr);
	bool SaveFile(const char* filePath, void* pBuff, size_t buffSize);
};