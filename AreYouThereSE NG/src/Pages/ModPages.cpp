#include "pch.h"
#include "Pages/ModPages.h"

#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	std::shared_ptr<ModPage> ModPages::GetPage(size_t page) {
		if(page >= Pages.size())
			return nullptr;

		return Pages[page];
	}

	void ModPages::Generate() {
		if(Pages.empty()) {
			auto mods = Plugin::GetInstance()->Mods;

			const size_t count = HowManyPages(mods.size(), PAGE_ITEMS);

			if (count == 0) {
				Pages.emplace_back(std::make_shared<ModPage>(0, PAGE_ITEMS));
			}

			for(size_t page = 0; page < count; ++page) {
				Pages.emplace_back(std::make_shared<ModPage>(mods, page, PAGE_ITEMS));
			}
		}

		SPDLOG_DEBUG("Generated {} mod pages", Pages.size());
	}

	RE::BSTArray<RE::BSFixedString> ModPages::GetNames() {
		Generate();
		if(Pages.empty()) {
			RE::BSTArray<RE::BSFixedString> ret;
			ret.emplace_back("Empty");

			return ret;
		}
		return CopyPage<RE::BSTArray<RE::BSFixedString>>(
		                                                 Pages,
		                                                 PAGE_ITEMS,
		                                                 [](const std::shared_ptr<ModPage> &page) {
			                                                 return page->GenerateName();
		                                                 }
		                                                );
	}

	ModPages* ModPages::GetInstance() {
		static ModPages instance;

		return &instance;
	}

	void ModPages::Clear() {
		GetInstance()->Pages.clear();
	}
}
