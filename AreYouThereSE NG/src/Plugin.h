#pragma once

#include <string_view>

#include <REL/Version.h>

namespace BeinzPlugin {
	class Mod;

	using namespace std::literals;
	inline constexpr REL::Version VERSION { 1, 4, 2 };
	constexpr auto NAME = "AreYouThere NG"sv;

	inline constexpr size_t PAGE_ITEMS  = 64;
	inline constexpr size_t PAGE_ACTORS = 100;

	class Plugin {
	public:
		static Plugin* GetInstance();

		uint32_t InitMods();

		size_t ActorCount = 0;
		size_t NPCCount = 0;

		std::vector<std::shared_ptr<Mod>> Mods;

		std::unordered_map<uint32_t, RE::BSScript::Array> ActorPages;
		std::unordered_map<uint32_t, RE::BSScript::Array> NCCPages;

	private:
		void Clear();

		void ProcessFiles(const RE::TESFileCollection &files);
		void ProcessFiles(RE::BSTArray<RE::TESFile*> files);
	};
}
