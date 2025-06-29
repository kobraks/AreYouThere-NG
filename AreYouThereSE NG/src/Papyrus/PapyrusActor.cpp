#include "pch.h"
#include "Papyrus.h"

#include "Plugin.h"
#include "Mod.h"

#include "Pages/ActorBasePages.h"
#include "Pages/ActorPages.h"

#include "Papyrus/PapyrusHelper.h"
#include "Papyrus/PapyrusCommon.h"

namespace BeinzPlugin::Papyrus {
	uint32_t GetTotalActors(RE::StaticFunctionTag*) {
		return static_cast<uint32_t>(Plugin::GetInstance()->ActorCount);
	}

	uint32_t GetTotalNPCs(RE::StaticFunctionTag*) {
		return static_cast<uint32_t>(Plugin::GetInstance()->NPCCount);
	}

	auto GenerateActorPageStrings(RE::StaticFunctionTag*, uint32_t modIndex) {
		ActorPages::GetInstance()->Generate(GetMod(modIndex), modIndex);
		return ActorPages::GetInstance()->GetNames(modIndex);
	}

	auto GetActorsInPage(RE::StaticFunctionTag*, uint32_t modIndex, uint32_t page) {
		if (const auto p = ActorPages::GetInstance()->GetPage(page, modIndex); p) {
			return p->GetActors();
		}

		RE::BSTArray<RE::Actor*> empty;
		return empty;
	}

	auto GenerateNPCPageStrings(RE::StaticFunctionTag*, uint32_t modIndex) {
		ActorBasePages::GetInstance()->Generate(GetMod(modIndex), modIndex);
		return ActorBasePages::GetInstance()->GetNames(modIndex);
	}

	auto GetNPCsInPage(RE::StaticFunctionTag*, uint32_t modIndex, uint32_t page) {
		if (auto p = ActorBasePages::GetInstance()->GetPage(page, modIndex); p) {
			return p->GetActors();
		}

		RE::BSTArray<RE::TESNPC*> empty;
		return empty;
	}

	uint32_t GetModFromActor(RE::StaticFunctionTag*, RE::Actor* actor) {
		if (actor) {
			SPDLOG_INFO("Looking for mod having an actor: {:08X}", actor->formID);

			std::size_t i = 0;
			for (const auto& mod : Plugin::GetInstance()->Mods) {
				if (mod->Contains(actor->formID)) {
					SPDLOG_DEBUG("Mod \"{}\", has actor: {:08X}", mod->CombinedName(), actor->formID);
					return static_cast<uint32_t>(i);
				}
				++i;
			}
		}

		return 0;
	}

	bool RegisterActor(RE::BSScript::IVirtualMachine* vm) {
		REGISTER_FUNCTION(GetTotalActors)
		REGISTER_FUNCTION(GetTotalNPCs)
		REGISTER_FUNCTION(GenerateActorPageStrings)
		REGISTER_FUNCTION(GetActorsInPage)
		REGISTER_FUNCTION(GenerateNPCPageStrings)
		REGISTER_FUNCTION(GetNPCsInPage)
		REGISTER_FUNCTION(GetModFromActor)

		return true;
	}
}
