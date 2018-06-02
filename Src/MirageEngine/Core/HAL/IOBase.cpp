#include "IOBase.h"


FileIOSystem FileIOSystem::Instance;

void FileIOSystem::LoadFileAsync(const char* filePath, void* pBuff, size_t buffSize, size_t& dataSize, FileIOLoadCallBack callback)
{
	std::async(std::launch::async, [=, &dataSize]() {
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
void FileIOSystem::LoadFileAsync(char* filePath, void* pBuff, size_t buffSize, FileIOLoadCallBack callback)
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
bool FileIOSystem::LoadFile(const char* filePath, void* pBuff, size_t buffSize, size_t& dataSize)
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
void FileIOSystem::SaveFileAsync(const char* filePath, void* pBuff, size_t buffSize, FileIOSaveCallBack callback)
{
	std::async(std::launch::async, [=]() {
		bool r = SaveFile(filePath, pBuff, buffSize);

		if (callback != nullptr)
			callback(r);
	});
}
bool FileIOSystem::SaveFile(const char* filePath, void* pBuff, size_t buffSize)
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