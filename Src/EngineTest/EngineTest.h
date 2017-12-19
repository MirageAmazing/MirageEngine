#include "../MirageEngine/Core/HAL/Platform.h"
#include <string>

#define Print(x) cout<<x<<endl
#define ResourcePath(x) "../../MirageEngine/Resource/"#x

void EnvironmentInfo()
{
	string header = "------------------------------------------";
	string platformTypeTips = "Current OS is ";
	string platformByteSizeTips = "Current OSType is ";
	string platformCompilerTips = "Current compiler is ";

	Print(header);

    #ifdef MIRAGE_PLATFORM_WINDOWS
        Print(platformTypeTips+"Windows");
    #elif MIRAGE_PLATFORM_LINUX
        Print(platformTypeTips+"Linux");    
    #elif MIRAGE_PLATFORM_MAC
        Print(platformTypeTips+"Mac");  
    #elif MIRAGE_PLATFORM_ANDROID
        Print(platformTypeTips+"Android");  
    #elif MIRAGE_PLATFORM_HTML5
        Print(platformTypeTips+"HTML5");    
    #elif MIRAGE_PLATFORM_IOS
        Print(platformTypeTips+"IOS");  
    #else
        Print(platformTypeTips+"Unknown");        
    #endif

    #ifdef MIRAGE_PLATFORM_32BIT
        Print(platformByteSizeTips+"32Bit");
    #elif MIRAGE_PLATFORM_64BIT
        Print(platformByteSizeTips+"64Bit");
    #else
        #error "This platform is not 32Bit or 64Bit."
    #endif

	#if defined(MIRAGE_COMPILER_CLANG)
		Print(platformCompilerTips+"CLANG");
	#elif defined(MIRAGE_COMPILER_GNUC)
		Print(platformCompilerTips+"GCC");
	#elif defined(MIRAGE_COMPILER_MSVC)
		Print(platformCompilerTips+"MSVC");
	#else
		#error Unsupported compiler was used.
	#endif

	Print(header);
}
