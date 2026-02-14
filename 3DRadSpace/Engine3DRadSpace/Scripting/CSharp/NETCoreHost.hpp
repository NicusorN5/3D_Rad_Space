#pragma once
#include "../../Core/Libs.hpp"
#include <nethost.h>
#include <hostfxr.h>
#include <coreclr_delegates.h>

using string_t = std::basic_string<char_t>;

#define STR(s) L ## s

bool load_hostfxr();
load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path);