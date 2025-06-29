#include "pch.h"
#include "PapyrusRegistration.h"

#include "Papyrus/Papyrus.h"

namespace BeinzPlugin {
	bool PapyrusRegistration::Register(RE::BSScript::IVirtualMachine* vm) {
		if (!vm) {
			logger::error("Papyrus VM is null!");
			return false;
		}

		bool result = true;

		result &= Papyrus::RegisterUtils(vm);
		result &= Papyrus::RegisterActor(vm);
		result &= Papyrus::RegisterMod(vm);
		result &= Papyrus::RegisterSearch(vm);
		result &= Papyrus::RegisterLogging(vm);

		return result;
	}

}
