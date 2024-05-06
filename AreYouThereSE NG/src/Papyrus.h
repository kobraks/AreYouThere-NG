#pragma once

#include <string_view>

namespace BeinzPlugin {
	constexpr inline std::string_view PAPYRUS_CLASS = "BeinzPluginScript";

	bool RegisterFuncs(RE::BSScript::IVirtualMachine *vm);
}