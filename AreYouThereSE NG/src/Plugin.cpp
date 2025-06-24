#include "pch.h"
#include "Plugin.h"

#include "Mod.h"
#include "FindCharacter.h"
#include "Pages.h"

#include <chrono>

namespace BeinzPlugin {
	Plugin* Plugin::GetInstance() {
		static Plugin instance;

		return &instance;
	}

	bool Plugin::InitMods() {
		const auto start = std::chrono::system_clock::now();
		SPDLOG_INFO("Initializing mod list");

		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		assert(dataHandler);

		Clear();

		ProcessFiles(dataHandler->compiledFileCollection);
		const auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);

		SPDLOG_INFO("Loaded: {} mods", Mods.size());
		SPDLOG_INFO("Found {} Actor", ActorCount);
		SPDLOG_INFO("Found {} ActorBases", NPCCount);
		SPDLOG_INFO("Done initializing: {}ms", end.count());

		return !Mods.empty();
	}

	void Plugin::Clear() {
		FoundActorPages::GetInstance()->Clear();
		FindCharacter::Clear();

		ActorPages::GetInstance()->Clear();
		ActorBasePages::GetInstance()->Clear();

		ModPages::Clear();

		ActorCount = NPCCount = 0;
		Mods.clear();
	}

	void Plugin::ProcessFiles(const RE::TESFileCollection &files) {
		SPDLOG_INFO("Parsing ESPs");
		ProcessFiles(files.files); {}

		SPDLOG_INFO("Parsing ESLs");
		ProcessFiles(files.smallFiles);
	}

	void Plugin::ProcessFiles(RE::BSTArray<RE::TESFile*> files) {
		const auto start = std::chrono::system_clock::now();
		for(const auto file : files) {
			const auto &mod = Mods.emplace_back(std::make_shared<Mod>(*file));

			ActorCount += mod->ActorCount();
			NPCCount += mod->NPCCount();
		}
		const auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
		SPDLOG_INFO("Done: {}ms", end.count());
	}
}
