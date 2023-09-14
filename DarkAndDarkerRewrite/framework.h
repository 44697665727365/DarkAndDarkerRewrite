#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define WINDOWS_IGNORE_PACKING_MISMATCH
#define NOMINMAX 1
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1

#include <Windows.h>
#include <sdkddkver.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <map>
#include <unordered_map>
#include <thread>
#include <string>
#include <cstring>
#include <math.h>
#include <conio.h>
#include "Hooking/detours.h"
#include <functional>
#include <optional>
#include <d3d11.h>
#include <fstream>
#include <deque>
#include <mutex>
#include <assert.h> 
#include <filesystem>
#include <codecvt>
#include <queue> 
#include <iterator>
#include <csetjmp>
#include <unordered_map>
#include <unordered_set>

#include <DXGI.h>
#include <mutex>
#include <d3d12.h>
#include <dxgi1_4.h>

#endif