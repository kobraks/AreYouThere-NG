#include "pch.h"
#include "Papyrus.h"
#include "FindCharacter.h"
#include "Mod.h"
#include "Pages.h"
#include "Plugin.h"
#include "Utils.h"

#define REGISTER_FUNCTION(x) vm->RegisterFunction(#x, PAPYRUS_CLASS, x); SPDLOG_DEBUG("Register {} Function", #x);

namespace {
	std::shared_ptr<BeinzPlugin::Mod> GetMod(uint32_t modIndex) {
		auto mods = BeinzPlugin::Plugin::GetInstance()->Mods;
		if(modIndex < mods.size()) {
			const auto mod = mods[modIndex];

			SPDLOG_TRACE("Geting mod: {}, id: {}, index: {}", mod->Name(), mod->ID(), modIndex);

			return mod;
		}

		return nullptr;
	}

	std::shared_ptr<BeinzPlugin::Actor> GetActor(uint32_t modIdx, uint32_t actorIdx) {
		if(const auto mod = GetMod(modIdx); mod) {
			if(auto actor = mod->GetActor(actorIdx); actor)
				return actor;
		}

		return nullptr;
	}

	std::shared_ptr<BeinzPlugin::ActorBase> GetActorBase(uint32_t modIdx, uint32_t actorIdx) {
		if(const auto mod     = GetMod(modIdx); mod) {
			if(auto actorBase = mod->GetActorBase(actorIdx); actorBase)
				return actorBase;
		}

		return nullptr;
	}
}

namespace BeinzPlugin {
	bool InitMods(RE::StaticFunctionTag *) {
		return Plugin::GetInstance()->InitMods();
	}

	uint32_t GetTotalModCount(RE::StaticFunctionTag *) {
		return static_cast<uint32_t>(Plugin::GetInstance()->Mods.size());
	}

	uint32_t GetTotalActors(RE::StaticFunctionTag *) {
		return static_cast<uint32_t>(Plugin::GetInstance()->ActorCount);
	}

	uint32_t GetTotalNPCs(RE::StaticFunctionTag *) {
		return static_cast<uint32_t>(Plugin::GetInstance()->NPCCount);
	}

	RE::BSTArray<RE::BSFixedString> GenerateModPages(RE::StaticFunctionTag *) {
		return ModPages::GetInstance()->GetNames();
	}

	uint32_t GetModActorCount(RE::StaticFunctionTag *, uint32_t modIndex) {
		if(const auto mod = GetMod(modIndex); mod)
			return static_cast<uint32_t>(mod->ActorCount());

		return 0;
	}

	uint32_t GetModNPCCount(RE::StaticFunctionTag *, uint32_t modIndex) {
		if(const auto mod = GetMod(modIndex); mod)
			return static_cast<uint32_t>(mod->ActorCount());

		return 0;
	}

	auto GetModNames(RE::StaticFunctionTag *, uint32_t page) {
		if(auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetNames();
		}

		RE::BSTArray<RE::BSFixedString> empty;
		empty.emplace_back("Empty");
		return empty;
	}

	auto GetModIndexes(RE::StaticFunctionTag *, uint32_t page) {
		if(auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetIndexes();
		}

		RE::BSTArray<uint32_t> empty;
		empty.emplace_back(0);
		return empty;
	}

	auto GetModActorCounts(RE::StaticFunctionTag *, uint32_t page) {
		if(auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetActorCounts();
		}

		RE::BSTArray<uint32_t> empty;
		empty.emplace_back(0);
		return empty;
	}

	auto GetModNPCCounts(RE::StaticFunctionTag *, uint32_t page) {
		if(auto p = ModPages::GetInstance()->GetPage(page); p) {
			return p->GetNPCCounts();
		}

		RE::BSTArray<uint32_t> empty;
		empty.emplace_back(0);
		return empty;
	}

	auto GenerateActorPageStrings(RE::StaticFunctionTag *, uint32_t modIndex) {
		ActorPages::GetInstance()->Generate(GetMod(modIndex), modIndex);
		return ActorPages::GetInstance()->GetNames(modIndex);
	}

