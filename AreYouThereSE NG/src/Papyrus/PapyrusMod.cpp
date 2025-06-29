#include "pch.h"
#include "Papyrus.h"

#include "PapyrusHelper.h"
#include "Plugin.h"
#include "Mod.h"
#include "Actor.h"
#include "PapyrusCommon.h"
#include "Pages/ModPages.h"

namespace BeinzPlugin::Papyrus {
	uint32_t GetTotalModCount(RE::StaticFunctionTag*) {
		return static_cast<uint32_t>(Plugin::GetInstance()->Mods.size());
	}

	RE::BSTArray<RE::BSFixedString> GenerateModPages(RE::StaticFunctionTag*) {
		return ModPages::GetInstance()->GetNames();
	}

	uint32_t GetModActorCount(RE::StaticFunctionTag*, uint32_t modIndex) {
		if (const auto mod = GetMod(modIndex); mod)
			return static_cast<uint32_t>(mod->ActorCount());

		return 0;
	}

	uint32_t GetModNPCCount(RE::StaticFunctionTag*, uint32_t modIndex) {
		if (const auto mod = GetMod(modIndex); mod)
			return static_cast<uint32_t>(mod->NPCCount());

		return 0;
	}

	auto GetModNames(RE::StaticFunctionTag*, uint32_t page) {
		if (auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetNames();
		}

		RE::BSTArray<RE::BSFixedString> empty;
		empty.emplace_back("Empty");
		return empty;
	}

	auto GetModIndexes(RE::StaticFunctionTag*, uint32_t page) {
		if (auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetIndexes();
		}

		RE::BSTArray<uint32_t> empty;
		empty.emplace_back(0);
		return empty;
	}

	auto GetModActorCounts(RE::StaticFunctionTag*, uint32_t page) {
		if (auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetActorCounts();
		}

		RE::BSTArray<uint32_t> empty;
		empty.emplace_back(0);
		return empty;
	}

	auto GetModNPCCounts(RE::StaticFunctionTag*, uint32_t page) {
		if (auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetNPCCounts();
		}

		RE::BSTArray<uint32_t> empty;
		empty.emplace_back(0);
		return empty;
	}

	RE::BSFixedString GetModName(RE::StaticFunctionTag*, uint32_t index) {
		if (const auto mod = GetMod(index); mod)
			return mod->Name().data();

		return "";
	}

	RE::TESNPC* GetModNPC(RE::StaticFunctionTag*, uint32_t modIdx, uint32_t actorIdx) {
		if (auto actor = GetActorBase(modIdx, actorIdx); actor)
			return actor->GetNpcForm();

		return nullptr;
	}

	RE::Actor* GetModActor(RE::StaticFunctionTag*, uint32_t modIdx, uint32_t actorIdx) {
		if (auto actor = GetActor(modIdx, actorIdx); actor)
			return actor->GetActor();

		return nullptr;
	}

	uint32_t GetModActorId(RE::StaticFunctionTag*, uint32_t modIdx, uint32_t actorIdx) {
		if (auto actor = GetActor(modIdx, actorIdx); actor)
			return actor->ID();

		return 0;
	}

	uint32_t GetModNPCId(RE::StaticFunctionTag*, uint32_t modIdx, uint32_t actorIdx) {
		if (auto actor = GetActorBase(modIdx, actorIdx); actor)
			return actor->ID();

		return 0;
	}

	bool RegisterMod(RE::BSScript::IVirtualMachine* vm) {
		REGISTER_FUNCTION(GetTotalModCount);
		REGISTER_FUNCTION(GenerateModPages);
		REGISTER_FUNCTION(GetModNames);
		REGISTER_FUNCTION(GetModIndexes);
		REGISTER_FUNCTION(GetModActorCounts);
		REGISTER_FUNCTION(GetModNPCCounts);
		REGISTER_FUNCTION(GetModActorCount);
		REGISTER_FUNCTION(GetModNPCCount);
		REGISTER_FUNCTION(GetModName);
		REGISTER_FUNCTION(GetModActor);
		REGISTER_FUNCTION(GetModNPC);
		REGISTER_FUNCTION(GetModActorId);
		REGISTER_FUNCTION(GetModNPCId);

		return true;
	}
}
