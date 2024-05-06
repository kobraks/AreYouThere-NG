#pragma once
#include "Page/FoundActorPage.h"

namespace BeinzPlugin {
	class FoundActorPages {
	public:
		std::unordered_map<std::string, std::vector<std::shared_ptr<FoundActorPage>>> Pages;

		void Generate(const char *name);
		std::vector<std::shared_ptr<FoundActorPage>> &GetPages(const char *name);
		RE::BSTArray<RE::BSFixedString> GetNames(const char * name);

		static FoundActorPages *GetInstance();
		static void Clear();

	private:
		static std::string Prepare(const char* name);
	};
}