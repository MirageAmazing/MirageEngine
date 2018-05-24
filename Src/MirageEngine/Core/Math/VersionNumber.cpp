#include "VersionNumber.h"
#include <stdio.h>
#include <memory>
#include <vector>
#include <string>

namespace MirageMath
{
	VersionNumber::VersionNumber(uint8 major, uint8 minor, uint8 revision)
	{
		mVN.mVersionNumber[2] = major;
		mVN.mVersionNumber[1] = minor;
		mVN.mVersionNumber[0] = revision;

		sprintf(mVersionStr, "%d.%d.%d", mVN.mVersionNumber[2], mVN.mVersionNumber[1], mVN.mVersionNumber[0]);
	}
	VersionNumber::VersionNumber(const char* version)
	{
		if (version == nullptr)
			VersionNumber(0, 0, 0);
		else
		{
			if (strlen(version) > 0)
			{
				vector<int> vnList;
				const char split[2]{ "." };
				char newVersionStr[20]{ "" };

				strcpy(newVersionStr, const_cast<char*>(version));

				auto splitResult = strtok(newVersionStr, split);
				while (splitResult != nullptr)
				{
					vnList.push_back(stoi(splitResult));
					splitResult = strtok(nullptr, split);
				}

				auto size = vnList.size();
				mVN.mVersionNumber[2] = size >= 1 ? vnList[0] : 0;
				mVN.mVersionNumber[1] = size >= 2 ? vnList[1] : 0;
				mVN.mVersionNumber[0] = size >= 3 ? vnList[2] : 0;
			}
		}

		sprintf(mVersionStr, "%d.%d.%d", mVN.mVersionNumber[2], mVN.mVersionNumber[1], mVN.mVersionNumber[0]);
	}
	VersionNumber::VersionNumber(VersionNumber& In)
	{
		mVN.mWholeNumber = In.mVN.mWholeNumber;
		strcpy(mVersionStr, In.mVersionStr);
	}

	VersionNumber operator ""_V(const char* version, size_t n)
	{
		if (version == nullptr)
			return nullptr;
		for (uint16 i = 0; i < n; i++)
		{
			if (isalpha(version[i]))
				return nullptr;
		}

		return VersionNumber(version);
	}
	VersionNumber operator ""_v(const char* version, size_t n)
	{
		if (version == nullptr)
			return nullptr;
		for (uint16 i = 0; i < n; i++)
		{
			if (isalpha(version[i]))
				return nullptr;
		}

		return VersionNumber(version);
	}
}