	auto GetActorsInPage(RE::StaticFunctionTag *, uint32_t modIndex, uint32_t page) {
		if(const auto p = ActorPages::GetInstance()->GetPage(page, modIndex); p) {
			return p->GetActors();
		}

		RE::BSTArray<RE::Actor*> empty;
		return empty;
	}

	auto GenerateNPCPageStrings(RE::StaticFunctionTag *, uint32_t modIndex) {
		ActorBasePages::GetInstance()->Generate(GetMod(modIndex), modIndex);
		return ActorBasePages::GetInstance()->GetNames(modIndex);
	}

	auto GetNPCsInPage(RE::StaticFunctionTag *, uint32_t modIndex, uint32_t page) {
		if(auto p = ActorBasePages::GetInstance()->GetPage(page, modIndex); p) {
			return p->GetActors();
		}

		RE::BSTArray<RE::TESNPC*> empty;
		return empty;
	}

	RE::BSFixedString GetModName(RE::StaticFunctionTag *, uint32_t index) {
		if(const auto mod = GetMod(index); mod)
			return mod->Name().data();

		return "";
	}

	RE::BSFixedString IntToHexString(RE::StaticFunctionTag *, uint32_t num) {
		return fmt::format("{:06X}", num).c_str();
	}

	RE::BSFixedString ModIndexToHexString(RE::StaticFunctionTag *, uint32_t num) {
		if(num < 0x100)
			return fmt::format("{:02X}", num).c_str();
		return fmt::format("FE:{:03X}", num).c_str();
	}

	RE::TESNPC* GetModNPC(RE::StaticFunctionTag *, uint32_t modIdx, uint32_t actorIdx) {
		if(auto actor = GetActorBase(modIdx, actorIdx); actor)
			return actor->Form<RE::TESNPC>();

		return nullptr;
	}

	RE::Actor* GetModActor(RE::StaticFunctionTag *, uint32_t modIdx, uint32_t actorIdx) {
		if(auto actor = GetActor(modIdx, actorIdx); actor)
			return actor->Form<RE::Actor>();

		return nullptr;
	}

	uint32_t GetModActorId(RE::StaticFunctionTag *, uint32_t modIdx, uint32_t actorIdx) {
		if(auto actor = GetActor(modIdx, actorIdx); actor)
			return actor->ID();

		return 0;
	}

	uint32_t GetModNPCId(RE::StaticFunctionTag *, uint32_t modIdx, uint32_t actorIdx) {
		if(auto actor = GetActorBase(modIdx, actorIdx); actor)
			return actor->ID();

		return 0;
	}

	uint32_t GetModFromActor(RE::StaticFunctionTag *, RE::Actor *actor) {
		if(actor) {
			SPDLOG_INFO("Looking for mod having an actor: {:08X}", actor->formID);

			size_t i = 0;
			for(const auto &mod : Plugin::GetInstance()->Mods) {
				if(mod->Contains(actor->formID)) {
					SPDLOG_DEBUG("Mod \"{}\", has actor: {:08X}", mod->CombinedName(), actor->formID);
					return static_cast<uint32_t>(i);
				}
				++i;
			}
		}

		return 0;
	}

	uint32_t FindCharactersByName(RE::StaticFunctionTag *, RE::BSFixedString name) {
		return static_cast<uint32_t>(FindCharacter::GetInstance()->FindCharacters(name.c_str()));
	}

	RE::BSTArray<RE::Actor*> FindCharactersByNameActors(RE::StaticFunctionTag *, uint32_t searchIndex) {
		const auto &actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		RE::BSTArray<RE::Actor*> ret;
		ret.reserve(static_cast<RE::BSTArray<RE::Actor*>::size_type>(actors.size()));

		Copy(
		     actors.begin(),
		     actors.end(),
		     std::back_inserter(ret),
		     [](const ActorSearchResult &res) { return res.Actor->Form<RE::Actor>(); }
		    );

		return ret;
	}

	RE::BSFixedString FindCharactersByNameModName(
		RE::StaticFunctionTag *,
		uint32_t searchIndex,
		uint32_t characterIndex
		) {
		const auto &actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		if(characterIndex < actors.size())
			return actors[characterIndex].Mod->Name().data();

		return "";
	}

