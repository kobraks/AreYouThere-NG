#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <unordered_map>
#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>

#pragma warning(push)
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/SKSE.h>

#ifndef NDEBUG
#include <spdlog/sinks/msvc_sink.h>
#endif

#include <spdlog/sinks/basic_file_sink.h>

namespace logger = SKSE::log;

namespace util {
	using SKSE::stl::report_and_fail;
}

#pragma warning(pop)