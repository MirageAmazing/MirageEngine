#pragma once

#include "HAL/Platform.h"
#include "HAL/MMalloc.h"

#include <type_traits>

#define FromBaseType(B,T) typename std::enable_if<std::is_base_of<B, T>::value, T>::type