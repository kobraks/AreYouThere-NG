#pragma once
#include "Page/ActorBasePage.h"

namespace BeinzPlugin {
	class Mod;

	class ActorBasePages {
	public:
		std::unordered_map<uint32_t, std::vector<std::shared_ptr<ActorBasePage>>> Pages;

		std::shared_ptr<ActorBasePage> GetPage(size_t page, uint32_t modID);

		void Generate(std::shared_ptr<Mod> mod, uint32_t modIndex);
		RE::BSTArray<RE::BSFixedString> GetNames(uint32_t modIndex);

		static ActorBasePages *GetInstance();
		static void Clear();
	};
}