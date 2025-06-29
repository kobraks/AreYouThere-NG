#pragma once

namespace BeinzPlugin {
	constexpr inline std::string_view PAPYRUS_CLASS = "BeinzPluginScript";
}

#define REGISTER_FUNCTION(x) vm->RegisterFunction(#x, PAPYRUS_CLASS, x); SPDLOG_DEBUG("Register {} Function", #x);
