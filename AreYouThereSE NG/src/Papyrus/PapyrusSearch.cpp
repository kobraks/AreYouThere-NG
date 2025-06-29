#include "pch.h"
#include "Papyrus.h"

#include "FindCharacter.h"
#include "Actor.h"
#include "Mod.h"
#include "PapyrusCommon.h"
#include "Utils.h"
#include "Pages/FoundActorPages.h"

namespace BeinzPlugin::Papyrus {
	uint32_t FindCharactersByName(RE::StaticFunctionTag*, RE::BSFixedString name) {
		return static_cast<uint32_t>(FindCharacter::GetInstance()->FindCharacters(name.c_str()));
	}

	RE::BSTArray<RE::Actor*> FindCharactersByNameActors(RE::StaticFunctionTag*, uint32_t searchIndex) {
		const auto& actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		RE::BSTArray<RE::Actor*> ret;
		ret.reserve(static_cast<RE::BSTArray<RE::Actor*>::size_type>(actors.size()));

		Copy(
			actors.begin(),
			actors.end(),
			std::back_inserter(ret),
			[](const ActorSearchResult& res) { return res.Actor->GetActor(); }
		);

		return ret;
	}

	RE::BSFixedString FindCharactersByNameModName(
		RE::StaticFunctionTag*,
		uint32_t searchIndex,
		uint32_t characterIndex
	) {
		const auto& actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		if (characterIndex < actors.size())
			return actors[characterIndex].Mod->Name().data();

		return "";
	}

	RE::BSTArray<RE::BSFixedString> FindCharactersByNameModNames(RE::StaticFunctionTag*, uint32_t searchIndex) {
		const auto& actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		RE::BSTArray<RE::BSFixedString> ret;
		ret.reserve(static_cast<RE::BSTArray<RE::detail::BSFixedString<char>>::size_type>(actors.size()));

		Copy(
			actors.begin(),
			actors.end(),
			std::back_inserter(ret),
			[](const ActorSearchResult& res) { return res.Mod->CombinedName().data(); }
		);

		return ret;
	}

	RE::BSTArray<uint32_t> FindCharactersByNameModIndices(RE::StaticFunctionTag*, int searchIndex) {
		const auto& actors = FindCharacter::GetInstance()->GetSearchResult(searchIndex);
		SPDLOG_TRACE("Recived: {}, At: {}", actors.size(), searchIndex);

		RE::BSTArray<uint32_t> ret;
		ret.reserve(static_cast<RE::BSTArray<uint32_t>::size_type>(actors.size()));

		Copy(
			actors.begin(),
			actors.end(),
			std::back_inserter(ret),
			[](const ActorSearchResult& res) { return static_cast<uint32_t>(res.ModIndex); }
		);

		return ret;
	}

	RE::BSTArray<RE::BSFixedString> GenerateFoundPages(RE::StaticFunctionTag*, int searchIndex) {
		FoundActorPages::GetInstance()->Generate(searchIndex);
		return FoundActorPages::GetInstance()->GetNames(searchIndex);
	}

	void ClearSearchCache(RE::StaticFunctionTag*) {
		FindCharacter::Clear();
		FoundActorPages::GetInstance()->Clear();
	}

	bool RegisterSearch(RE::BSScript::IVirtualMachine* vm) {
		REGISTER_FUNCTION(FindCharactersByName);
		REGISTER_FUNCTION(FindCharactersByNameActors);
		REGISTER_FUNCTION(FindCharactersByNameModName);
		REGISTER_FUNCTION(FindCharactersByNameModNames);
		REGISTER_FUNCTION(FindCharactersByNameModIndices);
		REGISTER_FUNCTION(GenerateFoundPages);
		REGISTER_FUNCTION(ClearSearchCache);

		return true;
	}
}
