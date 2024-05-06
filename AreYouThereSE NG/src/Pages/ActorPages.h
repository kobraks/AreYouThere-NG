#pragma once
#include "Page/ActorPage.h"

namespace BeinzPlugin {
	class Mod;

	class ActorPages {
	public:
		std::unordered_map<uint32_t, std::vector<std::shared_ptr<ActorPage>>> Pages;

		std::shared_ptr<ActorPage> GetPage(size_t page, uint32_t modID);

		void Generate(std::shared_ptr<Mod> mod, uint32_t modIndex);
		RE::BSTArray<RE::BSFixedString> GetNames(uint32_t modIndex);

		static ActorPages *GetInstance();
		static void Clear();
	};
}
