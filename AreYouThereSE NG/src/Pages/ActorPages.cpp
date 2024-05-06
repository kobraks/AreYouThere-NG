#include "pch.h"
#include "Pages/ActorPages.h"

#include "Mod.h"
#include "Plugin.h"
#include "Utils.h"

namespace BeinzPlugin {
	std::shared_ptr<ActorPage> ActorPages::GetPage(size_t page, uint32_t modID) {
		if(auto it = Pages.find(modID); it != Pages.end()) {
			SPDLOG_TRACE("Found page: {}", page);
			const auto &vec = it->second;
			if(page < vec.size())
				return vec[page];
		}

		SPDLOG_TRACE("Page doesnt exists {} !", page);
		return nullptr;
	}

	void ActorPages::Generate(std::shared_ptr<Mod> mod, uint32_t modIndex) {
		if (Pages.contains(modIndex)) {
			SPDLOG_DEBUG("Page already exits returing cached");
			return;
		}

		auto &pages = Pages[modIndex];

		if(mod) {
			const auto &actors = mod->GetActors();

			const auto count = HowManyPages(actors.size(), PAGE_ACTORS);
			if(count == 0) {
				pages.emplace_back(std::make_shared<ActorPage>(0, PAGE_ACTORS));
			}

			for(size_t i = 0; i < count; ++i) {
				pages.emplace_back(std::make_shared<ActorPage>(actors, i, PAGE_ACTORS));
			}

			SPDLOG_DEBUG("Generated {} Actor pages", pages.size());
			return;
		}

		pages.emplace_back(std::make_shared<ActorPage>(0, PAGE_ACTORS));
		SPDLOG_ERROR("Incorrect mod, generated {} Actor pages", 1);
	}

	RE::BSTArray<RE::BSFixedString> ActorPages::GetNames(uint32_t modIndex) {
		if(auto it = Pages.find(modIndex); it != Pages.end()) {
			const auto &pages = it->second;

			return CopyPage<RE::BSTArray<RE::BSFixedString>>(
			                                                 pages,
			                                                 PAGE_ACTORS,
			                                                 [](const auto &page) { return page->GenerateName(); }
			                                                );
		}

		RE::BSTArray<RE::BSFixedString> empty;
		empty.emplace_back("Empty");
		return empty;
	}

	ActorPages* ActorPages::GetInstance() {
		static ActorPages instance;

		return &instance;
	}

	void ActorPages::Clear() {
		GetInstance()->Pages.clear();
	}
}
