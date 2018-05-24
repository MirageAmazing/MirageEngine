#pragma once
#include "../Core.h"
#include <iostream>
using namespace std;

namespace MirageMath
{
	struct VersionNumber
	{
	public:
		VersionNumber(uint8 major = 0, uint8 minor = 0, uint8 revision = 0);
		VersionNumber(const char* version);
		VersionNumber(VersionNumber& In);

		MEINLINE uint8 MajorNumber() const 
		{ 
			return mVN.mVersionNumber[2]; 
		}
		MEINLINE uint8 MinorNumber() const 
		{ 
			return mVN.mVersionNumber[1]; 
		}
		MEINLINE uint8 RevisionNumber() const 
		{ 
			return mVN.mVersionNumber[0]; 
		}
		MEINLINE const char* VersionStr() const 
		{ 
			return const_cast<const char*>(mVersionStr); 
		};

		MEINLINE bool operator > (const VersionNumber& In) const
		{
			return mVN.mWholeNumber > In.mVN.mWholeNumber;
		}
		MEINLINE bool operator >= (const VersionNumber& In) const
		{
			return mVN.mWholeNumber >= In.mVN.mWholeNumber;
		}
		MEINLINE bool operator < (const VersionNumber& In) const
		{
			return mVN.mWholeNumber < In.mVN.mWholeNumber;
		}
		MEINLINE bool operator <= (const VersionNumber& In) const
		{
			return mVN.mWholeNumber <= In.mVN.mWholeNumber;
		}
		MEINLINE bool operator == (const VersionNumber& In) const
		{
			return mVN.mWholeNumber == In.mVN.mWholeNumber;
		}
	private:
		union uVersionNumber
		{
			uint8 mVersionNumber[4];
			uint32 mWholeNumber = 0;
		};
		uVersionNumber mVN;
		
		char mVersionStr[20];
	};

	MEINLINE ostream& operator << (ostream& out, VersionNumber& ver)
	{
		return out << ver.VersionStr();
	}

	VersionNumber operator ""_V(const char* version, size_t n);
	VersionNumber operator ""_v(const char* version, size_t n);
}
