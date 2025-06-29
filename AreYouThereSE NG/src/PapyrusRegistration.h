#pragma once
#include <string_view>

namespace BeinzPlugin {
	class PapyrusRegistration final {
	public:
		static bool Register(RE::BSScript::IVirtualMachine* vm);
	};
}