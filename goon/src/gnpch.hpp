#pragma once
//Std libs
#include <utility>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

//Data Structures
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <ostream>

//Handle platform specific includes.
#ifdef GN_PLATFORM_MACOS
#elifdef GN_PLATFORM_WINDOWS
#elifdef GN_PLATFORM_LINUX
#endif
