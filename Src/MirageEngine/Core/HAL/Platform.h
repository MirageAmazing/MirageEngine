#pragma once

#define MIRAGE_PLATFORM 1

// About CPU ( x86, x64, arm )
#if defined(__x86_64__) || defined(_M_X64)
	#define MIRAGE_PLATFORM_X64		1
	#define MIRAGE_PLATFORM_64BIT		1
	#define MIRAGE_PLATFORM_SSE2		1
#elif defined(__i386) || defined(_M_IX86)
	#define MIRAGE_PLATFORM_X86    1
	#define MIRAGE_PLATFORM_32BIT  1
#elif defined(__arm__) || defined(_M_ARM)
	#define MIRAGE_PLATFORM_ARM	1
	#define MIRAGE_PLATFORM_32BIT	1
	#if defined(__ARM_NEON__)
		#define MIRAGE_PLATFORM_NEON 1
	#endif
#else
	#define MIRAGE_PLATFORM_UNKNOWNCPU 1
#endif 

// About Platform( Win32, Win64, Linux, Android )
#if defined(_WIN32)
	#define MIRAGE_PLATFORM_DESKTOP   1
	#define MIRAGE_PLATFORM_WINDOWS 1
	#define MIRAGE_PLATFORM_WINAPI      1
	#if defined(_WIN64)
		#if !MIRAGE_PLATFORM_X64
			#error Unsupported Windows 64 CPU (the only supported is x86-64).
		#endif
	#else
		#if !MIRAGE_PLATFORM_X86
			#error Unsupported Windows 32 CPU (the only supported is x86).
		#endif
	#endif
#elif defined(__ANDROID__) || defined(ANDROID)
	#define MIRAGE_PLATFORM_MOBILE  1
	#define MIRAGE_PLATFORM_ANDROID 1
	#define MIRAGE_PLATFORM_POSIX   1
	#if !MIRAGE_PLATFORM_ARM || !MIRAGE_PLATFORM_32BIT
		#error Unsupported Android CPU (the only supported is 32-bit ARM).
	#endif
#elif defined(__linux__) || defined(__linux)
	#define MIRAGE_PLATFORM_DESKTOP 1
	#define MIRAGE_PLATFORM_LINUX   1
	#define MIRAGE_PLATFORM_POSIX   1
	#if !MIRAGE_PLATFORM_X64 && !MIRAGE_PLATFORM_X86
		#error Unsupported Linux CPU (the only supported are x86 and x86-64).
	#endif
#elif defined(__APPLE__)
	#define MIRAGE_PLATFORM_DESKTOP 1
	#define MIRAGE_PLATFORM_APPLE   1
	#define MIRAGE_PLATFORM_POSIX   1	
	#if TARGET_OS_IPHONE
		#define MIRAGE_PLATFORM_MOBILE 1
		#define MIRAGE_PLATFORM_IOS 1
		#if !MIRAGE_PLATFORM_UNKNOWNCPU
			#error Unsupported IOS CPU.
		#endif
		#define MIRAGE_PLATFORM_64BIT 1
	#elif TARGET_OS_MAC
		#define MIRAGE_PLATFORM_DESKTOP 1
		#define MIRAGE_PLATFORM_MAC 1
		#if !MIRAGE_PLATFORM_X64
			#error Unsupported Mac CPU(the only supported is x86-64).
		#endif
	#else
		#error Unknown Apple platform.
	#endif
#else
	#error Unknown target platform.
#endif

#if MIRAGE_PLATFORM_AVX
	#define MIRAGE_PLATFORM_ALIGNMENT 32
#elif MIRAGE_PLATFORM_SSE2 || MIRAGE_PLATFORM_SSE4 || MIRAGE_PLATFORM_NEON
	#define MIRAGE_PLATFORM_ALIGNMENT 16
#else
	#define MIRAGE_PLATFORM_ALIGNMENT 1
#endif

// About Compiler (clang, g++, msvc)
#if defined(__clang__)
#elif defined(__GNUC__)
#elif defined(_MSC_VER)
#else
	#error Unsupported compiler was used.
#endif