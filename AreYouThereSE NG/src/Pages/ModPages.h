#pragma once
#include "Page/ModPage.h"

namespace BeinzPlugin {
	class ModPages {
	public:
		std::vector<std::shared_ptr<ModPage>> Pages;

		std::shared_ptr<ModPage> GetPage(size_t page);

		void Generate();
		RE::BSTArray<RE::BSFixedString> GetNames();

		static ModPages *GetInstance();
		static void Clear();
	};
}