	RE::BSTArray<RE::BSFixedString> FindCharactersByNameModNames(RE::StaticFunctionTag *, uint32_t searchIndex) {
		const auto &actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		RE::BSTArray<RE::BSFixedString> ret;
		ret.reserve(static_cast<RE::BSTArray<RE::detail::BSFixedString<char>>::size_type>(actors.size()));

		Copy(
		     actors.begin(),
		     actors.end(),
		     std::back_inserter(ret),
		     [](const ActorSearchResult &res) { return res.Mod->CombinedName().data(); }
		    );

		return ret;
	}

	RE::BSTArray<uint32_t> FindCharactersByNameModIndices(RE::StaticFunctionTag*, int searchIndex) {
		const auto &actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		RE::BSTArray<uint32_t> ret;
		ret.reserve(static_cast<RE::BSTArray<uint32_t>::size_type>(actors.size()));

		Copy(
		     actors.begin(),
		     actors.end(),
		     std::back_inserter(ret),
		     [](const ActorSearchResult &res) { return static_cast<uint32_t>(res.ModIndex); }
		    );

		return ret;
	}

	RE::BSTArray<RE::BSFixedString> GenerateFoundPages(RE::StaticFunctionTag*, int searchIndex) {
		FoundActorPages::GetInstance()->Generate(searchIndex);
		return FoundActorPages::GetInstance()->GetNames(searchIndex);
	}

	void ClearSearchCache(RE::StaticFunctionTag *) {
		FindCharacter::Clear();
		FoundActorPages::Clear();
	}

	void WriteInfoLog(RE::StaticFunctionTag *, RE::BSFixedString message) {
		
		SPDLOG_INFO(message.c_str());
	}

	void WriteDebugLog(RE::StaticFunctionTag *, RE::BSFixedString message) {
		SPDLOG_DEBUG(message.c_str());
	}

	void WriteErrorLog(RE::StaticFunctionTag *, RE::BSFixedString message) {
		SPDLOG_ERROR(message.c_str());
	}

	bool RegisterFuncs(RE::BSScript::IVirtualMachine *vm) {
		SPDLOG_DEBUG("Registering functions");

		REGISTER_FUNCTION(InitMods)
		REGISTER_FUNCTION(GetTotalModCount)
		REGISTER_FUNCTION(GetTotalActors)
		REGISTER_FUNCTION(GetTotalNPCs)

		REGISTER_FUNCTION(GenerateModPages)
		REGISTER_FUNCTION(GetModNames)
		REGISTER_FUNCTION(GetModIndexes)
		REGISTER_FUNCTION(GetModActorCounts)
		REGISTER_FUNCTION(GetModNPCCounts)

		REGISTER_FUNCTION(GetModActorCount)
		REGISTER_FUNCTION(GetModNPCCount)

		REGISTER_FUNCTION(GenerateActorPageStrings)
		REGISTER_FUNCTION(GenerateNPCPageStrings)

		REGISTER_FUNCTION(GetActorsInPage)
		REGISTER_FUNCTION(GetNPCsInPage)

		REGISTER_FUNCTION(GetModName)
		REGISTER_FUNCTION(GetModActor)
		REGISTER_FUNCTION(GetModNPC)
		REGISTER_FUNCTION(GetModActorId)
		REGISTER_FUNCTION(GetModNPCId)

		REGISTER_FUNCTION(IntToHexString)
		REGISTER_FUNCTION(ModIndexToHexString)

		REGISTER_FUNCTION(FindCharactersByName)
		REGISTER_FUNCTION(FindCharactersByNameActors)
		REGISTER_FUNCTION(FindCharactersByNameModName)

		REGISTER_FUNCTION(FindCharactersByNameModNames)
		REGISTER_FUNCTION(FindCharactersByNameModIndices)

		REGISTER_FUNCTION(GenerateFoundPages)
		REGISTER_FUNCTION(ClearSearchCache)

		REGISTER_FUNCTION(GetModFromActor)

		REGISTER_FUNCTION(WriteInfoLog)
		REGISTER_FUNCTION(WriteDebugLog)
		REGISTER_FUNCTION(WriteErrorLog)

		return true;
	}
}
