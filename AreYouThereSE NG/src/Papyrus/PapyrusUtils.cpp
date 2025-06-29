#include "pch.h"
#include "Papyrus.h"

#include "Plugin.h"

#include "Papyrus/PapyrusCommon.h"

namespace BeinzPlugin::Papyrus {
	bool InitMods(RE::StaticFunctionTag*) {
		return Plugin::GetInstance()->InitMods();
	}

	RE::BSFixedString IntToHexString(RE::StaticFunctionTag*, uint32_t num) {
		return fmt::format("{:06X}", num);
	}

	RE::BSFixedString ModIndexToHexString(RE::StaticFunctionTag*, uint32_t num) {
		if (num < 0x100)
			return fmt::format("{:02X}", num);
		return fmt::format("FE:{:03X}", num);
	}

	bool RegisterUtils(RE::BSScript::IVirtualMachine* vm) {
		REGISTER_FUNCTION(InitMods);
		REGISTER_FUNCTION(IntToHexString);
		REGISTER_FUNCTION(ModIndexToHexString);

		return true;
	}
}