#pragma once
#include "Page/FoundActorPage.h"

namespace BeinzPlugin {
	class FoundActorPages {
	public:
		std::unordered_map<size_t, std::vector<std::shared_ptr<FoundActorPage>>> Pages;

		void Generate(size_t searchIndex);
		std::vector<std::shared_ptr<FoundActorPage>> &GetPages(size_t searchIndex);
		RE::BSTArray<RE::BSFixedString> GetNames(size_t searchIndex);

		static FoundActorPages *GetInstance();
		static void Clear();

	private:
	};
}