#include "pch.h"
#include "PapyrusHelper.h"
#include "Plugin.h"

#include "Actor.h"
#include "Mod.h"

namespace BeinzPlugin {
	std::shared_ptr<Mod> GetMod(uint32_t modIndex) {
		auto mods = Plugin::GetInstance()->Mods;

		if (modIndex < mods.size()) {
			const auto mod = mods[modIndex];
			SPDLOG_TRACE("Getting mod: {}, id: {:#x}, index: {}", mod->Name(), mod->ID(), modIndex);

			return mod;
		}

		SPDLOG_ERROR("Invalid mod index: {}", modIndex);
		return nullptr;
	}

	std::shared_ptr<Actor> GetActor(uint32_t modIndex, uint32_t actorIndex) {
		if (const auto mod = GetMod(modIndex); mod) {
			if (auto actor = mod->GetActor(actorIndex); actor) {
				return actor;
			}
		}

		return nullptr;
	}


	std::shared_ptr<ActorBase> GetActorBase(uint32_t modIndex, uint32_t actorIndex) {
		if (const auto mod = GetMod(modIndex); mod) {
			if (auto actorBase = mod->GetActorBase(actorIndex); actorBase) {
				return actorBase;
			}
		}

		return nullptr;
	}

}