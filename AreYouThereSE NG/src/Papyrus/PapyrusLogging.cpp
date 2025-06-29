#include "pch.h"
#include "Papyrus.h"
#include "PapyrusCommon.h"

namespace BeinzPlugin::Papyrus {
	void WriteInfoLog(RE::StaticFunctionTag*, RE::BSFixedString message) {
		SPDLOG_INFO(message.c_str());
	}

	void WriteDebugLog(RE::StaticFunctionTag*, RE::BSFixedString message) {
		SPDLOG_DEBUG(message.c_str());
	}

	void WriteErrorLog(RE::StaticFunctionTag*, RE::BSFixedString message) {
		SPDLOG_ERROR(message.c_str());
	}

	bool RegisterLogging(RE::BSScript::IVirtualMachine* vm) {
		REGISTER_FUNCTION(WriteInfoLog);
		REGISTER_FUNCTION(WriteDebugLog);
		REGISTER_FUNCTION(WriteErrorLog);

		return true;
	}
}
