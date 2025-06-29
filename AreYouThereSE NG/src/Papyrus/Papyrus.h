#pragma once

namespace BeinzPlugin::Papyrus {
	bool RegisterActor(RE::BSScript::IVirtualMachine* vm);
	bool RegisterMod(RE::BSScript::IVirtualMachine* vm);
	bool RegisterSearch(RE::BSScript::IVirtualMachine* vm);
	bool RegisterUtils(RE::BSScript::IVirtualMachine* vm);
	bool RegisterLogging(RE::BSScript::IVirtualMachine* vm);
}